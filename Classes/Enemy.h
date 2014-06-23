/***********************************************

  ��Ϊ�з��ɻ���������ֵ�����ԣ���Ҫ��������

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