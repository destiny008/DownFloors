#pragma once

#include "cocos2d.h"
#include "GameBasic.h"
#include "IBackableScene.h"

USING_NS_CC;

class StartScene : public IBackableScene
{
public:
	static CCScene* scene();

	CREATE_FUNC(StartScene);

	bool GoBack();
};

class StartLayer : public CCLayer
{
public:
	CREATE_FUNC(StartLayer);

	virtual bool init();

	void InitAnimation();
	
	void InitGameResourceAsync(float dt);
	void InitGameResourceCallBack(CCObject* sender);

	void LoadUserSettings();

private:
	CCSprite* wheel1;
	CCSprite* wheel2;
	CCSprite* wheel3;

	CCLabelBMFont* pLabel;

	int changeIndex;
};