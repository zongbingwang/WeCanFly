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

	// ������������
	this->setTouchEnabled(true);

	if ((CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) == false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();// �ָ�
	}

	// �������޹���
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

	// ÿ֡�����õĺ���
	this->schedule(schedule_selector(GameLayer::backgroundMove));
	this->schedule(schedule_selector(GameLayer::gameUpdate));
	this->schedule(schedule_selector(GameLayer::enemyBullet),1.0f);

	// ����ɻ�
	planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);

	// �����ӵ�
	bulletLayer = BulletLayer::create();
	this->addChild(bulletLayer);

	// ����л��ͷ�����ʾ
	enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer);

	// ������ͣ��ť
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
		
		// ���г��� ���о��ǳ�������
		
		float flyLen = bulletPos.y - bullet->getContentSize().height/2;
		float flyVelocity = (320 + (pEnemySprite->getTag() - 1)*100) / 1; //�����ٶ�
	    float realFlyDuration = flyLen / flyVelocity; // ����ʱ��
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

	//����forд����C++ 11�������� �ӵ��͵л�����
	for( auto& eButtle : bulletLayer->vecBullet)
	{
		Sprite* pBullet=(Sprite*)eButtle; // ��ȡ�ӵ�����
		bMoveButt = bulletCollisionEnemy(pBullet);
		if (bMoveButt)
		{
			// �ӵ�ɾ���ˣ������ٱ���
			return;
		}
	}

	for( auto& ppButtle : eneBullet)
	{
		Sprite* pBullet=(Sprite*)ppButtle; // ��ȡ�ӵ�����
		bMoveButt = bulletCollisionPlane(pBullet);
		if (bMoveButt)
		{
			// �ӵ�ɾ���ˣ������ٱ���
			return;
		}
	}

	for ( auto& bbButtle : bulletLayer->bigBullet)
	{
		Sprite* bBullet=(Sprite*)bbButtle; // ��ȡ�ӵ�����
		bMoveButt = bigBulletCollisionEnemy(bBullet);
		if (bMoveButt)
		{
			// �ӵ�ɾ���ˣ������ٱ���
			return;
		}
	}


	// �л����ô�˵�е�����ը�������һ�ͬ���ھ�
	enemyCollisionPlane();
}

bool GameLayer::bulletCollisionPlane( Sprite* pBullet)
{
	Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);
	// �Ƿ�����ײ
	
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

		// �Ƿ�����ײ
		if (pow(pBullet->getPosition().x - pEnemySprite->getPosition().x, 2) + pow(pBullet->getPosition().y - pEnemySprite->getPosition().y, 2) <= 100000)
		{
			// �ɻ�ֻʣ��һ������ֵ
			/*
			if (1 == pEnemySprite->getLife())
			{
				pEnemySprite->loseLife(); // ֪��Ϊʲô����ҲҪloselife�����������ע�͵�����
				enemyLayer->blowupEnemy(pEnemySprite);
			}
			else
			{
				pEnemySprite->loseLife();
			}
			// �ɻ�ֻʣ��һ������ֵ
			*/
			while (pEnemySprite->getLife() >= 1)
			{
				pEnemySprite->loseLife(); // ֪��Ϊʲô����ҲҪloselife�����������ע�͵�����
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

		// �Ƿ�����ײ
		if (pBullet->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()))
		{
				
			// �ɻ�ֻʣ��һ������ֵ
			if (1 == pEnemySprite->getLife())
			{
				pEnemySprite->loseLife(); // ֪��Ϊʲô����ҲҪloselife�����������ע�͵�����
				enemyLayer->blowupEnemy(pEnemySprite);
			}
			else
			{
				pEnemySprite->loseLife();
			}

			//ɾ���ӵ�
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

		// �Ƿ�����ײ
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

