#ifndef LOCATE_H
#define LOCATE_H

//need Edges, Vertexes, Vector3 (as a point)
#include "Vector3.h"
#include "edge.h"
/*need orient2d(): Return a positive value if the points pa, pb, and pc occur  */
/*               in counterclockwise order; a negative value if they occur   */
/*               in clockwise order; and zero if they are collinear.  The    */
/*               result is also a rough approximation of twice the signed    */
/*               area of the triangle defined by the three points.
*/
Vector3 p;
Edge * pq_walk(Vector3 q);
Edge * GSLocate(Vector3 q);
Edge * randEdge(Triangulation T);
bool leftOrOn(Edge e, Vector3 q);
bool equivalent(Vector3 q, Vertex edgeVertex);

#endif /*LOCATE_H*/


