#include "vertex.h"

class Edge;

/*
	@brief:        Locate edge containing or bounding a point	
	@param		X			point whose location has to be found
	@returns :     Returns the edge on which point x lies or which has the trangle containing X on its left
*/
Edge* gsLocate(vec3& x, Edge* initEdge);

