#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BaseInput : public CCLayer
{
public:
	BaseInput();
	~BaseInput();

public:
	int inputX, inputY;
};