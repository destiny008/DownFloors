#pragma once

#include "cocos2d.h"
#include "GameBasic.h"

USING_NS_CC;

class IBackableScene : public CCScene
{
public:
	virtual bool GoBack() = 0;
};