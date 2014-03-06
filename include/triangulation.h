#ifndef TRIANGULATION_H_INCLUDED
#define TRIANGULATION_H_INCLUDED

#include <vector>

typedef Y Point;
class QuadEdgeWrapper;

namespace Triangulation {

void triangulate(QuadEdgeWrapper* boundingFace, const std::vector<Point>& pts);

void addPoint(QuadEdgeWrapper* currentTris, const Point& pt);


}

#endif
