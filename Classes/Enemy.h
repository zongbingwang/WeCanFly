/***********************************************

  因为敌方飞机具有生命值等特性，需要附加属性

************************************************/
#include "cocos2d.h"
#include "EnemyDefine.h"

USING_NS_CC;


class EnemySprite : public Node
{
public:
	EnemySprite();
	~EnemySprite();
	virtual bool init();
	CREATE_FUNC(EnemySprite);

public:
	void setEnemyByType(EnemyType enType);
	Sprite* getSprite();

	int getLife();
	void loseLife();
	Rect getBoundingBox();

private:
	Sprite *pEnemySprite;
	int nLife;
};