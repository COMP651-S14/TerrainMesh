#ifndef INC_VECTOR3_H
#define INC_VECTOR3_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Vector3{
    float x;
	float y;
	float z;

	friend std::istream& operator>>(std::istream& in, Vector3& vec);
	friend std::ifstream& operator >> (std::ifstream& in, Vector3& vec);
};


inline std::istream& operator>>(std::istream& in, Vector3& vec)
{
    in >> vec.x >> vec.y >> vec.z;
	return in;
}

inline std::ifstream& operator >> (std::ifstream& in, Vector3& vec)
{
    in >> vec.x >> vec.y >> vec.z;
	return in;
}

#endif	// INC_VECTOR3_H
