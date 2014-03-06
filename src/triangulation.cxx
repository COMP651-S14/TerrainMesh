
#include "triangulation.h"
#include "quadedgewrapper.h"

QuadEdge* localizePoint(QuadEdge*, const Point&);

void splitTriangleToLeft(QuadEdgeWrapper* wrapper, QuadEdge* tri,
                         const Point& ptInTri);

void questionAndSwapEdges(std::vector< QuadEdge* >& edges,
                          const Point& newPoint);

void Triangulation::triangulate(QuadEdgeWrapper* boundingFace,
                                const std::vector< Point >& pts)
{
  int size = pts.size();
  for (int i = 0; i < size; i++) {
    addPoint(boundingFace, pts.at(i));
  }
}

void Triangulation::addPoint(QuadEdgeWrapper* currentTris, const Point& pt)
{
  QuadEdge* tri = localizePoint(currentTris.getFirstQuadEdgeInStructure(), pt);
  splitTriangle(currentTris, tri, pt);
  std::vector< QuadEdge* > edges;
  edges.push_back(getEdge(tri, 0));
  edges.push_back(getEdge(tri, 1));
  edges.push_back(getEdge(tri, 2));
  questionEdges(edges, pt);
}

void Triangulation::splitTriangleToLeft(QuadEdgeWrapper* wrapper, QuadEdge* tri,
                                        const Point& ptInTri)
{
}

void Triangulation::questionAndSwapEdges(std::vector< QuadEdge* >& edges,
                                         const Point& newPoint)
{
}
