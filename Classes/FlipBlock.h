#pragma once

#include "BlockBase.h"

class FlipBlock : public BlockBase
{
public:

	CREATE_FUNC(FlipBlock);

	virtual bool init();

	virtual void OnPlayOn();

	virtual void CheckMoveOut(int status);
};