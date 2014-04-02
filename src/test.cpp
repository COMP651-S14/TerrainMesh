#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <vec3.h>
#include <cell.h>
#include <triangulation.h>
#include <predicates.h>
#include <GSLocate.h>
#include <walkquadedge.h>
using namespace std;

void printAllEdgesInCell(Cell *c) {
    int cell = 0;

    CellFaceIterator itr(c);
    Face *f = NULL;
    while ((f = itr.next())) {
        cout << "Face: " << f->getID() << endl;
        FaceEdgeIterator eitr(f);
        Edge *e = NULL;
        int edge = 0;
        while ((e = eitr.next())) {
            cout << "Edge " << edge <<" from " << e->Org()->pos << " to " << e->Dest()->pos << endl;
            ++edge;
        }
        cout << endl;
        ++cell;
    }
}

// deletes the vertex at the origin of the given edge
static inline void deleteVertexFromTriangulation(Cell *c, Edge *startEdge) {
    // the next line (commented) is only there for understanding
    //Vertex *vertexToDelete = startEdge->Org();
    Edge *endEdge = startEdge->Oprev();
    Edge *currentEdge = startEdge;
    Vertex *lastVertex = NULL;
//    Face *f = currentEdge->Left();
    while (currentEdge != endEdge) {
        // save values
        Edge *next = currentEdge->Onext();
        Vertex *nextDest = next->Dest();
        Vertex *dest = currentEdge->Dest();
        Face *f = currentEdge->Left();

        // delete the current edge
        c->killFaceEdge(currentEdge);

        // fix the dest vertices' triangulation
        // to change to deleting internal points, fix this section
        if (lastVertex != NULL) {
            // if a turn to the left, then dest is not on the convex hull and
            // the triangulation needs a triangle to fix the convex hull
            if (orient2dfastVec(lastVertex->pos,dest->pos,nextDest->pos) > 0) {
                c->makeFaceEdge(f,nextDest,lastVertex);
            }
        } else {
            // use saved values
            lastVertex = dest;
        }
        currentEdge = next;
    }
    // only endEdge is left of the edges containing vertexToDelete
    // this line also should effectively delete vertexToDelete
    c->killVertexEdge(endEdge->Sym());
}

// deletes the vertices for the initial face created in setUpInitialCell,
// leaving the result of the Delauney triangulation of the input points
// as the remainder
// This function assumes that the three vertices passed in have edges between
// them and a face that is made up of only these edges (infinite face), so that
// the selections of edges to do deletions from works correctly
static inline void deleteSetupVertices(Cell *c, Vertex *initialVertex1,
                         Vertex *initialVertex2, Vertex *initialVertex3) {
    VertexEdgeIterator vei(initialVertex1);
    Edge *e = NULL;
    while ( e == NULL || e->Dest() != initialVertex2) {
        e = vei.next();
    }
    if (e->Onext()->Dest() == initialVertex3) {
        e = e->Onext();
    }
    Edge *e1 = e;
    Edge *e2 = e1->Sym()->Onext();
    Edge *e3 = e2->Sym()->Onext()->Onext();
    deleteVertexFromTriangulation(c,e1);
    deleteVertexFromTriangulation(c,e2);
    deleteVertexFromTriangulation(c,e3);
}

Cell* setUpInitialCell(float minx, float maxx, float miny, float maxy) {
	float dmax = max( maxx - minx, maxy - miny );
	dmax = max( dmax, 10.0f );	// in case of a single point
	float cx = ( maxx - minx ) * 0.5f;
	float cy = ( maxy - miny ) * 0.5f;

	vec3 tri[3];
	tri[0].x = cx - 20.0f * dmax;
	tri[0].y = cy - dmax;
	tri[1].x = cx + 20.0f * dmax;
	tri[1].y = cy - dmax;
	tri[2].x = cx;
	tri[2].y = cy + 20.0f * dmax;

	Cell *cell = Cell::make();

	CellVertexIterator iter( cell );
	Vertex *v1 = iter.next();
	
	Edge *a = v1->getEdge();
	Face *left = a->Left();
	Face *right = a->Right();

	Vertex *v2 = cell->makeVertexEdge(v1, left, right)->Dest();
	Vertex *v3 = cell->makeVertexEdge(v2, left, right)->Dest();

	v1->pos.set( tri[0].x, tri[0].y, 0.0f );
	v2->pos.set( tri[1].x, tri[1].y, 0.0f );
	v3->pos.set( tri[2].x, tri[2].y, 0.0f );

	return cell;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Error: no filename specified." << endl;
        cerr << "Usage: " << argv[0] << " datafilename" << endl;
        exit(1);
    }
    string fname = string(argv[1]);
    ifstream fin(fname.c_str());
	if (!fin.is_open()) {
		cout << "The file " << fname << " could not be opened for reading." << endl;
		return -1;
	}
	vector<vec3> vecArray;

	float maxx, maxy, maxz, minx, miny, minz;
	maxx = maxy = maxz = -10000;
	minx = miny = minz = 10000;

	while (!fin.eof()) {
		string raw_line;
		getline(fin, raw_line);
		if ((raw_line.length() <= 0) || (raw_line[0] == '#'))
			continue;

		stringstream ss(raw_line);
		float x, y, z;
		ss >> x >> y >> z;
		cout << x << " " << y << " " << z << endl;
		vecArray.push_back(vec3(x,y,z));

		if (x < minx) minx = x;
		if (x > maxx) maxx = x;
		if (y < miny) miny = y;
		if (y > maxy) maxy = y;
		if (z < minz) minz = z;
		if (z > maxz) maxz = z;
	}
	fin.close();

	cout << vecArray.size() << " vertices were read from " << fname << endl
		<< "The bounding box was: [" << minx << " " << miny << " " << minz << "] -> [" << maxx << " " << maxy << " " << maxz << "]" << endl;
	
	//system("pause");
	
	Cell * initialCell = setUpInitialCell(minx, maxx, miny, maxy);
    Vertex *v1, *v2, *v3;
    {
        CellVertexIterator cvi(initialCell);
        v1 = cvi.next();
        v2 = cvi.next();
        v3 = cvi.next();
        assert(v1 != NULL);
        assert(v2 != NULL);
        assert(v3 != NULL);
        assert(cvi.next() == NULL);
    }
    Triangulation::triangulate(initialCell, vecArray);//, &gsLocate);
//    WalkQuadEdge w(initialCell);
//    w.interactiveWalk(cin,cout);

    cout << "Finished inserting points, removing initial face vertices..." << endl;
    deleteSetupVertices(initialCell,v1,v2,v3);

    printAllEdgesInCell(initialCell);

	return 0;
}
