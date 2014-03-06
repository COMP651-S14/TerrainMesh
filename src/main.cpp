#include <iostream>
#include <fstream>
#include <string>

struct Vector3{
    float x;
	float y;
	float z;

	friend std::istream& operator>>(std::istream& in, Vector3& vec);
	friend std::ifstream& operator >> (std::ifstream& in, Vector3& vec);
};



int main(){

	Vector3 ted;
	int blah;
	std::string test;
	std::ifstream fin;
	fin.open("xyz.txt");	

	if (fin.is_open()) {

		//fin >> test;
		fin >> ted;
		std::cout << ted.x << " " << ted.y << " " << ted.z << "\n";
		
		fin >> ted;
		std::cout << ted.x << " " << ted.y << " " << ted.z << "\n";
		
		//std::cout << test;
	}
	else {
		return 1;
	}
	fin.close();
	return 0;
}


std::istream& operator>>(std::istream& in, Vector3& vec)
{
    in >> vec.x >> vec.y >> vec.z;
	return in;
}

std::ifstream& operator >> (std::ifstream& in, Vector3& vec)
{
    in >> vec.x >> vec.y >> vec.z;
	return in;
}