#pragma once
#include <algorithm>;
class World;
#include <vector>;
#include <Windows.h>;
#include <GL/gl.h>;
#include "Point4.h";
#include "World.h";


class Button
{
public:
	Point4** getPoints();
	GLfloat maxX;
	GLfloat minX;
	GLfloat maxY;
	GLfloat minY;
	World* world;
	std::string Text = "";
	virtual void actionOnClick() =0;
	Button(int, int, int, int, World*);
	~Button();
	bool pointInObject(GLfloat, GLfloat);
};

