#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public CCLayer
{
public:

	CREATE_FUNC(BackgroundLayer);

	virtual bool init();

public:

	void UpdateBloodValue(float percent);
	void UpdateFloorValue(int floor);


private:

	CCSprite* blood;

	CCLabelBMFont* floorFont;

	CCSize initBloodSize;

	int m_hasDownedFloor;

};