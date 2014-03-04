class Edge;

struct Vert
{

	float x;
	float y;
	float z;

	Edge* edge;  // one of the half-edges emantating from the vertex 

};

struct Face
{

    Edge* edge;  // one of the half-edges bordering the face

};

struct Edge
{

	Vert* vert;   // vertex at the end of the half-edge
	Edge* pair;   // oppositely oriented adjacent half-edge
	Face* face;   // face the half-edge borders
	Edge* next;   // next half-edge around the face

};
