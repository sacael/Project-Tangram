#include "Button.h"



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



Button::Button( int _minX, int _maxX,  int _minY, int _maxY, World* _world)
{
	world = _world;
	maxX = _maxX;
	maxY = _maxY;
	minX = _minX;
	minY = _minY;
}

Button::~Button()
{
}

bool Button::pointInObject(GLfloat xp , GLfloat yp)
{
	return !(xp<minX || xp>maxX || yp<minY || yp>maxY);
}
