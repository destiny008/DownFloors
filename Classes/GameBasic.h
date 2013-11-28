#pragma once

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;

enum DirectState 
{
	LEFT = 0, 
	RIGHT,
	STAND
};

enum GameStatus
{
	GAME_START,
	GAME_ING,
	GAME_OVER,
};


const char MSG_CHECK_PATTERN[] = "MSG_CHECK_PATTERN";
const char MSG_SWAP_PATTERN[] = "MSG_SWAP_PATTERN";


//GameScene Tag.
const int WELCOME_SCENE_TAG = 1;
const int GAME_SCENE_TAG = 2;
const int Main_SCENE_TAG = 3;
const int Option_SCENE_TAG = 4;


//IsolateStorage Keys.
const char Key_IfOpenMusic[] = "Key_IfOpenMusic";

static bool IfOpenMusic;

const int Player_TotalBloodValue = 5;
const int ThornBlock_HurtValue = 1;
const int Top_HurtValue = 2;



class CovertTool
{
public:

	static char* G2U(const char* gb2312)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr)
			delete[] wstr;
		return str;
	}
};
