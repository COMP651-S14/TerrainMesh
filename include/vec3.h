#ifndef vec3INCLUDED
#define vec3INCLUDED

#include <ostream>

struct vec3 {
	float x;
	float y;
	float z;

	vec3() {}

	vec3(float newX, float newY, float newZ) {
		x = newX;
		y = newY;
		z = newZ;
	}
	void set(float newX, float newY, float newZ) {
		x = newX;
		y = newY;
		z = newZ;
	}

	friend std::ostream& operator<< (std::ostream& os, const vec3& vec);
	friend bool operator== (const vec3& v1, const vec3& v2);
};

inline std::ostream& operator<< (std::ostream& os, const vec3& vec) {
	os << "|" << vec.x << " " << vec.y << " " << vec.z << "|";
	return os;
}

inline bool operator== (const vec3& v1, const vec3& v2) {
	return (v1.x == v2.x) && (v1.y == v2.y);
}

#endif
