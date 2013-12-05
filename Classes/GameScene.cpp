#include "GameScene.h"
#include "GameBasic.h"
#include "SimpleAudioEngine.h"
#include "HideLayer.h"
#include "MainScene.h"

using namespace CocosDenshion;

const int Hide_Layer_Tag = 10;

const int Hide_Layer_Menu_Tag = 1;

const int MenuItemTag_Restart = 1;
const int MenuItemTag_Quite = 2;

GameStatus gGameStatus;

GameScene::GameScene()
{
	this->setTag(GAME_SCENE_TAG);
}

GameScene::~GameScene()
{
	// don‘t delete object duplicately
	//delete m_input;
	//delete m_blockLayer;
}

CCScene* GameScene::scene()
{
	CCScene* scene = GameScene::create();
	scene->setTag(WELCOME_SCENE_TAG);

	return scene;
}

bool GameScene::GoBack()
{
	return true;
}

bool GameScene::init()
{
	if(!CCScene::init())
		return false;

	m_backgroundLayer = BackgroundLayer::create();
	this->addChild(m_backgroundLayer, 100);

	//comment is meessy code?
	{
		SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/die.wav");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/flip_on.wav");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/hurt.wav");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/normal_on.wav");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/miss_on.wav");
	}

	gGameStatus = GAME_START;

	m_input = new TouchInput();
	this->addChild(m_input, 100);

	m_controllLayer = ControlLayer::create();
	this->addChild(m_controllLayer);

	StartPlayer();
	startBlock();

	scheduleUpdate();

	return true;
}

void GameScene::StartPlayer()
{
	Player::SharedPlayer()->setmInput(m_input);
	Player::SharedPlayer()->setmInput2(KeyBoardInput::SharedInput());
	Player::SharedPlayer()->ResetPosition();

	this->addChild(Player::SharedPlayer(), 10);
}

void GameScene::startBlock()
{
	m_blockLayer = new BlockFactory();
	this->addChild(m_blockLayer);

	m_blockLayer->CreateFirtBlock();
}

void GameScene::CreateBlockUpdate(float dt)
{
	
}

void GameScene::update(float dt)
{
	if(m_blockLayer->CanGetNextBlockPosition())
	{
		m_blockLayer->CreateBlock();

		m_blockLayer->RemoveUnUsedBlock();
	}

	if (gGameStatus == GAME_OVER)
		return;

	int index = m_blockLayer->getBlockCount() / 5;
	if(index != m_hasDownedFloor)
	{
		m_hasDownedFloor = index;

		m_backgroundLayer->UpdateFloorValue(m_hasDownedFloor);
	}
}


void GameScene::GameOver()
{
	Player::SharedPlayer()->stopAllActions();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	HideLayer* layer = HideLayer::create();
	layer->setTag(Hide_Layer_Tag);

	{
		CCMenuItemImage* restartBtn = CCMenuItemImage::create("btn_restart.png", "btn_restart.png", this, menu_selector(GameScene::Menu_Handler));
		restartBtn->setTag(MenuItemTag_Restart);

		CCMenuItemImage* quiteBtn = CCMenuItemImage::create("btn_quit.png", "btn_quit.png", this, menu_selector(GameScene::Menu_Handler));
		quiteBtn->setTag(MenuItemTag_Quite);

		CCMenu* menu = CCMenu::create(restartBtn, quiteBtn, NULL);
		menu->alignItemsVerticallyWithPadding(50);
		menu->setTag(Hide_Layer_Menu_Tag);
		menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

		layer->addChild(menu);
	}

	this->addChild(layer, 101);

	gGameStatus = GAME_OVER;
}


void GameScene::Menu_Handler(CCObject* sender)
{
	unscheduleUpdate();

	m_blockLayer->StopBlock();

	this->removeChild(Player::SharedPlayer());
	Player::PurgePlayer();


	CCLayer* hideLayer = (CCLayer*)this->getChildByTag(Hide_Layer_Tag);
	hideLayer->removeChildByTag(Hide_Layer_Menu_Tag);

	this->removeChild(hideLayer);

	CCMenuItem* item = (CCMenuItem*)sender;
	switch (item->getTag())
	{
	case MenuItemTag_Restart:
		{
			CCDirector::sharedDirector()->replaceScene(GameScene::scene());
		}
		break;
	case MenuItemTag_Quite:
		{
			CCDirector::sharedDirector()->replaceScene(MainScene::scene());
		}
		break;
	default:
		break;
	}
}

void GameScene::UpdateBloodValue(float percent)
{
	m_backgroundLayer->UpdateBloodValue(percent);
}
