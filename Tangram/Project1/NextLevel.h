#pragma once
/*
class of implementation of a button for going to the next level
*/
class NextLevel : public Button
{
public:
	virtual void actionOnClick();
	NextLevel(int,int,int,int,World*);
	~NextLevel();
};

