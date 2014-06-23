#include "GameScene.h"
#include "SimpleAudioEngine.h"


cocos2d::Scene* GameLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GameLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 启动触摸机制
	this->setTouchEnabled(true);

	if ((CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) == false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();// 恢复
	}

	// 背景无限滚动
	auto backgroundA = Sprite::create("ui/shoot_background/background_game.png");
	backgroundA->setTag(e_BackgroundA);
	backgroundA->setAnchorPoint(Point::ZERO);
	backgroundA->setPosition(Point::ZERO);
	this->addChild(backgroundA);

	auto backgroundB = Sprite::create("ui/shoot_background/background_game.png");
	backgroundB->setTag(e_BackgroundB);
	backgroundB->setAnchorPoint(Point::ZERO);
	backgroundB->setPosition(Point::ZERO);
	this->addChild(backgroundB);

	// 每帧都调用的函数
	this->schedule(schedule_selector(GameLayer::backgroundMove));
	this->schedule(schedule_selector(GameLayer::gameUpdate));
	this->schedule(schedule_selector(GameLayer::enemyBullet),1.0f);

	// 加入飞机
	planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);

	// 开启子弹
	bulletLayer = BulletLayer::create();
	this->addChild(bulletLayer);

	// 加入敌机和分数显示
	enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer);

	// 加入暂停按钮
	controlLayer = ControlLayer::create();
	this->addChild(controlLayer);
}

void GameLayer::backgroundMove(float dt)
{
	Sprite *pBackgroundA = (Sprite*)this->getChildByTag(EnBackground::e_BackgroundA);
	Sprite *pBackgroundB = (Sprite*)this->getChildByTag(EnBackground::e_BackgroundB);


	pBackgroundA->setPositionY(pBackgroundA->getPositionY() - 2);
	pBackgroundB->setPositionY(pBackgroundA->getPositionY() + pBackgroundA->getContentSize().height);
	if (0 == pBackgroundB->getPositionY())
	{
		pBackgroundA->setPositionY(0);
	}
}

void GameLayer::enemyBullet(float dt)
{
	for( auto& eEnemy : enemyLayer->vecEnemy)
	{
		EnemySprite* pEnemySprite = (EnemySprite*)eEnemy;
		char szName[100] = {0};
		sprintf(szName, "ui/shoot/bullet%d.png", pEnemySprite->getTag( ) + 2);
		auto bullet = Sprite::create(szName);
		this->addChild(bullet);
		eneBullet.pushBack(bullet);
		
		Point planePos = pEnemySprite->getPosition();
		Point bulletPos = Point(planePos.x, planePos.y-2*pEnemySprite->getContentSize().height-bullet->getContentSize().height);
		bullet->setPosition(bulletPos);
		
		// 飞行长度 飞行就是超出窗体
		
		float flyLen = bulletPos.y - bullet->getContentSize().height/2;
		float flyVelocity = (320 + (pEnemySprite->getTag() - 1)*100) / 1; //飞行速度
	    float realFlyDuration = flyLen / flyVelocity; // 飞行时间
		auto actionMove=MoveTo::create(realFlyDuration, Point(bulletPos.x,-2*pEnemySprite->getContentSize().height));
		auto actionDone=CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBullet, this));
		
		Sequence* sequence=Sequence::create(actionMove,actionDone,NULL);
		
		bullet->runAction(sequence);
	}

}

void GameLayer::removeBullet( Node* pNode )
{
	if (NULL == pNode)
	{ 
		return;
	}

	Sprite* bullet=(Sprite*)pNode;
	this->removeChild(bullet,true);
	eneBullet.eraseObject(bullet);
}


PlaneLayer* GameLayer::returnPlaneLayer()
{
	return planeLayer;
}

