#include "Player.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const float GAcceleration = 1;

const float PlayerXSpeed = 0;
const float PlayerYSpeed = 0;

const float PlayerFlipSpeed = 15;

static Player* g_sharedPlayer = NULL;

extern GameStatus gGameStatus;

Player* Player::SharedPlayer()
{
	if(!g_sharedPlayer)
	{
		g_sharedPlayer = new Player();
		g_sharedPlayer->init();
	}

	return g_sharedPlayer;
}

void Player::PurgePlayer()
{
	delete g_sharedPlayer;
	g_sharedPlayer = NULL;
}

Player::Player():
	m_currentBloodValue(Player_TotalBloodValue)
{

}

Player::~Player()
{
	CC_SAFE_RELEASE(walk_Right_Animate);
	CC_SAFE_RELEASE(flip_Animate);
}

bool Player::init()
{
	if(!initWithSpriteFrameName("stand.png"))
		return false;

	isFlip = false;
	ySpeed = PlayerYSpeed;
	xSpeed = PlayerXSpeed;

	InitAnimation();

	m_state = Move_Down;

	scheduleUpdate();

	ResetPosition();

	//this->setFlipX(true);
	//this->runAction(walk_Right_Animate);

	return true;
}

void Player::InitAnimation()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	CCAnimation* runAnim = CCAnimation::create();
	char str[64] = {0};

	//Right.
	{
		runAnim = CCAnimation::create();

		for (int i = 0; i <= 2; i++) 
		{
			sprintf(str, "move_right%d.png", i);

			CCSpriteFrame* frame = cache->spriteFrameByName(str);
			runAnim->addSpriteFrame(frame);
		}
		runAnim->setDelayPerUnit(0.04f);
		runAnim->setRestoreOriginalFrame(true);

		walk_Right_Animate = CCRepeatForever::create(CCAnimate::create(runAnim));
		walk_Right_Animate->retain();
	}

	//Up.
	{
		runAnim = CCAnimation::create();

		for (int i = 0; i <= 1; i++) 
		{
			sprintf(str, "move_up%d.png", i);

			CCSpriteFrame* frame = cache->spriteFrameByName(str);
			runAnim->addSpriteFrame(frame);
		}
		runAnim->setDelayPerUnit(0.04f);
		runAnim->setRestoreOriginalFrame(true);

		flip_Animate = CCRepeatForever::create(CCAnimate::create(runAnim));
		flip_Animate->retain();
	}
}

void Player::update(float dt)
{
	if (gGameStatus == GAME_OVER)
		return;

	float inputX = 0;
	if (m_Input->inputX == 0)
	{
		inputX = m_Input2->inputX;
	}
	else
	{
		inputX = m_Input->inputX;
	}

	switch (m_state)
	{
	case Move_Up:
		{
			
		}
		break;
	case Move_Down:
		{
			ySpeed += GAcceleration;
		}
		break;
	case Move_Flip:
		{
			ySpeed += GAcceleration;

			if(ySpeed >= 0)
			{
				isFlip = false;

				MoveDown();
				return;
			}
		}
		break;
	default:
		break;
	}

	float y = this->getPositionY() - ySpeed;
	float x = this->getPositionX() + inputX + xSpeed;

	
	if(inputX > 0)
	{
		Run(RIGHT);
	}
	else if(inputX < 0)
	{
		Run(LEFT);
	}
	else
	{
		Run(STAND);
	}
	
	int w = getContentSize().width/2;
	int h = getContentSize().height/2;

	if(y >= 1120) //到达顶部
	{
		Hurt(2);
	}
	else if(y <= -h) //到达底部.
	{
		Die();
	}

	//左右不要超出界外.
	if(x < w + 29)
	{
		x = w + 29;
	}
	else if(x > 768 - 29 -w)//还要减去墙壁的宽度
	{
		x = 768 - 29 -w;
	}
	this->setPosition(ccp(x, y));
}

void Player::ResetPosition()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	setPosition(ccp(size.width / 2, size.height / 2 + 300));
}

CCPoint Player::GetNextPosition()
{
	float x = this->getPositionX() + xSpeed ;
	float y = this->getPositionY() - ySpeed - GAcceleration / 2;

	return ccp(x, y);
}

void Player::MoveUp(float x, float y)
{
	m_state = Move_Up;

	ySpeed = - y;
	xSpeed = x;
}

void Player::MoveDown()
{
	m_state = Move_Down;

	ySpeed = PlayerYSpeed;
}

void Player::Flip()
{
	if(isFlip)
		return;

	isFlip = true;

	ySpeed = -PlayerFlipSpeed;
	xSpeed = 0;

	m_state = Move_Flip;
}

void Player::Run(DirectState direction)
{
	if(direction != mDir)
	{
		if(direction == LEFT)
		{
			mDir = LEFT;
			this->setFlipX(true);

			this->stopAllActions();
			if(m_state == Move_Up)
			{
				this->runAction(walk_Right_Animate);
			}
			else
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("move_right0.png"));
			}
		}
		else if(direction == RIGHT)
		{
			mDir = RIGHT;
			this->setFlipX(false);

			this->stopAllActions();
			if(m_state == Move_Up)
			{
				this->runAction(walk_Right_Animate);
			}
			else
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("move_right0.png"));
			}
		}
		else
		{
			mDir = STAND;

			this->stopAllActions();
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("stand.png"));
		}
	}
}

void Player::Hurt(float amount)
{
	if (amount > 0)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/hurt.wav");
	}

	GameScene* father = (GameScene*)this->getParent();

	m_currentBloodValue -= amount;

	if (m_currentBloodValue <= 0)
		m_currentBloodValue = 0;
	else if (m_currentBloodValue >= Player_TotalBloodValue)
		m_currentBloodValue = Player_TotalBloodValue;
		
	father->UpdateBloodValue(m_currentBloodValue*1.0/Player_TotalBloodValue);

	if(m_currentBloodValue <= 0)
	{
		Die();
	}
	else
	{
		
	}

	
	

	if(amount == 1)
	{

	}
}

void Player::Die()
{
	if(m_state != DIED)
	{
		m_state = DIED;

		SimpleAudioEngine::sharedEngine()->playEffect("sounds/die.wav");

		GameScene* father = (GameScene*)this->getParent();
		father->GameOver();
	}
}