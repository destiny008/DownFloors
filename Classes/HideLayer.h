#pragma once

#include "cocos2d.h"

USING_NS_CC;

class HideLayer : public CCLayerColor
{
public:
	CREATE_FUNC(HideLayer);

	virtual bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void registerWithTouchDispatcher();

	void onExit();
};