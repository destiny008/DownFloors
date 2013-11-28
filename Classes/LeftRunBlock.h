#pragma once
#include "BlockBase.h"

class LeftRunBlock : public BlockBase
{
public:
	CREATE_FUNC(LeftRunBlock);

	virtual bool init();

	virtual void OnPlayOn();

	void CheckMoveOut(int status);
};