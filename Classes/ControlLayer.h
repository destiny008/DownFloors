#pragma once

#include "cocos2d.h"
#include "BaseInput.h"
#include "KeyBoardInput.h"

USING_NS_CC;
using namespace Windows::System;

class ControlLayer : public BaseInput, public CCKeyboardDelegate
{
public:
	CREATE_FUNC(ControlLayer);

	virtual void OnKeyDown(VirtualKey key);

	virtual void OnKeyUp();

	virtual bool init();
};