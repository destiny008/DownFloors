#include "GameOptionScene.h"
#include "MainScene.h"

CCScene* GameOptionScene::scene()
{
	CCScene* scene = GameOptionScene::create();
	scene->setTag(Option_SCENE_TAG);

	GameOptionLayer* layer = GameOptionLayer::create();
	scene->addChild(layer, 0);

	return scene;
}

bool GameOptionScene::GoBack()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1, MainScene::scene()));

	return true;
}



bool GameOptionLayer::init()
{
	if (!CCLayer::init())
		return false;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);


	return true;
}