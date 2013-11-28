#include "ControlLayer.h"

bool ControlLayer::init()
{
	if (!CCLayer::init())
		return false;

	CCKeyboardDispatcher::SharedKeyboardDispatcher()->addDelegate(this);


	return true;
}

void ControlLayer::OnKeyDown(VirtualKey key)
{
	if (key == VirtualKey::Left)
	{
		KeyBoardInput::SharedInput()->inputX = -9;
	}
	else if (key == VirtualKey::Right)
	{
		KeyBoardInput::SharedInput()->inputX = 9;
	}
}

void ControlLayer::OnKeyUp()
{
	KeyBoardInput::SharedInput()->inputX = 0;
}