#include "GLTriangle.h";
#include <vector>;

Point4 GLTriangle::getCenter() {
	return Point4(((*trianglePoints[0]).X + (*trianglePoints[1]).X + (*trianglePoints[2]).X) / 3
		, ((*trianglePoints[0]).Y + (*trianglePoints[1]).Y + (*trianglePoints[2]).Y) / 3
		, ((*trianglePoints[0]).Z + (*trianglePoints[1]).Z + (*trianglePoints[2]).Z) / 3);
}

bool GLTriangle::pointInTriangle(GLfloat xp, GLfloat yp)
{
	bool b1, b2, b3;

	b1 = sign(xp,yp, (*trianglePoints[0]).X, (*trianglePoints[0]).Y, (*trianglePoints[1]).X, (*trianglePoints[1]).Y) < 0.0f;
	b2 = sign(xp, yp, (*trianglePoints[1]).X, (*trianglePoints[1]).Y, (*trianglePoints[2]).X, (*trianglePoints[2]).Y) < 0.0f;
	b3 = sign(xp, yp, (*trianglePoints[2]).X, (*trianglePoints[2]).Y, (*trianglePoints[0]).X, (*trianglePoints[0]).Y) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

GLTriangle::GLTriangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
	trianglePoints[0]= new Point4(x1,y1,z1);
	trianglePoints[1] =new Point4(x2, y2, z2);
	trianglePoints[2] =new Point4(x3, y3, z3);
}


GLTriangle::~GLTriangle()
{
	delete trianglePoints[0];
	delete trianglePoints[1];
	delete trianglePoints[2];
}

float GLTriangle::sign(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}
