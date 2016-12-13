#include "Button.h"


//getter for the points of the rectangle
Point4 ** Button::getPoints()
{
	Point4** returnpoints = new Point4*[6];
	returnpoints[0] = new Point4(minX, minY, 0);
	returnpoints[1] = new Point4(minX, maxY, 0);
	returnpoints[2] = new Point4(maxX, minY, 0);
	returnpoints[3] = new Point4(maxX, minY, 0);
	returnpoints[4] = new Point4(minX, maxY, 0);
	returnpoints[5] = new Point4(maxX, maxY, 0);
	return returnpoints;
}


//initialisation of the button
Button::Button( int _minX, int _maxX,  int _minY, int _maxY, World* _world)
{
	world = _world;
	minX = _minX;
	maxX = _maxX;
	minY = _minY;
	maxY = _maxY;
}

Button::~Button()
{
}
//verification if the point is in the button
bool Button::pointInObject(GLfloat xp , GLfloat yp)
{
	return !(xp<minX || xp>maxX || yp<minY || yp>maxY);
}