void GameLayer::gameUpdate( float dt )
{
	bool bMoveButt = false;

	//这种for写法是C++ 11的新特性 子弹和敌机对碰
	for( auto& eButtle : bulletLayer->vecBullet)
	{
		Sprite* pBullet=(Sprite*)eButtle; // 获取子弹精灵
		bMoveButt = bulletCollisionEnemy(pBullet);
		if (bMoveButt)
		{
			// 子弹删除了，无需再遍历
			return;
		}
	}

	for( auto& ppButtle : eneBullet)
	{
		Sprite* pBullet=(Sprite*)ppButtle; // 获取子弹精灵
		bMoveButt = bulletCollisionPlane(pBullet);
		if (bMoveButt)
		{
			// 子弹删除了，无需再遍历
			return;
		}
	}

	for ( auto& bbButtle : bulletLayer->bigBullet)
	{
		Sprite* bBullet=(Sprite*)bbButtle; // 获取子弹精灵
		bMoveButt = bigBulletCollisionEnemy(bBullet);
		if (bMoveButt)
		{
			// 子弹删除了，无需再遍历
			return;
		}
	}


	// 敌机采用传说中的人肉炸弹，与我机同归于尽
	enemyCollisionPlane();
}

bool GameLayer::bulletCollisionPlane( Sprite* pBullet)
{
	Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);
	// 是否发生碰撞
	
	if (pBullet->boundingBox().intersectsRect(pPlane->getBoundingBox()))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/game_over.mp3");
		this->unscheduleAllSelectors();
		this->bulletLayer->StopBulletShoot();
		this->planeLayer->blowUp();
		removeBullet(pBullet);
		return true;
	}
	
	return false;
}

bool GameLayer::bigBulletCollisionEnemy( Sprite* pBullet )
{
	bool flag = false;
	for( auto& eEnemy : enemyLayer->vecEnemy)
	{
		EnemySprite* pEnemySprite = (EnemySprite*)eEnemy;

		// 是否发生碰撞
		if (pow(pBullet->getPosition().x - pEnemySprite->getPosition().x, 2) + pow(pBullet->getPosition().y - pEnemySprite->getPosition().y, 2) <= 100000)
		{
			// 飞机只剩下一格生命值
			/*
			if (1 == pEnemySprite->getLife())
			{
				pEnemySprite->loseLife(); // 知道为什么这里也要loselife吗？你可以试着注释掉看看
				enemyLayer->blowupEnemy(pEnemySprite);
			}
			else
			{
				pEnemySprite->loseLife();
			}
			// 飞机只剩下一格生命值
			*/
			while (pEnemySprite->getLife() >= 1)
			{
				pEnemySprite->loseLife(); // 知道为什么这里也要loselife吗？你可以试着注释掉看看
			}
			enemyLayer->blowupEnemy(pEnemySprite);
			bulletLayer->removeBigBullet(pBullet);
            return true;
		}
	}
	return false;
}



bool GameLayer::bulletCollisionEnemy( Sprite* pBullet )
{
	for( auto& eEnemy : enemyLayer->vecEnemy)
	{
		EnemySprite* pEnemySprite = (EnemySprite*)eEnemy;

		// 是否发生碰撞
		if (pBullet->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()))
		{
				
			// 飞机只剩下一格生命值
			if (1 == pEnemySprite->getLife())
			{
				pEnemySprite->loseLife(); // 知道为什么这里也要loselife吗？你可以试着注释掉看看
				enemyLayer->blowupEnemy(pEnemySprite);
			}
			else
			{
				pEnemySprite->loseLife();
			}

			//删除子弹
			bulletLayer->removeBullet(pBullet);
			return true;
		}
	}

	return false;
}

bool GameLayer::enemyCollisionPlane()
{
	Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);
	for( auto& eEnemy : enemyLayer->vecEnemy)
	{
		EnemySprite* pEnemySprite = (EnemySprite*)eEnemy;

		// 是否发生碰撞
		if (pPlane->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()) && pEnemySprite->getLife() > 0)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/game_over.mp3");
			this->unscheduleAllSelectors();
			this->bulletLayer->StopBulletShoot();
			this->planeLayer->blowUp();
			return true;
		}
	}

	return false;
}

