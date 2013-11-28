#include "StartScene.h"
#include "MainScene.h"

CCScene* StartScene::scene()
{
	CCScene* scene = StartScene::create();
	scene->setTag(WELCOME_SCENE_TAG);

	StartLayer* layer = StartLayer::create();
	scene->addChild(layer, 0);

	return scene;
}

bool StartScene::GoBack()
{
	return false;
}

const int AllResourcesCount = 1;
static int g_loadedResourcesCount = 0;

const float wheel1Speed = 30;
const float wheel2Speed = 150;
const float wheel3Speed = 75;

bool StartLayer::init()
{
	if(!CCLayer::init())
		return false;

	changeIndex = 0;
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();	

	scheduleOnce(schedule_selector(StartLayer::InitGameResourceAsync), 0.1);

	return true;
}

void StartLayer::InitAnimation()
{
	
}


void StartLayer::InitGameResourceAsync(float delayTime)
{
	CCTextureCache::sharedTextureCache()->addImageAsync("GameResources.png", this, callfuncO_selector(StartLayer::InitGameResourceCallBack));
}

void StartLayer::InitGameResourceCallBack(CCObject* sender)
{
	g_loadedResourcesCount++;
	if(g_loadedResourcesCount >= AllResourcesCount)
	{
		InitAnimation();
		//LoadUserSettings();

		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1, MainScene::scene()));
	}
}

void StartLayer::LoadUserSettings()
{
	IfOpenMusic = CCUserDefault::sharedUserDefault()->getBoolForKey(Key_IfOpenMusic, true);
}