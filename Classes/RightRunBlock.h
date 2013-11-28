#pragma once
#include "BlockBase.h"

class RightRunBlock : public BlockBase
{
public:
	CREATE_FUNC(RightRunBlock);

	virtual bool init();

	virtual void OnPlayOn();

	void CheckMoveOut(int status);
};