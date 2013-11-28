#include "BlockFactory.h"
#include "Player.h"

static BlockFactory *s_SharedFactory = NULL;

const int BLOCK_SPACE = 150;
const int BLOCK_POSITION_COUNT = 11;



BlockFactory::BlockFactory()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	site = new int[BLOCK_POSITION_COUNT];;

	site[0] = winSize.width / 2;
	site[1] = 128;
	site[2] = 190;
	site[3] = 260;
	site[4] = 340;
	site[5] = 464;
	site[6] = 524;
	site[7] = 650;
	site[8] = 570;
	site[9] = 610;
	site[10] = 640;


	cc_timeval psv;   

	// 计算时间种子
	CCTime::gettimeofdayCocos2d( &psv, NULL );

	// 初始化随机数
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;    

	srand( tsrans ); 
}

BlockFactory::~BlockFactory()
{
	
}

void BlockFactory::CreateBlock()
{
	BlockBase* block = NULL;

	//随机方块类型.
	int randomBlock = floor(CCRANDOM_0_1() * 100);
	if(randomBlock <= 70)
	{
		block = NormalBlock::create();
	}
	else if(randomBlock <= 80)
	{
		block = MissBlock::create();
	}
	else if(randomBlock <= 85)
	{
		block = FlipBlock::create();
	}
	else if(randomBlock <= 90)
	{
		block = LeftRunBlock::create();
	}
	else if(randomBlock <= 95)
	{
		block = RightRunBlock::create();
	}
	else
	{
		block = ThornBlock::create();
	}
	//block = MissBlock::create();

	//随机方块位置
	int randomPosition = floor(CCRANDOM_0_1() * BLOCK_POSITION_COUNT);

	m_targetPosition = ccp(site[randomPosition], m_targetPosition.y);
	this->AddBlock(block, m_targetPosition);

	blockCount++;
}

void BlockFactory::CreateFirtBlock()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	m_targetPosition = ccp(winSize.width / 2, 250);

	BlockBase* block = NormalBlock::create();
	this->AddBlock(block, m_targetPosition);

	blockCount = 1;
}

bool BlockFactory::CanGetNextBlockPosition()
{
	BlockBase* lastBlock = allBlockes.back();

	float y  = lastBlock->getPositionY();
	if(y > -100)
	{
		m_targetPosition.y = y - BLOCK_SPACE;

		return true;
	}

	return false;
}

void BlockFactory::RemoveUnUsedBlock()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	BlockBase* firstBlock = allBlockes.front();

	if(firstBlock->getPositionY() > winSize.height + 20)
	{
		firstBlock->End();
		RemoveBlock(firstBlock);
	}
}

void BlockFactory::AddBlock(BlockBase* block, CCPoint pos)
{
	block->setPosition(pos);

	this->addChild(block);
	allBlockes.push(block);

	//block.onCheckPlayerOn = function(){return this.checkPlayerOn(_this.player);}
	//block.onPlayOn = function(){this.playOn(_this.player);}
	//block.onCheckMoveOut = function(){this.checkMoveOut(_this.player);}
	//block.onEnd = function(){_this.blockList.remove(this);}
	//	
	//block.animation();
}

void BlockFactory::RemoveBlock(BlockBase* block)
{
	allBlockes.pop();

	this->removeChild(block);
}

void BlockFactory::StopBlock()
{
	unscheduleUpdate();

	delete site;
}