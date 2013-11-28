#pragma once

#include "BaseInput.h"

class KeyBoardInput : public BaseInput
{
public:
	static KeyBoardInput* SharedInput();
};
