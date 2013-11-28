#pragma once

#include "cocos2d.h"
#include "BaseInput.h"

class TouchInput : public BaseInput
{
public:
	TouchInput();
	~TouchInput();

	virtual void onEnter();
	virtual void onExit();

public:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCPoint m_startPoint;
};