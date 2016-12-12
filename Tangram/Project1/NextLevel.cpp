#include "Button.h"
#include "NextLevel.h"



void NextLevel::actionOnClick()
{
	world->currentLevel++;
	world->UI.pop_back();
	world->InitLevel();
	delete this ;
}

NextLevel::NextLevel( int _minX, int _maxX,  int _minY, int _maxY, World* _world):Button( _minX, _maxX, _minY, _maxY, _world)
{
	Text = "Next Level";
}



NextLevel::~NextLevel()
{
}
