#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Player;

class BlockBase : public CCSprite
{
public:
	BlockBase();
	~BlockBase();

public:
	void Animation();

	virtual void update(float dt);


	int CheckPlayerOn();

	void End();
	void StopMove();

	virtual void OnEnd(){}
	//virtual void PlayerOn(Player* player) = 0;
	//virtual void CheckMoveOut(Player* player) = 0;

	virtual void OnCheckMoveOut(int status);
	virtual void CheckMoveOut(int status) = 0;

	//virtual void OnCheckPlayerOn() = 0;
	virtual void OnPlayOn() = 0;

	virtual float GetPlatformTop();

	bool IfInXSection();

protected:
	bool hasCheckMove; //���������Ƿ���ƽ̨��.
	float m_movepx, m_movepy;

	bool shouldCheckPlayon; //�������ƽ̨�Ƿ���Ҫ�������Ƿ���������.
private:
	
	
};