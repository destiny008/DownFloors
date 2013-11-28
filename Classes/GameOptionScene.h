#pragma once

#include "IBackableScene.h"

USING_NS_CC;

class GameOptionScene : public IBackableScene
{
public:
	
	static CCScene* scene();

	CREATE_FUNC(GameOptionScene);

	bool GoBack();
}; 


class GameOptionLayer : public CCLayer
{
public:

	CREATE_FUNC(GameOptionLayer);

	virtual bool init();
};