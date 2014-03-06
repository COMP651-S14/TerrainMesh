
#include "triangulation.h"

Edge* localizePoint(Edge*,const Point&);

void Triangulation::triangulate(Edge* boundingFace, const std::vector<Point>& pts) {
    int size = pts.size();
    for (int i = 0; i < size; i++)
    {
        addPoint(boundingFace,pts.at(i));
    }
}

void Triangulation::addPoint(Edge* currentTris, const Point& pt) {
    Edge* tri = localizePoint(currentTris,pt);
    splitTriangle(tri,pt);
    std::vector<Edge*> edges;
    edges.push_back(getEdge(tri,0));
    edges.push_back(getEdge(tri,1));
    edges.push_back(getEdge(tri,2));
    questionEdges(edges,pt);
}

void Triangulation::splitTriangleToLeft(Edge* tri, const Point& ptInTri) {
}

void Triangulation::questionAndSwapEdges(std::vector<Edge*>& edges, const Point& newPoint) {
}

