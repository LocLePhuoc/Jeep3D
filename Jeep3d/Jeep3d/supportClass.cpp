
#include "supportClass.h"
#include <math.h>


Point3 Point3::operator - (Point3 b) {
	float x, y, z;
	x = this->x - b.x;
	y = this->y - b.y;
	z = this->z - b.z;
	return Point3(x, y, z);
}

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
	return c;
}

float Vector3::dot(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x*x + y*y + z*z);
	x = x/temp;
	y = y/temp;
	z = z/temp;
}
