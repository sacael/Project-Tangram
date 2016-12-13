#ifndef _GLOBJECT_H
#define NOMINMAX
#define _GLOBJECT_H
#include <vector>
#include "GLTriangle.h"
#include <algorithm> 
/*
class object on an object in the world
*/
class GLobject
{
public:
	Point4** getPoints();//getter of points of the objects by triangles
	GLfloat maxX;//information one the bounding box of the object
	GLfloat minX;
	GLfloat maxY;
	GLfloat minY;
	GLfloat maxZ;
	GLfloat minZ;
	Point4 center;//center of the object
	void updateValues();//update the values of center and boundingbox
	std::vector<GLTriangle*> triangles;// list of triangles
	GLobject(GLfloat[],int);
	~GLobject();
	bool pointInObject(GLfloat, GLfloat);
private:
	void updateCenter();//update the center
	void updateBox();//update the bounding box
};
#endif
