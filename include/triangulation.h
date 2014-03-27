#ifndef TRIANGULATION_H_INCLUDED
#define TRIANGULATION_H_INCLUDED

#include <vector>
#include <Vector3.h>

typedef Vector3 Point;
class Cell;

namespace Triangulation {

void triangulate(Cell* boundingFace, const std::vector<Point>& pts);

void addPoint(Cell* currentTris, const Point& pt);

}

#endif
