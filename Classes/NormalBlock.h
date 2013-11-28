#include "BlockBase.h"
#include "cocos2d.h"

USING_NS_CC;

class NormalBlock : public BlockBase
{
public:
	CREATE_FUNC(NormalBlock);

	virtual bool init();

	virtual void OnPlayOn();

	virtual void CheckMoveOut(int status);
};