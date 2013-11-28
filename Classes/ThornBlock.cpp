#include "ThornBlock.h"
#include "Player.h"


bool ThornBlock::init()
{
	if(!initWithSpriteFrameName("ci.png"))
		return false;

	return true;
}

void ThornBlock::OnPlayOn()
{
	Player::SharedPlayer()->Hurt(1);

	Player::SharedPlayer()->MoveUp(0, m_movepy);
	hasCheckMove = true;
}

float ThornBlock::GetPlatformTop()
{
	return getPositionY() - 2;
}

void ThornBlock::CheckMoveOut(int status)
{
	
}