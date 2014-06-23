#include "BulletLayer.h"

#define	KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)


BulletLayer::BulletLayer()
{

}

BulletLayer::~BulletLayer()
{

}

bool BulletLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	BeginBulletShoot();

	this->schedule(schedule_selector(BulletLayer::keyBoardEvent)); //����
	return true;
}
void BulletLayer::keyBoardEvent(float dt)
{
	if (KEY_DOWN(0x4B))
	{
		CallFunc* removePlane=CallFunc::create(this,callfunc_selector(BulletLayer::addBigBullet));
		Sequence* sequence=Sequence::create(removePlane,NULL); // ��ִ���궯�������Ƴ����ɻ�
		this->runAction(sequence); // ִ��
	}
}

void BulletLayer::BeginBulletShoot( float dt )
{
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.3f, kRepeatForever, dt);
}

void BulletLayer::StopBulletShoot()
{
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::addBullet( float dt )
{
	// �ӵ�
	auto bullet1 = Sprite::create("ui/shoot/bullet1.png");
	auto bullet2 = Sprite::create("ui/shoot/bullet2.png");

	if (NULL == bullet1)
	{
		return;
	}

	this->addChild(bullet1);// �ӵ�Layer��ȥ
	this->addChild(bullet2);

	vecBullet.pushBack(bullet1); // �ӵ�������ȥ�������Ժ����ײ����
	vecBullet.pushBack(bullet2);

	// ��÷ɻ���λ��
	Point planePos = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletPos1 = Point(planePos.x + 20, planePos.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);
	Point bulletPos2 = Point(planePos.x - 20, planePos.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);

	bullet1->setPosition(bulletPos1);
	bullet2->setPosition(bulletPos2);

	// ���г��� ���о��ǳ�������

	///////1
	float flyLen1 = Director::getInstance()->getWinSize().height + bullet1->getContentSize().height/2 - bulletPos1.y;
	float flyVelocity1 = 320/1; //�����ٶ�
	float realFlyDuration1 = flyLen1/flyVelocity1; // ����ʱ��
	auto actionMove1=MoveTo::create(realFlyDuration1,Point(bulletPos1.x,Director::getInstance()->getWinSize().height+bullet1->getContentSize().height/2));
	auto actionDone=CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBullet, this));

	Sequence* sequence1=Sequence::create(actionMove1,actionDone,NULL);
	bullet1->runAction(sequence1);

	///////2

	float flyLen2 = Director::getInstance()->getWinSize().height + bullet2->getContentSize().height/2 - bulletPos2.y;
	float flyVelocity2 = 320/1; //�����ٶ�
	float realFlyDuration2 = flyLen2/flyVelocity2; // ����ʱ��
	auto actionMove2=MoveTo::create(realFlyDuration2,Point(bulletPos2.x,Director::getInstance()->getWinSize().height+bullet2->getContentSize().height/2));

	Sequence* sequence2=Sequence::create(actionMove2,actionDone,NULL);
	bullet2->runAction(sequence2);

	//Point enemyPos = PlaneLayer::sharedPlane->getChildByTag(Enemy3)->getPosition();


}
void BulletLayer::addBigBullet( )
{
	// �ӵ�
	auto bullet1 = Sprite::create("ui/shoot/bang.png");

	if (NULL == bullet1)
	{
		return;
	}

	this->addChild(bullet1);// �ӵ�Layer��ȥ

	bigBullet.pushBack(bullet1); // �ӵ�������ȥ�������Ժ����ײ����

	// ��÷ɻ���λ��
	Point planePos = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletPos = Point(planePos.x, planePos.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);

	bullet1->setPosition(bulletPos);
	// ���г��� ���о��ǳ�������

	///////1
	float flyLen1 = Director::getInstance()->getWinSize().height + bullet1->getContentSize().height/2 - bulletPos.y;
	float flyVelocity1 = 480/1; //�����ٶ�
	float realFlyDuration1 = flyLen1/flyVelocity1; // ����ʱ��
	auto actionMove1=MoveTo::create(realFlyDuration1,Point(bulletPos.x,Director::getInstance()->getWinSize().height+bullet1->getContentSize().height/2));
	auto actionDone=CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBigBullet, this));

	Sequence* sequence1=Sequence::create(actionMove1,actionDone,NULL);
	bullet1->runAction(sequence1);

}


void BulletLayer::removeBullet( Node* pNode )
{
	if (NULL == pNode)
	{ 
		return;
	}

	Sprite* bullet=(Sprite*)pNode;
	this->removeChild(bullet,true);
	vecBullet.eraseObject(bullet);
}

void BulletLayer::removeBigBullet( Node* pNode )
{
	if (NULL == pNode)
	{ 
		return;
	}

	Sprite* bullet=(Sprite*)pNode;
	this->removeChild(bullet,true);
	bigBullet.eraseObject(bullet);
}