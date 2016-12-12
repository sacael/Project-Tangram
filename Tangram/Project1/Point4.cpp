#include "Point4.h"


Point4::Point4(float x, float y, float z) 
{ 
	X = x;
	Y= y;
	Z = z;
	W = 1; }

Point4::Point4()
{
	X = 0;
	Y = 0;
	Z = 0;
	W = 1;
}

Point4 Point4::operator+(Point4 const & a)
{
	return Point4(X+a.X, Y + a.Y, Z + a.Z);
}

Point4 Point4::operator/(double const & a)
{
	return Point4(X/a, Y/a, Z/a);
}
