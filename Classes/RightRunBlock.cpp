#include "RightRunBlock.h"
#include "Player.h"


bool RightRunBlock::init()
{
	if(!initWithSpriteFrameName("move_q1.png"))
		return false;

	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("RightBlockAnimation");
	
	CCAnimate* animate = CCAnimate::create(animation);
	this->runAction(CCRepeatForever::create(animate));

	return true;
}

void RightRunBlock::OnPlayOn()
{
	Player::SharedPlayer()->MoveUp(m_movepx, m_movepy);
	hasCheckMove = true;
}

void RightRunBlock::CheckMoveOut(int status)
{
	if(status == -1)
	{
		Player::SharedPlayer()->setXSpeed(0);
	}
}