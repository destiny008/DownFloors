#pragma once

#include "cocos2d.h"
#include "IBackableScene.h"
#include "BlockFactory.h"
#include "Player.h"
#include "BaseInput.h"
#include "TouchInput.h"
#include "ControlLayer.h"
#include "BackgroundLayer.h"

USING_NS_CC;

class GameScene : public IBackableScene
{
public:
	GameScene();
	~GameScene();

	static CCScene* scene();

	CREATE_FUNC(GameScene);

	virtual bool init();

	virtual void update(float dt);

	bool GoBack();

public:
	void StartPlayer();
	void startBlock();

	void CreateBlockUpdate(float dt);

	void GameOver();

	void UpdateBloodValue(float percent);

public:

	void Menu_Handler(CCObject* sender);

private:

	Player* m_player;
	ControlLayer* m_controllLayer;
	BackgroundLayer* m_backgroundLayer;

	BlockFactory* m_blockLayer;
	BaseInput* m_input;

	int m_hasDownedFloor;

};