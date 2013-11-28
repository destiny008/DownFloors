#pragma once

#include "BlockBase.h"

class ThornBlock : public BlockBase
{
public:

	CREATE_FUNC(ThornBlock);

	virtual bool init();

	virtual void OnPlayOn();

	float GetPlatformTop();

	void CheckMoveOut(int status);
};