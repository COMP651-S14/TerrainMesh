#ifndef vec3INCLUDED
#define vec3INCLUDED

#include <ostream>

class vec3 {

private:
	float x;
	float y;
	float z;

public:
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

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	friend std::ostream& operator<< (std::ostream& out, vec3& vec);
};

inline std::ostream& operator<< (std::ostream& out, vec3& vec) {
	out << "|" << vec.x << " " << vec.y << " " << vec.z << "|\n";
	return out;
}

#endif
