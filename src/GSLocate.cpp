
#include "GSLocate.h"

#include <predicates.h>
#include "edge.h"
/*  orient2dfast()   Approximate 2D orientation test.  Nonrobust.            */
/*  orient2dexact()   Exact 2D orientation test.  Robust.                    */
/*  orient2dslow()   Another exact 2D orientation test.  Robust.             */
/*  orient2d()   Adaptive exact 2D orientation test.  Robust.                */
/*                                                                           */
/*               Return a positive value if the points pa, pb, and pc occur  */
/*               in counterclockwise order; a negative value if they occur   */
/*               in clockwise order; and zero if they are collinear.  The    */
/*               result is also a rough approximation of twice the signed    */
/*               area of the triangle defined by the three points.           */                                    


Edge* gsLocate(vec3& x, Edge* initEdge){
	Edge * e=initEdge;
	while(true){
		if(x==e->Org->pos  || x==e->Dest->pos)
			return e;
		else
		{
			if(orient2dfastVec(e->Org->pos,e->Dest->pos,x)==-1) 
				e=e->Sym();
			else
			{
				if(orient2dfastVec(e->Onext()->Org->pos,e->Onext()->Dest->pos,x)!=-1)
					e=e->Onext();
				else
				{
					if(orient2dfastVec(e->Dprev()->Org->pos,e->Dprev()->Dest->pos,x)!=-1)
						e=e->Dprev();
					else
						return e;
				}
			}
		}

	}
}
