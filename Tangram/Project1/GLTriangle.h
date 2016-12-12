#ifndef _GLTRIANGLE_H
#define _GLTRIANGLE_H
#include <Windows.h>
#include <GL/GL.h>
#include "Point4.h"
class GLTriangle
{
public:
	Point4 * trianglePoints[3];
	Point4 getCenter();
	bool pointInTriangle(GLfloat, GLfloat);
	GLTriangle(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~GLTriangle();
private:
	float sign(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
};
#endif

