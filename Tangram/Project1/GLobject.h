#ifndef _GLOBJECT_H
#define NOMINMAX
#define _GLOBJECT_H
#include <vector>
#include "GLTriangle.h"
#include <algorithm> 
class GLobject
{
public:
	Point4** getPoints();
	GLfloat maxX;
	GLfloat minX;
	GLfloat maxY;
	GLfloat minY;
	GLfloat maxZ;
	GLfloat minZ;
	Point4 center;
	void updateValues();
	std::vector<GLTriangle*> triangles;
	GLobject(GLfloat[],int);
	~GLobject();
	bool pointInObject(GLfloat, GLfloat);
private:
	void updateCenter();
	void updateBox();
};
#endif
