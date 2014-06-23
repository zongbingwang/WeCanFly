#include "EnemyLayer.h"
#include "SimpleAudioEngine.h"

EnemyLayer::EnemyLayer()
{

}

EnemyLayer::~EnemyLayer()
{

}

bool EnemyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	cocos2d::Vector<SpriteFrame*> vecTemp;
	vecTemp.clear();

// 	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
// 	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
// 	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
// 	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

	// �л�1���򱬶���֡ ���������ʽ��һ����
	Animation* pAnimation1=Animation::create();
	pAnimation1->setDelayPerUnit(0.1f);
	pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

	// ��ӵ�AnimationCache����������ΪEnemy1Blowup
	AnimationCache::getInstance()->addAnimation(pAnimation1, "Enemy1Blowup");
	this->schedule(schedule_selector(EnemyLayer::addEnemy1), 1.0f); // ÿ1�����һ�ܵл�1

	// �л�2���򱬶���֡
	vecTemp.clear();
	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
	vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));

	Animation *pAnimation2 = Animation::createWithSpriteFrames(vecTemp);
	pAnimation2->setDelayPerUnit(0.1f);
	AnimationCache::getInstance()->addAnimation(pAnimation2, "Enemy2Blowup");
	this->schedule(schedule_selector(EnemyLayer::addEnemy2), 2.0f);

	// �л�3���򱬶���֡
	Animation *pAnimation3 = Animation::create();
	pAnimation3->addSpriteFrameWithFile("ui/shoot/enemy_down1.png");
	pAnimation3->addSpriteFrameWithFile("ui/shoot/enemy_down2.png");
	pAnimation3->setDelayPerUnit(0.1f);
	AnimationCache::getInstance()->addAnimation(pAnimation3, "Enemy3Blowup");
	this->schedule(schedule_selector(EnemyLayer::addEnemy3), 4.0f);

	//�л�4
	Animation *pAnimation4 = Animation::create();
	pAnimation4->addSpriteFrameWithFile("ui/shoot/enemy_down1.png");
	pAnimation4->addSpriteFrameWithFile("ui/shoot/enemy_down2.png");
	pAnimation4->setDelayPerUnit(0.1f);
	AnimationCache::getInstance()->addAnimation(pAnimation4, "Enemy3Blowup");
	this->schedule(schedule_selector(EnemyLayer::addEnemy4), 8.0f);


	//�л�5
	Animation *pAnimation5 = Animation::create();
	pAnimation5->addSpriteFrameWithFile("ui/shoot/enemy_down1.png");
	pAnimation5->addSpriteFrameWithFile("ui/shoot/enemy_down2.png");
	pAnimation5->setDelayPerUnit(0.1f);
	AnimationCache::getInstance()->addAnimation(pAnimation5, "Enemy3Blowup");
	this->schedule(schedule_selector(EnemyLayer::addEnemy5), 16.0f);

	// �����˵�
	// ��������ı��˵�
	scoreItem=LabelBMFont::create("0","fonts/font.fnt");
	scoreItem->setColor(Color3B(143,146,147));
	scoreItem->setAnchorPoint(Point(0,0.5));
	scoreItem->setPosition(Point(75,735)); // ���������������ģ�Ϊ�˷�����ͣ��ť�Ա�
	this->addChild(scoreItem);

	auto coin=Sprite::create("ui/shoot_background/coin.png");
	coin->setPosition(Point(250,730));
	this->addChild(coin);

	auto lives1=Sprite::create("ui/shoot_background/lives.png");
	lives1->setPosition(Point(700,730));
	this->addChild(lives1);

	auto lives2=Sprite::create("ui/shoot_background/lives.png");
	lives2->setPosition(Point(800,730));
	this->addChild(lives2);

	auto bigBullet1=Sprite::create("ui/shoot_background/bigBullet.png");
	bigBullet1->setPosition(Point(900,730));
	this->addChild(bigBullet1);

	auto bigBullet2=Sprite::create("ui/shoot_background/bigBullet.png");
	bigBullet2->setPosition(Point(1000,730));
	this->addChild(bigBullet2);

	auto bigBullet3=Sprite::create("ui/shoot_background/bigBullet.png");
	bigBullet3->setPosition(Point(1100,730));
	this->addChild(bigBullet3);

	return true;
}

