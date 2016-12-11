#include "Button.h"
#include "NextLevel.h"



void NextLevel::actionOnClick()
{
	world->currentLevel++;
	world->InitLevel();
	world->UI.pop_back();
	delete this ;
}

NextLevel::NextLevel( int _minX, int _maxX,  int _minY, int _maxY, World* _world):Button( _minX, _maxX, _minY, _maxY, _world)
{
}



NextLevel::~NextLevel()
{
}
