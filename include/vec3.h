#ifndef vec3INCLUDED
#define vec3INCLUDED

#include <ostream>

class vec3 {

public:
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


	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	friend std::ostream& operator<< (std::ostream& os, const vec3& vec);
	friend bool operator== (const vec3& v1, const vec3& v2);
};

inline std::ostream& operator<< (std::ostream& os, const vec3& vec) {
	os << "|" << vec.getX() << " " << vec.getY() << " " << vec.getZ() << "|\n";
	return os;
}

inline bool operator== (const vec3& v1, const vec3& v2) {
	return (v1.getX() == v2.getX()) && (v1.getY() == v2.getY());
}

#endif
