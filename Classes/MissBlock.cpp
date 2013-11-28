#include "MissBlock.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const int Block_CrashAction_Tag = 1;

void MissBlock::OnPlayOn()
{
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/miss_on.wav");

	Player::SharedPlayer()->MoveUp(0, m_movepy);
	hasCheckMove = true;

	CCAnimation* blockMissAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("blockMissAnimation");
	CCAnimate* animate = CCAnimate::create(blockMissAnimation);

	CCAction* action = CCSequence::create(CCDelayTime::create(1), animate, CCCallFunc::create(this, callfunc_selector(MissBlock::BlockCrashOver)), NULL);
	this->runAction(action);

	//基本是动画结束之后就掉落，时间要算好.
	CCAction* moveDown = CCSequence::create(CCDelayTime::create(1.1), CCCallFunc::create(this, callfunc_selector(MissBlock::BlockCrash)), NULL);
	moveDown->setTag(Block_CrashAction_Tag);
	this->runAction(moveDown);
}

bool MissBlock::init()
{
	if(!initWithSpriteFrameName("plat1.png"))
		return false;

	return true;
}

void MissBlock::CheckMoveOut(int status)
{
	if(status == -1)
	{
		//如果离开了这个平台的话就要取消降落的操作，否则刚到第二个台上就会掉下.
		CCActionInterval* action = dynamic_cast<CCActionInterval*>(this->getActionByTag(Block_CrashAction_Tag));
		if(action->getElapsed() <= 1.1)
		{
			shouldCheckPlayon = false;
			this->stopActionByTag(Block_CrashAction_Tag);
		}
	}
}

void MissBlock::BlockCrash()
{
	hasCheckMove = false;
	shouldCheckPlayon = false;

	Player::SharedPlayer()->MoveDown();
}

void MissBlock::BlockCrashOver()
{
	this->setVisible(false);
}