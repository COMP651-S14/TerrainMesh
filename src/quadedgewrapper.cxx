#include "quadedgewrapper.h"

#include <cstdlib>
#include <cassert>

QuadEdgeWrapper::QuadEdgeWrapper(int maxNumQuadEdges) :
  edges(NULL),
  numEdges(0),
  maxNumEdges(maxNumQuadEdges)
{
    edges = reinterpret_cast<QuadEdge*>(malloc(maxNumQuadEdges * sizeof(QuadEdge)));
}

QuadEdgeWrapper::~QuadEdgeWrapper()
{
  free(reinterpret_cast<void*>(edges));
}

QuadEdge* QuadEdgeWrapper::getNewQuadEdgeMemory()
{
  assert(numEdges < maxNumQuadEdges);
  QuadEdge* ret = &edges[numEdges];
  ++numEdges;
  return ret;
}

QuadEdge* QuadEdgeWrapper::getFirstQuadEdgeInStructure()
{
  assert(numEdges > 0);
  return &edges[0];
}
