#include "Enemy.h"

EnemySprite::EnemySprite()
	: pEnemySprite(NULL)
{

}

EnemySprite::~EnemySprite()
{

}

void EnemySprite::setEnemyByType( EnemyType enType )
{
	switch (enType)
	{
	case Enemy1:
		pEnemySprite = Sprite::create("ui/shoot/enemy1.png");         //createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1.png"));
		nLife = ENEMY1_MAXLIFE;
		break;
	case Enemy2:
		pEnemySprite = Sprite::create("ui/shoot/enemy2.png");         //createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
		nLife = ENEMY2_MAXLIFE;
		break;
	case Enemy3:
		pEnemySprite = Sprite::create("ui/shoot/enemy3.png");        //createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		nLife = ENEMY3_MAXLIFE;
		break;
	case Enemy4:
		pEnemySprite = Sprite::create("ui/shoot/enemy4.png");        //createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		nLife = ENEMY4_MAXLIFE;
		break;
	case Enemy5:
		pEnemySprite = Sprite::create("ui/shoot/enemy5.png");        //createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		nLife = ENEMY5_MAXLIFE;
		break;
	default:
		return;
		break;
	}

	this->addChild(pEnemySprite);
	Size winSize = Director::getInstance()->getWinSize();
	Size enemySize = pEnemySprite->getContentSize();
	int minX=enemySize.width/2;
	int maxX=winSize.width - enemySize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX) + minX;

	// 设置敌机Node方位 Node包含Sprite
	this->setPosition(Point(actualX, winSize.height + enemySize.height/2));
}

bool EnemySprite::init()
{
	bool pRet = true;
	if (!Node::init())
	{
		pRet = false;
	}

	return pRet;
}

Sprite* EnemySprite::getSprite()
{
	return pEnemySprite;
}

int EnemySprite::getLife()
{
	return nLife;
}

void EnemySprite::loseLife()
{
	--nLife;
}

Rect EnemySprite::getBoundingBox()
{
	Rect rect=pEnemySprite->boundingBox();  
	Point pos=this->convertToWorldSpace(rect.origin);  
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);  
	return enemyRect;  
}

