#include "Button.h"
#include "NextLevel.h"


//on click on the button we switch to the next level
void NextLevel::actionOnClick()
{
	world->currentLevel++;
	world->UI.pop_back();
	world->InitLevel();
	delete this ;
}


NextLevel::NextLevel( int _minX, int _maxX,  int _minY, int _maxY, World* _world):Button( _minX, _maxX, _minY, _maxY, _world)
{
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
	Text = "Next Level";
}



NextLevel::~NextLevel()
{
}
