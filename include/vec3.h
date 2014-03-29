#ifndef vec3INCLUDED
#define vec3INCLUDED

class vec3 {

private:
	float x;
	float y;
	float z;

public:
	vec3() {}
	void set(float newX, float newY, float newZ)
	{
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
};

#endif
