#include "MainScene.h"
#include "GameScene.h"

CCScene* MainScene::scene()
{
	CCScene* scene = MainScene::create();
	scene->setTag(Main_SCENE_TAG);

	MainLayer* layer = MainLayer::create();
	scene->addChild(layer, 0);

	return scene;
}

bool MainScene::GoBack()
{
	return false;
}


bool MainLayer::init()
{
	if(!CCLayer::init())
		return false;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(bg);

	CCMenuItemImage* startBtn = CCMenuItemImage::create("btn_bg.png", "btn_bg2.png", this, menu_selector(MainLayer::StartGame));
	CCMenuItemImage* optionBtn = CCMenuItemImage::create("btn_option.png", "btn_option2.png", this, menu_selector(MainLayer::GameOption));
	//CCMenuItemImage* aboutBtn = CCMenuItemImage::create("btn_bg.png", "btn_bg.png", this, menu_selector(MainLayer::StartGame));

	CCMenu* menu = CCMenu::create(startBtn, NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(ccp(visibleSize.width - 180, visibleSize.height - 180));

	this->addChild(menu);


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameResources.plist");

	CCAnimation* blockMissAnimation = CCAnimation::create();
	blockMissAnimation->setDelayPerUnit(0.016f);

	char frameName[20];

	//add Miss Block Animation to the cache.
	for(int i = 1; i <= 6; i++)
	{
		sprintf(frameName, "plat%d.png", i);

		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
		blockMissAnimation->addSpriteFrame(frame);
	}
	CCAnimationCache::sharedAnimationCache()->addAnimation(blockMissAnimation, "blockMissAnimation");

	//add left-run-block animation to the cache.
	blockMissAnimation = CCAnimation::create();
	blockMissAnimation->setDelayPerUnit(0.016f);

	for(int i = 1; i <= 9; i++)
	{
		sprintf(frameName, "move_p%d.png", i);

		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
		blockMissAnimation->addSpriteFrame(frame);
	}
	CCAnimationCache::sharedAnimationCache()->addAnimation(blockMissAnimation, "LeftBlockAnimation");

	//add right-run-block Animation to the cache.
	blockMissAnimation = CCAnimation::create();
	blockMissAnimation->setDelayPerUnit(0.016f);

	for(int i = 1; i <= 9; i++)
	{
		sprintf(frameName, "move_q%d.png", i);

		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
		blockMissAnimation->addSpriteFrame(frame);
	}
	CCAnimationCache::sharedAnimationCache()->addAnimation(blockMissAnimation, "RightBlockAnimation");


	return true;
}

void MainLayer::StartGame(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1, GameScene::scene()));
}

void MainLayer::GameOption(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1, GameOptionScene::scene()));
}