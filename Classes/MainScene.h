#include "IBackableScene.h"
#include "GameOptionScene.h"

class MainScene : public IBackableScene
{
public:
	static CCScene* scene();

	CREATE_FUNC(MainScene);

	bool GoBack();
};

class MainLayer : public CCLayer
{
public:
	CREATE_FUNC(MainLayer);

	bool init();

public:
	void StartGame(CCObject* sender);

	void GameOption(CCObject* sender);
};