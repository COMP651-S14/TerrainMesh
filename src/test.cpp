#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <vec3.h>
using namespace std;

int main(int argc, char *argv[]) {
	string fname = (argc == 2) ? string(argv[1]): "E:/University/COMP 651 - Computational Geometry/HW4/data/test1.txt";
	ifstream fin(fname);
	if (!fin.is_open()) {
		cout << "The file " << fname << " could not be opened for reading." << endl;
		return -1;
	}
	vector<vec3> vecArray;

	float maxx, maxy, maxz, minx, miny, minz;
	maxx = maxy = maxz = -10000;
	minx = miny = minz = 10000;

	while (!fin.eof()) {
		string raw_line;
		getline(fin, raw_line);
		if ((raw_line.length() <= 0) || (raw_line[0] == '#'))
			continue;

		stringstream ss(raw_line);
		float x, y, z;
		ss >> x >> y >> z;
		cout << x << " " << y << " " << z << endl;
		vecArray.push_back(vec3(x,y,z));

		if (x < minx) minx = x;
		if (x > maxx) maxx = x;
		if (y < miny) miny = y;
		if (y > maxy) maxy = y;
		if (z < minz) minz = z;
		if (z > maxz) maxz = z;
	}
	fin.close();

	cout << vecArray.size() << " vertices were read from " << fname << endl
		<< "The bounding box was: [" << minx << " " << miny << " " << minz << "] -> [" << maxx << " " << maxy << " " << maxz << "]" << endl;
	
	system("pause");
	return 0;
}

/*
#include <stdlib.h>
#include <stdio.h>

#include "cell.h"
#include "obj.h"

static void printCell(Cell *cell)
{
  {
    CellFaceIterator faces(cell);

    Face *face;

    while ((face = faces.next())!=0)
    {
      (void)printf("face %u: ", face->getID());

      FaceEdgeIterator edges(face);

      Edge *edge;

      while ((edge = edges.next())!=0)
	(void)printf("%u ", edge->Dest()->getID());

      (void)printf("\n");
    }
  }

  {
    CellVertexIterator vertices(cell);

    Vertex *vertex;

    while ((vertex = vertices.next())!=0)
    {
      (void)printf("vertex %u: ", vertex->getID());

      VertexEdgeIterator edges(vertex);

      Edge *edge;

      while ((edge = edges.next())!=0)
	(void)printf("%u ", edge->Left()->getID());

      (void)printf("\n");
    }
  }
}

int main(int argc, char **argv)
{
  if (argc>3)
  {
    (void)printf("usage: %s [<infile>.obj [<outfile>.obj]]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc==1)
  {
    Cell *cell = Cell::makeTetrahedron();

    printCell(cell);

    Cell::kill(cell);
  }

  if (argc>1)
  {
    Cell *cell = objReadCell(argv[1]);
    if (!cell)
      exit(EXIT_FAILURE);

    printCell(cell);

    if (argc>2)
      objWriteCell(cell, argv[2]);

    Cell::kill(cell);
  }

  return EXIT_SUCCESS;
}
*/