#ifndef TRIANGULATION_H_INCLUDED
#define TRIANGULATION_H_INCLUDED

#include <vector>
#include <vec3.h>

typedef vec3 Point;

class Cell;
class Edge;
typedef Edge *(*LocateFunction)(vec3&, Edge*);

namespace Triangulation {

void triangulate(Cell* boundingFace, const std::vector<Point>& pts, LocateFunction l = NULL);

void addPoint(Cell* currentTris, const Point& pt, LocateFunction l = NULL);

}

#endif
