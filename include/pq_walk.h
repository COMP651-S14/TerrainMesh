#ifndef PQ_WALK_H
#define PQ_WALK_H

//need Edges, Vertexes, Vector3 (as a point)
#include "Vector3.h"
#include "edge.h"
/*need orient2d(): Return a positive value if the points pa, pb, and pc occur  */
/*               in counterclockwise order; a negative value if they occur   */
/*               in clockwise order; and zero if they are collinear.  The    */
/*               result is also a rough approximation of twice the signed    */
/*               area of the triangle defined by the three points.
*/
Edge * pq_walk(Vector3 q);
Edge * randEdge(Triangulation T);
bool leftOrOn(Vector3 p, Vector3 q);

#endif /*PQ_WALK_H*/


