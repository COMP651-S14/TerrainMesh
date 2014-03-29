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
	// bool MyClass::operator==(const MyClass &other) const
	bool vec3::operator==( vec3 v1) {
		
		return !(x == v1.getX() && y==v1.getY());
		//return Vector2d<Type>( s * v._x, s * v._y );
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
