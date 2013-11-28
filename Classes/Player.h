#pragma once

#include "cocos2d.h"
#include "BaseInput.h"
#include "GameBasic.h"

USING_NS_CC;

enum PlyerMovingState
{
	Move_Up,
	Move_Down,
	Move_Flip,
	DIED
};

class Player : public CCSprite
{
public:
	Player();
	~Player();

	static Player* SharedPlayer();
	static void PurgePlayer();

	virtual bool init();
	virtual void update(float dt);

	void InitAnimation();

public:
	void ResetPosition();

	CCPoint GetNextPosition();

	void MoveUp(float speedX, float speedY);
	void MoveDown();
	void Flip();
	void Run(DirectState dir);

	void Hurt(float amount);
	void Die();

public:
	bool isFlip;

	CC_SYNTHESIZE(float, ySpeed, YSpeed);
	CC_SYNTHESIZE(float, xSpeed, XSpeed);

	CC_SYNTHESIZE(BaseInput*, m_Input, mInput);
	CC_SYNTHESIZE(BaseInput*, m_Input2, mInput2);

private:
	PlyerMovingState m_state;

	DirectState mDir;

	CCAction* walk_Right_Animate;
	CCAction* flip_Animate;
	int m_currentBloodValue;
};