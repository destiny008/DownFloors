#include "LeftRunBlock.h"
#include "Player.h"


bool LeftRunBlock::init()
{
	if(!initWithSpriteFrameName("move_p1.png"))
		return false;

	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("LeftBlockAnimation");
	
	CCAnimate* animate = CCAnimate::create(animation);
	this->runAction(CCRepeatForever::create(animate));

	return true;
}

void LeftRunBlock::OnPlayOn()
{
	Player::SharedPlayer()->MoveUp(-m_movepx, m_movepy);

	hasCheckMove = true;
}

void LeftRunBlock::CheckMoveOut(int status)
{
	if(status == -1)
	{
		Player::SharedPlayer()->setXSpeed(0);
	}
}