#include "FlipBlock.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool FlipBlock::init()
{
	if(!initWithSpriteFrameName("tan1.png"))
		return false;



	return true;
}

void FlipBlock::OnPlayOn()
{
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/flip_on.wav");
	Player::SharedPlayer()->Flip();

	shouldCheckPlayon = true;
}

void FlipBlock::CheckMoveOut(int status)
{
	if(status == -1)
	{

	}
}