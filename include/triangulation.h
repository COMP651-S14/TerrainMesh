#ifndef TRIANGULATION_H_INCLUDED
#define TRIANGULATION_H_INCLUDED

#include <vector>

typedef Y Point;
typedef Z Edge;

namespace Triangulation {

void triangulate(Edge* boundingFace, const std::vector<Point>& pts);

void addPoint(Edge* currentTris, const Point& pt);

void splitTriangleToLeft(Edge* tri, const Point& ptInTri);

void Triangulation::questionAndSwapEdges(std::vector<Edge*>& edges, const Point& newPoint);

}

#endif
