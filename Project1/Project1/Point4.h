#ifndef _POINT4_H
#define _POINT4_H
class Point4
{
public:
    // constructors
	float X;
	float Y;
	float Z;
	float W;
	Point4(float, float, float);
	Point4();
	Point4 operator+(Point4 const& a);
	Point4 operator/(double const& a);
};
#endif
