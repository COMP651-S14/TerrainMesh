#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <vec3.h>
#include <cell.h>
#include <triangulation.h>
#include <GSLocate.h>
using namespace std;

void printAllEdgesInCell(Cell *c) {
    int cell = 0;

    CellFaceIterator itr(c);
    Face *f = NULL;
    while ((f = itr.next())) {
        cout << "Cell: " << cell << endl;
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
    Triangulation::triangulate(initialCell, vecArray);//, &gsLocate);

    printAllEdgesInCell(initialCell);

	return 0;
}

/*
#include <stdlib.h>
#include <stdio.h>

#include "cell.h"
#include "obj.h"

static void printCell(Cell *cell)
{
  {
    CellFaceIterator faces(cell);

    Face *face;

    while ((face = faces.next())!=0)
    {
      (void)printf("face %u: ", face->getID());

      FaceEdgeIterator edges(face);

      Edge *edge;

      while ((edge = edges.next())!=0)
	(void)printf("%u ", edge->Dest()->getID());

      (void)printf("\n");
    }
  }

  {
    CellVertexIterator vertices(cell);

    Vertex *vertex;

    while ((vertex = vertices.next())!=0)
    {
      (void)printf("vertex %u: ", vertex->getID());

      VertexEdgeIterator edges(vertex);

      Edge *edge;

      while ((edge = edges.next())!=0)
	(void)printf("%u ", edge->Left()->getID());

      (void)printf("\n");
    }
  }
}

int main(int argc, char **argv)
{
  if (argc>3)
  {
    (void)printf("usage: %s [<infile>.obj [<outfile>.obj]]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc==1)
  {
    Cell *cell = Cell::makeTetrahedron();

    printCell(cell);

    Cell::kill(cell);
  }

  if (argc>1)
  {
    Cell *cell = objReadCell(argv[1]);
    if (!cell)
      exit(EXIT_FAILURE);

    printCell(cell);

    if (argc>2)
      objWriteCell(cell, argv[2]);

    Cell::kill(cell);
  }

  return EXIT_SUCCESS;
}
*/
