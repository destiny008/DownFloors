#pragma once

#include "cocos2d.h"
#include "FlipBlock.h"
#include "ThornBlock.h"
#include "MissBlock.h"
#include "NormalBlock.h"
#include "LeftRunBlock.h"
#include "RightRunBlock.h"
#include <queue>

USING_NS_CC;
using namespace std;

class Player;

class BlockFactory : public CCLayer
{
public:
	BlockFactory();
	~BlockFactory();

public:
	void CreateBlock();

	bool CanGetNextBlockPosition();

	void CreateFirtBlock();

	void RemoveUnUsedBlock();

	void AddBlock(BlockBase* block, CCPoint pos);

	void RemoveBlock(BlockBase* block);

	void StopBlock();

public:

	CC_SYNTHESIZE(int, blockCount, BlockCount);

	CCPoint m_targetPosition;

	queue<BlockBase*> allBlockes;

private:
	int* site;
};