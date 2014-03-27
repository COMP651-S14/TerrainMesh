
#include "triangulation.h"
#include "cell.h"

Edge* localizePoint(Cell*, const Point&);

void splitTriangleToLeft(Cell* wrapper, Edge* tri,
                         const Point& ptInTri);

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
    Vertex *v1 = e1->Origin(), *v2 = e1->Dest();
    Face *f = e1->getLeft();
    Edge *e2 = e1->Lnext();
    Edge *e3 = e2->Lprev();
    Vertex *v3 = e2->Dest();
    Face *f2 = c->makeFaceEdge(f,v1,v2);
    Vertex *vnew = c->makeVertexEdge(v2,f,f2);
    c->makeFaceEdge(f,vnew,v3);
    // TODO - finish by testing neighbors
}

void splitTriangleToLeft(Cell* wrapper, Edge* tri,
                         const Point& ptInTri)
{
}

void questionAndSwapEdges(std::vector< Edge* >& edges,
                          const Point& newPoint)
{
}
