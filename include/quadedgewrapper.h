#ifndef QUADEDGEWRAPPER_H
#define QUADEDGEWRAPPER_H

typedef X QuadEdge;

class QuadEdgeWrapper
{
public:
    // this parameter should be the maximum possible number of quad-edges that
    // will be needed based on the number of vertices
    QuadEdgeWrapper(int maxNumQuadEdges);
    ~QuadEdgeWrapper();

    // gets the memory location to be initialized with a new quad-edge
    QuadEdge* getNewQuadEdgeMemory();
    // gets the existing quad edge as a pointer to the structure
    QuadEdge* getFirstQuadEdgeInStructure();
private:
    QuadEdge* edges;
    int numEdges, maxNumEdges;
};

#endif // QUADEDGEWRAPPER_H