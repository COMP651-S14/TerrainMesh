#ifndef TRIANGULATION_H_INCLUDED
#define TRIANGULATION_H_INCLUDED

#include <vector>

typedef X Triangle;
typedef Y Point;
typedef Z Edge;

namespace Triangulation {

void triangulate(Triangle* boundingFace, const std::vector<Point>& pts);

void addPoint(Triangle* currentTris, const Point& pt);

Triangle* Triangulation::localizePoint(Triangle* currentTris, const Point& pt);

void splitTriangle(Triangle* tri, const Point& ptInTri);

void Triangulation::questionAndSwapEdges(std::vector<Edge*>& edges, const Point& newPoint);

}

#endif
