#pragma once

#include "BlockBase.h"

class MissBlock : public BlockBase
{
public:
	CREATE_FUNC(MissBlock);
	virtual bool init();

public:
	virtual void OnPlayOn();
	virtual void CheckMoveOut(int status);

	void BlockCrash();
	void BlockCrashOver();
};