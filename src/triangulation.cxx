
#include "triangulation.h"
#include "predicates.h"
#include "cell.h"

typedef double pos[3];

Edge* localizePoint(Cell *c, const Point& newPoint) {
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
        p[0][0] = v1->pos.getX();
        p[0][1] = v1->pos.getY();
        p[0][2] = v1->pos.getZ();
        p[1][0] = v2->pos.getX();
        p[1][1] = v2->pos.getY();
        p[1][2] = v2->pos.getZ();
        p[2][0] = v3->pos.getX();
        p[2][1] = v3->pos.getY();
        p[2][2] = v3->pos.getZ();
        if (orient2d(p[0],p[1],p[3]) >= 0 && orient2d(p[1],p[2],p[3]) >= 0 && orient2d(p[2],p[0],p[3]) >= 0) {
            return e1;
        }
    }
}

void questionAndSwapEdges(std::vector< Edge* >& edges,
                          const Point& newPoint);

void Triangulation::triangulate(Cell* boundingFace,
                                const std::vector< Point >& pts)
{
  int size = pts.size();
  for (int i = 0; i < size; i++) {
    addPoint(boundingFace, pts.at(i));
  }
}

void Triangulation::addPoint(Cell* c, const Point& pt)
{
    Edge *e1 = localizePoint(c,pt);
    Vertex *v1 = e1->Org(), *v2 = e1->Dest();
    Face *f = e1->Left();
    Edge *e2 = e1->Lnext();
    Edge *e3 = e2->Lprev();
    Vertex *v3 = e2->Dest();
    Face *f2 = c->makeFaceEdge(f,v1,v2)->Left();
    Vertex *vnew = c->makeVertexEdge(v2,f,f2)->Dest();
    c->makeFaceEdge(f,vnew,v3);
    std::vector<Edge*> neighbors;
    neighbors.push_back(e1->Sym());
    neighbors.push_back(e2->Sym());
    neighbors.push_back(e3->Sym());
    questionAndSwapEdges(neighbors,pt);
}

void questionAndSwapEdges(std::vector< Edge* >& edges,
                          const Point& newPoint)
{
    while (!edges.empty()) {
        Edge *e1 = edges.back();
        edges.pop_back();
        Vertex *v1 = e1->Org(), *v2 = e1->Dest();
        Edge *e2 = e1->Lnext();
        Edge *e3 = e2->Lprev();
        Vertex *v3 = e2->Dest();
        Edge *e4 = e1->Rnext();
        Edge *e5 = e1->Rprev();
        pos p[4];
        p[0][0] = v1->pos.getX();
        p[0][1] = v1->pos.getY();
        p[0][2] = v1->pos.getZ();
        p[1][0] = v2->pos.getX();
        p[1][1] = v2->pos.getY();
        p[1][2] = v2->pos.getZ();
        p[2][0] = v3->pos.getX();
        p[2][1] = v3->pos.getY();
        p[2][2] = v3->pos.getZ();
        p[3][0] = newPoint.x;
        p[3][1] = newPoint.y;
        p[3][2] = newPoint.z;
        // test if in circle
        if (incircle(p[0],p[1],p[2],p[3]) > 0)
        {
            Edge::splice(e1,e2);
            Edge::splice(e1,e3);
            Edge::splice(e1,e4);
            Edge::splice(e1,e5);
            e1->setOrg(e5->Dest());
            e1->setDest(e2->Dest());
            Edge::splice(e1,e4);
            Edge::splice(e1,e5->Sym());
            Edge::splice(e1,e2);
            Edge::splice(e1,e3->Sym());
            edges.push_back(e2->Sym());
            edges.push_back(e3->Sym());
        }
    }
}
