#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vector3.h"





int main(){

	Vector3 ted;
	std::string test;
	std::ifstream fin;
	fin.open("..\\..\\data\\membrane_xyz.txt");	
	float maxx, maxy, maxz, minx, miny, minz;
	maxx = maxy = maxz = -10000;
	minx = miny = minz = 10000;
	std::vector<Vector3> vectorList;
	vectorList.reserve(15000);

	
	if (fin.is_open()) {

		//fin >> test;
		while (!fin.eof()){   
			fin >> ted;
			//std::cout << ted.x << " " << ted.y << " " << ted.z << "\n";
		
			if (ted.x > maxx)
				maxx = ted.x;
			else if (ted.x < minx)
				minx = ted.x;

			if (ted.y > maxy)
				maxy = ted.y;
			else if (ted.y < miny)
				miny = ted.y;

			if (ted.z > maxz)
				maxz = ted.z;
			else if (ted.z < minz)
				minz = ted.z;

			vectorList.push_back(ted);
		}
		std::cout <<"MAX " << maxx << " min " << minx << std::endl;
	}
	else {
		return 1;
	}
	std::cout <<"SIZE " << vectorList.size() << std::endl;
	fin.close();
	return 0;
}


