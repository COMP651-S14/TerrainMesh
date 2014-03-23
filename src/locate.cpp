#include "../include/locate.h"
#include "edge.cpp"
#include "predicates.cpp"
#include "vertex.cpp"

/* *********************Point Location***************************
TODO:   equivalent(), randEdge(), retrieveTriangulation()
CHECK:  orient2d() the right thing to use?


*****************************************************/



/* Need to access the triangulation. Get an edge from the triangulation.
Only need to test until 3 edges (consecutive in the iteration) all have point q the the left or on the edge.
To avoid some computation, test if the point is the end point of an edge first. If leftOrOn() test returns
false, take the symmetric edge and continue testing in ccw direction (i.e. Lnext()).

Someone should double check my work.
*/
pq_walk(Vector3 q){
    //get triangulation Triangulation

    Edge e = randEdge(theTriangulation);

    int counter = 0;
    while(counter < 3){
        if(equivalent(q,e.Org()) || equivalent(q,e.Dest()))
            return e;
        bool iterativeVal = leftOrOn(e,q);

        if(!iterativeVal) {
            e = e.Sym;
            counter = 0;
        }
        else {
            e = e.Lnext();
            counter++;
        }

    }
    return e;
}
//From lischinski paper..............
// Returns an edge e, s.t. either x is on e, or e is an edge of
// a triangle containing x. The search starts from startingEdge
// and proceeds in the general direction of x. Based on the
// pseudocode in Guibas and Stolfi (1985) p.121.
GSLocate(Vector3 q){
Edge e = randEdge(theTriangulation);

while(true){
    if(equivalent(q,e.Org()) || equivalent(q,e.Dest())) return e;
    else if(!leftOrOn(e,q)) e = e.Sym();
    else if (leftOrOn(e, e.Onext())) e = e.Onext();
    else if (leftOrOn(e,e.Dprev())) e = e.Dprev();
    else return e;
}
}


randEdge(Triangulation T){
    //get a random edge or apply some heuristic
}

leftOrOn(Edge e, Vector3 q){
    float org[3] = {e.org.pos.getX(), e.org.pos.getY(), e.org.pos.getZ()};
    float dest[3] = {e.dest.pos.getX(), e.dest.pos.getY(), e.dest.pos.getZ()};
    float pointQ[3] = {q.x,q.y,q.z};
    if(orient2d(org, dest,pointQ ) >= 0 ){
        return true;
    }
    else return false;
}
equivalent(Vector3 q, Vertex edgeVertex){
}

