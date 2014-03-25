#include "quadedgewrapper.h"

#include <cstdlib>
#include <cassert>

QuadEdgeWrapper::QuadEdgeWrapper(int maxNumQuadEdges) :
  edges(NULL),
  numEdges(0),
  maxNumEdges(maxNumQuadEdges)
{
    edges = reinterpret_cast<Edge*>(malloc(maxNumQuadEdges * sizeof(Edge)));
}

QuadEdgeWrapper::~QuadEdgeWrapper()
{
  free(reinterpret_cast<void*>(edges));
}

Edge* QuadEdgeWrapper::getNewQuadEdgeMemory()
{
  assert(numEdges < maxNumEdges);
  Edge* ret = &edges[numEdges];
  ++numEdges;
  return ret;
}

Edge* QuadEdgeWrapper::getFirstQuadEdgeInStructure()
{
  assert(numEdges > 0);
  return &edges[0];
}
