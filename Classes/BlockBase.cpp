#include "BlockBase.h"
#include "BlockFactory.h"
#include "Player.h"

extern GameStatus gGameStatus;

BlockBase::BlockBase()
	:m_movepx(3),
	 m_movepy(2),
	 hasCheckMove(false),
	 shouldCheckPlayon(true)
{
	scheduleUpdate();
}

BlockBase::~BlockBase()
{

}

void BlockBase::Animation()
{

}

void BlockBase::update(float dt)
{
	float x = this->getPositionX();
	float y = this->getPositionY() + m_movepy;

	this->setPosition(ccp(x, y));

	int status = -2;
	if(shouldCheckPlayon)
	{
		status = CheckPlayerOn();

		if(status > 0)
		{
			OnPlayOn();
		}
	}

	//只有已经在平台上菜需要判断方块上的左右移动.
	if(hasCheckMove)
	{
		if(status == -2) // 还是初始值，说明没有检测是否在上面，需要额外检测一次.
		{
			status = IfInXSection() ? 0 : -1;
		}

		OnCheckMoveOut(status);
	}
}

//-1 不在x和y, 0 在x内， 1在x,y内.
int BlockBase::CheckPlayerOn()
{
	if (gGameStatus == GAME_OVER)
		return -1;

	Player* player = Player::SharedPlayer();

	if(player->isFlip)
	{
		return -1;
	}
	
	//X没有超出.
	if(IfInXSection())
	{
		float topPlatY = GetPlatformTop();
		float bottomPlatY = this->getPositionY() - getContentSize().height / 2;

		float nextTopPlatY = topPlatY + m_movepy;
		
		float bottomPlayerY = player->getPositionY() - player->getContentSize().height / 2;
		float nexBottomPlayerY = player->GetNextPosition().y - player->getContentSize().height / 2;

		//Y下一帧即将触碰.
		if(bottomPlayerY >= bottomPlatY && nexBottomPlayerY <= nextTopPlatY)
		{
			float y = topPlatY + player->getContentSize().height / 2;
			player->setPositionY(y);

			shouldCheckPlayon = false;

			return 1;
		}

		return 0;
	}

	return -1;
}

void BlockBase::StopMove()
{
	unscheduleUpdate();
}

void BlockBase::End()
{
	StopMove();

	OnEnd();
}


void BlockBase::OnCheckMoveOut(int status) 
{
	if(status == -1)
	{
		Player::SharedPlayer()->MoveDown();

		hasCheckMove = false;
		shouldCheckPlayon = false;
	}

	CheckMoveOut(status);
}

void BlockBase::OnPlayOn() { }


bool BlockBase::IfInXSection()
{
	Player* player = Player::SharedPlayer();

	float leftPlatX = this->getPositionX() - getContentSize().width / 2;
	float rightPlatX = this->getPositionX() + getContentSize().width / 2;

	float leftPlayerX = player->getPositionX() - player->getContentSize().width/2;
	float rightPlayerX = player->getPositionX() + player->getContentSize().width/2;

	if(rightPlayerX > leftPlatX && leftPlayerX  < rightPlatX)
	{
		return true;
	}

	return false;
}

float BlockBase::GetPlatformTop()
{
	return this->getPositionY() + getContentSize().height / 2;
}