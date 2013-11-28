#include "KeyBoardInput.h"

static KeyBoardInput* g_SharedInput = NULL;

KeyBoardInput* KeyBoardInput::SharedInput()
{
	if (!g_SharedInput)
	{
		g_SharedInput = new KeyBoardInput();
		g_SharedInput->init();
	}

	return g_SharedInput;
}

