#include "HideLayer.h"


bool HideLayer::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 170)))
	{
		return false;
	}

	setTouchEnabled(true);


	return true;
}

void HideLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void HideLayer::onExit()
{
	setTouchEnabled(false);
}

bool HideLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{ 
	return true;
};