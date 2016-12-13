#pragma once
#include <algorithm>
class World;
#include <vector>
#include <Windows.h>
#include <GL/gl.h>
#include "Point4.h"
#include "World.h"
/*
Button class for UI in rectangle form
*/

class Button
{
public:
	Point4** getPoints();//getter for the points of the rectangle
	GLfloat maxX;//parameter of the rectangle
	GLfloat minX;
	GLfloat maxY;
	GLfloat minY;
	World* world;//reference to the world
	std::string Text = "";//text of the button
	virtual void actionOnClick() =0;//action on click (virtual)
	Button(int, int, int, int, World*);
	~Button();
	bool pointInObject(GLfloat, GLfloat);//verification function of possession of a point
};

