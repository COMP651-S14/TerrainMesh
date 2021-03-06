#include "triangulation.h"
#include "predicates.h"
#include "cell.h"
#include <iostream>
using namespace std;

typedef double pos[3];

Edge* localizePoint(Cell *c, const vec3& newPoint) {
    cout << "Now inserting point " << newPoint << " in cell with vertices:\n";
	CellVertexIterator iter(c);
	Vertex *v = iter.next();
	for (; v != NULL; v = iter.next()) {
		cout << v->pos << endl;
	}
	CellFaceIterator faces(c);
    Face *f = NULL;
    pos p[4];
    p[3][0] = newPoint.x;
    p[3][1] = newPoint.y;
    p[3][2] = newPoint.z;
    while ((f = faces.next())) {
        Edge *e1 = f->getEdge();
        Edge *e2 = e1->Lnext();
        Vertex *v1 = e1->Org();
        Vertex *v2 = e1->Dest();
        Vertex *v3 = e2->Dest();
        p[0][0] = v1->pos.x;
        p[0][1] = v1->pos.y;
        p[0][2] = v1->pos.z;
        p[1][0] = v2->pos.x;
        p[1][1] = v2->pos.y;
        p[1][2] = v2->pos.z;
        p[2][0] = v3->pos.x;
        p[2][1] = v3->pos.y;
        p[2][2] = v3->pos.z;
        if ((orient2d(p[0],p[1],p[3]) >= 0) && (orient2d(p[1],p[2],p[3]) >= 0) && (orient2d(p[2],p[0],p[3]) >= 0)) {
            return e1;
        }
    }
	cout << "Returned NULL!" << endl;
	return NULL;
}

void testAndSwapEdges(Cell *c, vector<Edge*>& edges, const Point& newPoint);

void Triangulation::triangulate(Cell* boundingFace, const vector<Point>& pts, LocateFunction l)
{
  int size = pts.size();
  for (int i = 0; i < size; i++) {
    addPoint(boundingFace, pts.at(i), l);
  }
}

void Triangulation::addPoint(Cell* c, const Point& pt, LocateFunction l)
{
    // locate point
    Edge *e0;
    CellFaceIterator fitr(c);
    e0 = fitr.next()->getEdge();
    vec3 v;
    v.set(pt.x,pt.y,pt.z);

    Edge *e1 = (l != NULL) ? l(v,e0) : localizePoint(c,pt);

    Vertex *v1 = e1->Org(), *v2 = e1->Dest();
    Face *f = e1->Left();
    Edge *e2 = e1->Lnext();
    Edge *e3 = e1->Lprev();
    Vertex *v3 = e2->Dest();
    Face *f2 = c->makeFaceEdge(f,v1,v2)->Right();
    Vertex *vnew = c->makeVertexEdge(v2,f2,f)->Dest();
	vnew->pos.set(pt.x,pt.y,pt.z);
    c->makeFaceEdge(f,vnew,v3);
    std::vector<Edge*> neighbors;
    neighbors.push_back(e1->Sym());
    neighbors.push_back(e2->Sym());
    neighbors.push_back(e3->Sym());
    testAndSwapEdges(c,neighbors,pt);
}

void testAndSwapEdges(Cell *c, std::vector< Edge* >& edges, const Point& newPoint)
{
    while (!edges.empty()) {
        Edge *e1 = edges.back();
        edges.pop_back();
        Vertex *v1 = e1->Org(), *v2 = e1->Dest();
        Edge *e2 = e1->Lnext();
        Edge *e3 = e1->Lprev();
        Vertex *v3 = e2->Dest();
        Edge *e4 = e1->Rnext();
        Edge *e5 = e1->Rprev();
        pos p[4];
        p[0][0] = v1->pos.x;
        p[0][1] = v1->pos.y;
        p[0][2] = v1->pos.z;
        p[1][0] = v2->pos.x;
        p[1][1] = v2->pos.y;
        p[1][2] = v2->pos.z;
        p[2][0] = v3->pos.x;
        p[2][1] = v3->pos.y;
        p[2][2] = v3->pos.z;
        p[3][0] = newPoint.x;
        p[3][1] = newPoint.y;
        p[3][2] = newPoint.z;
        // test if in circle
        if (incircle(p[0],p[1],p[2],p[3]) > 0)
        {
            Face *left = e1->Left();
            c->killFaceEdge(e1);
            c->makeFaceEdge(left,e2->Dest(),e5->Dest());
            edges.push_back(e2->Sym());
            edges.push_back(e3->Sym());
        }
    }
}
