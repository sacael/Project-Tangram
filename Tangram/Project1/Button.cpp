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

	int currentWidth = glutGet(GLUT_WINDOW_WIDTH);
	int currentHeight = glutGet(GLUT_WINDOW_HEIGHT);

	GLint centerX = currentWidth / 2;
	GLint centerY = currentHeight / 2;
	GLint halfWidth = (_maxX - _minX) / 2;
	GLint halfHeight = (_maxY - _minY) / 2;

	Point4* center = new Point4(centerX, centerY, 0);
	Point4* halfSize = new Point4(halfWidth, halfHeight, 0);

	maxX = center->X + halfSize->X;
	maxY = center->Y + halfSize->Y;
	minX = center->X - halfSize->X;
	minY = center->Y - halfSize->Y;
}

Button::~Button()
{
}

bool Button::pointInObject(GLfloat xp , GLfloat yp)
{
	return !(xp<minX || xp>maxX || yp<minY || yp>maxY);
}
