#pragma once

class NextLevel : public Button
{
public:
	virtual void actionOnClick();
	NextLevel(int,int,int,int,World*);
	~NextLevel();
};

