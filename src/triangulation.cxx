
#include "triangulation.h"


void Triangulation::triangulate(Triangle* boundingFace, const std::vector<Point>& pts) {
    int size = pts.size();
    for (int i = 0; i < size; i++)
    {
        addPoint(boundingFace,pts.at(i));
    }
}

void Triangulation::addPoint(Triangle* currentTris, const Point& pt) {
    Triangle* tri = localizePoint(currentTris,pt);
    splitTriangle(tri,pt);
    std::vector<Edge*> edges;
    edges.push_back(getEdge(tri,0));
    edges.push_back(getEdge(tri,1));
    edges.push_back(getEdge(tri,2));
    questionEdges(edges,pt);
}

Triangle* Triangulation::localizePoint(Triangle* currentTris, const Point& pt) {
}

void Triangulation::splitTriangle(Triangle* tri, const Point& ptInTri) {
}

void Triangulation::questionAndSwapEdges(std::vector<Edge*>& edges, const Point& newPoint) {
}

