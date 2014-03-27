
#include "triangulation.h"
#include "cell.h"

Face* localizePoint(Cell*, const Point&);

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

void Triangulation::addPoint(Cell* currentTris, const Point& pt)
{
}

void splitTriangleToLeft(Cell* wrapper, Edge* tri,
                         const Point& ptInTri)
{
}

void questionAndSwapEdges(std::vector< Edge* >& edges,
                          const Point& newPoint)
{
}
