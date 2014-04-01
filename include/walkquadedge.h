#ifndef WALKQUADEDGE_H
#define WALKQUADEDGE_H

#include <iosfwd>

class Edge;
class Cell;

// This class allows you to walk around the quad-edge datastructure intractively
// and view how it is connected and what the movement operations do
class WalkQuadEdge
{
public:
    // Initialize the walk either at some undefined starting point (Cell constructor)
    // or a defined starting point (Edge constructor)
    WalkQuadEdge(Edge *startingPoint);
    WalkQuadEdge(Cell *cell);

    // run the interactive walk.  This method will return only after the user enters
    // "quit"
    void interactiveWalk(std::istream &in, std::ostream &out);
private:
    Edge *currentEdge;
};

#endif // WALKQUADEDGE_H
