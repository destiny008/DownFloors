#include "TouchInput.h"


TouchInput::TouchInput()
{

}

TouchInput::~TouchInput()
{

}

void TouchInput::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void TouchInput::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}



bool TouchInput::ccTouchBegan(CCTouch* pTouch, CCEvent *pEvent)
{
	m_startPoint = pTouch->getLocationInView();

	return true;
}

void TouchInput::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) 
{
	CCPoint p = pTouch->getDelta();

	inputX = p.x * 0.75;

	//if(p.x > 2)
	//{
	//	inputX = 2;
	//	return;
	//}
	//else if(p.x < -2)
	//{
	//	inputX = -2;
	//	return;
	//}
	//inputX = 0;
}

void TouchInput::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) 
{
	inputX = 0;
}