#include "NormalBlock.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool NormalBlock::init()
{
	if(!CCSprite::initWithSpriteFrameName("normal.png"))
		return false;

	return true;
}

void NormalBlock::OnPlayOn()
{
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/normal_on.wav");
	Player::SharedPlayer()->MoveUp(0, m_movepy);

	Player::SharedPlayer()->Hurt(-1);

	hasCheckMove = true;
}

void NormalBlock::CheckMoveOut(int status)
{
	
}