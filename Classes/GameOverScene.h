#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public Layer 
{
public:
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOverLayer);

public:
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuBackCallback1(cocos2d::Ref* pSender);
};