void EnemyLayer::addEnemy1( float dt )
{
	EnemySprite *pEnemySprite = EnemySprite::create();
	pEnemySprite->setEnemyByType(Enemy1);
	pEnemySprite->setTag(Enemy1);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// �����˶��켣 �Լ����յ�ʱ���õĺ���
	auto actionMove=MoveTo::create(3.0f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
	Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // ��˳��ִ�� �л��ɵ���Ե���л��ƶ�����
	pEnemySprite->runAction(sequence);
}

void EnemyLayer::addEnemy2( float dt )
{
	EnemySprite *pEnemySprite = EnemySprite::create();
	pEnemySprite->setEnemyByType(Enemy2);
	pEnemySprite->setTag(Enemy2);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// �����˶��켣 �Լ����յ�ʱ���õĺ���
	auto actionMove=MoveTo::create(4.5f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
	Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // ��˳��ִ�� �л��ɵ���Ե���л��ƶ�����
	pEnemySprite->runAction(sequence);
}

void EnemyLayer::addEnemy3( float dt )
{
	EnemySprite *pEnemySprite = EnemySprite::create();
	pEnemySprite->setEnemyByType(Enemy3);
	pEnemySprite->setTag(Enemy3);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// �����˶��켣 �Լ����յ�ʱ���õĺ���
	auto actionMove=MoveTo::create(6.0f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
	Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // ��˳��ִ�� �л��ɵ���Ե���л��ƶ�����
	pEnemySprite->runAction(sequence);
}

void EnemyLayer::addEnemy4( float dt )
{
	EnemySprite *pEnemySprite = EnemySprite::create();
	pEnemySprite->setEnemyByType(Enemy4);
	pEnemySprite->setTag(Enemy4);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// �����˶��켣 �Լ����յ�ʱ���õĺ���
	auto actionMove=MoveTo::create(7.5f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
	Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // ��˳��ִ�� �л��ɵ���Ե���л��ƶ�����
	pEnemySprite->runAction(sequence);
}

void EnemyLayer::addEnemy5( float dt )
{
	EnemySprite *pEnemySprite = EnemySprite::create();
	pEnemySprite->setEnemyByType(Enemy5);
	pEnemySprite->setTag(Enemy5);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// �����˶��켣 �Լ����յ�ʱ���õĺ���
	auto actionMove=MoveTo::create(9.0f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
	Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // ��˳��ִ�� �л��ɵ���Ե���л��ƶ�����
	pEnemySprite->runAction(sequence);
}

void EnemyLayer::removeEnemy( Node *pNode)
{
	EnemySprite* enemy=(EnemySprite*)pNode;
	if (enemy!=NULL)
	{	 
		this->removeChild(enemy,true);
		vecEnemy.eraseObject(enemy);
	}
}

void EnemyLayer::blowupEnemy( EnemySprite* pEnemySprite )
{
	Animation *pAnimation = NULL;
	if (Enemy1 == pEnemySprite->getTag())
	{
		// ֮ǰ�����˱�ը�Ķ������ݣ���Enemy1Blowup����
		 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.wav");
		 pAnimation = AnimationCache::getInstance()->getAnimation("Enemy1Blowup");
		 setScore(ENEMY1_SCORE);
	}
	else if (Enemy2 == pEnemySprite->getTag())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy2_down.wav");
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy2Blowup");
		setScore(ENEMY2_SCORE);
	}
	else if (Enemy3 == pEnemySprite->getTag())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
		setScore(ENEMY3_SCORE);
	}
	else if (Enemy4 == pEnemySprite->getTag())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
		setScore(ENEMY4_SCORE);
	}
	else if (Enemy5 == pEnemySprite->getTag())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
		setScore(ENEMY5_SCORE);
	}
	else
	{
		return;
	}

	Animate *pAnimate = Animate::create(pAnimation);

	// ��ը�꣬Ҫ�Ƴ��л�
	auto pActionDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeEnemy,this, pEnemySprite)); // ������CC_CALLBACK Ϊʲô0���������и�pEnemySprite�أ������Լ������ϰɣ�
	//auto pActionDone = CallFuncN::create(std::bind(&EnemyLayer::removeEnemy, this, pEnemySprite)); ��������һ����
	Sequence* pSequence = Sequence::create(pAnimate, pActionDone, NULL);
	pEnemySprite->getSprite()->runAction(pSequence);

	updateScore(m_score);
}

void EnemyLayer::setScore( int nScore )
{
	m_score += nScore;
}

int EnemyLayer::getScore()
{
	return m_score;
}

void EnemyLayer::updateScore(int score)
{
	// ���·���
	if (score>=0)
	{
		CCString* strScore=CCString::createWithFormat("%d",score);
		scoreItem->setString(strScore->getCString());
	}
}

int EnemyLayer::m_score = 0;

