#ifndef _GLTRIANGLE_H
#define _GLTRIANGLE_H
#include <Windows.h>
#include <GL/GL.h>
#include "Point4.h"
/*
class object of a triangle for opengl
*/
class GLTriangle
{
public:
	Point4 * trianglePoints[3];//list of the 3 points
	Point4 getCenter();//getter of the center
	bool pointInTriangle(GLfloat, GLfloat);//verification if the point is in the projection of the triangle
	GLTriangle(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~GLTriangle();
private:
	float sign(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
};
#endif

