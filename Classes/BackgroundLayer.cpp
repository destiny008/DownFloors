#include "BackgroundLayer.h"
#include "GameBasic.h"

bool BackgroundLayer::init()
{
	if (!CCLayer::init())
		return false;


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//���ǽ�ںͶ�����װ��.
	{
		CCSprite* topCi = CCSprite::create("TopCi.png");
		topCi->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 95));
		this->addChild(topCi);

		CCSprite* leftWall = CCSprite::createWithSpriteFrameName("pang.png");

		float halfWidth = leftWall->getContentSize().width / 2;

		leftWall->setPosition(ccp(halfWidth, visibleSize.height / 2));
		this->addChild(leftWall);

		CCSprite* rightWall = CCSprite::createWithSpriteFrameName("pang.png");
		rightWall->setPosition(ccp(visibleSize.width - halfWidth, visibleSize.height / 2));
		this->addChild(rightWall);
	}


	//��Ӷ���Ѫ������ʾ.
	{
		CCSprite* top_bg = CCSprite::create("Top_bg.png");
		top_bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height - top_bg->getContentSize().height / 2));
		this->addChild(top_bg);

		CCSprite* blood_bg = CCSprite::create("blood_bg.png");
		blood_bg->setPosition(ccp(blood_bg->getContentSize().width / 2 + 30, 40));
		top_bg->addChild(blood_bg);

		blood = CCSprite::create("blood.png");
		blood->setAnchorPoint(ccp(0, 0.5));
		blood->setPosition(ccp(107, 40));
		top_bg->addChild(blood);

		initBloodSize = blood->getContentSize();


		floorFont = CCLabelBMFont::create(CovertTool::G2U("�� 1 ��"), "fonts/gameFont.fnt");
		floorFont->setScale(0.5);
		floorFont->setPosition(ccp(640, 40));
		top_bg->addChild(floorFont);
	}

	return true;
}

void BackgroundLayer::UpdateBloodValue(float percent)
{
	CCSize visibleSize = ccp(initBloodSize.width * percent, initBloodSize.height);

	blood->setTextureRect(CCRectMake(0, 0, visibleSize.width, visibleSize.height));
}


void BackgroundLayer::UpdateFloorValue(int floor)
{
	char des[20];
	sprintf(des, "�� %d ��", floor);

	floorFont->setString(CovertTool::G2U(des));
}