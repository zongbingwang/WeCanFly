#include "PlaneLayer.h"
#include "GameOverScene.h"

#define	KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)


PlaneLayer::PlaneLayer()
{
	isAlive = true;
}

PlaneLayer::~PlaneLayer()
{

}

PlaneLayer* PlaneLayer::sharedPlane = NULL;

PlaneLayer* PlaneLayer::create()
{
	// ����Ҫ�ֶ��ͷ�create�����Ķ���
	PlaneLayer *pRet = new PlaneLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease(); //���������ڴ�����������ڴ��ͷŹ���
		sharedPlane = pRet; // ����ָ��
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet); // ʹ��delete������ɾ��һ��C++����pRet,���pRetΪNULL,�򲻽��в���
		return NULL;
	}
}

bool PlaneLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// �һ�
	Size winSize = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("ui/shoot/hero1.png");
	sprite->setPosition(Point(winSize.width/2,sprite->getContentSize().height/2));
	sprite->setTag(AIRPLANE);
	this->addChild(sprite);

	// �һ�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event *event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0,0,s.width,s.height);

		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	listener->onTouchMoved =[](Touch* touch, Event *event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());  
		target->setPosition(target->getPosition() + touch->getDelta());  
	};


	listener->onTouchEnded = [=](Touch* touch, Event* event){
	};  

	//������������ӵ�eventDispacher��ȥ  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite); 

	// ÿ֡�����õĺ���
	this->schedule(schedule_selector(PlaneLayer::checkBorder));
	this->schedule(schedule_selector(PlaneLayer::keyBoardEvent));

	return true;
}

void PlaneLayer::checkBorder( float dt )
{
	//���б߽��ж�,���ɳ�����Ļ  
	Point location = this->getChildByTag(AIRPLANE)->getPosition();  
	Size winSize=Director::sharedDirector()->getWinSize();  // ��ȡopengl��ͼ���ڴ�С

	Size planeSize=this->getChildByTag(AIRPLANE)->getContentSize();  // ���صľ���������εĴ�С,ֻ�����߼��ߴ�, ���������ص�
	if (location.x<planeSize.width/2)  
	{  
		location.x=planeSize.width/2;  
	}  
	if (location.x>winSize.width-planeSize.width/2)  
	{  
		location.x=winSize.width-planeSize.width/2;  
	}  
	if (location.y<planeSize.height/2)  
	{  
		location.y=planeSize.height/2;  
	}  
	if (location.y>winSize.height-planeSize.height/2)  
	{  
		location.y=winSize.height-planeSize.height/2;  
	}  
	this->getChildByTag(AIRPLANE)->setPosition(location);  
}

void PlaneLayer::blowUp()
{
	if(isAlive)
	{
		isAlive=false; // �ѷɻ�������ʶ����Ϊ����
		this->unscheduleAllSelectors(); // ֹͣ�ɻ��������ж�

		Animation* animation=Animation::create();
		animation->setDelayPerUnit(0.3f); // ����4��ͼƬ�л� ÿ�ż��0.2��
		animation->addSpriteFrameWithFileName("ui/shoot/dead1.png");
		animation->addSpriteFrameWithFileName("ui/shoot/dead2.png");
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png")); // ����
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));

		Animate* animate=Animate::create(animation);
		CallFunc* removePlane=CallFunc::create(this,callfunc_selector(PlaneLayer::removePlane)); // �Ƴ��ɻ��Ļص�����
		Sequence* sequence=Sequence::create(animate,removePlane,NULL); // ��ִ���궯�������Ƴ����ɻ�
		this->getChildByTag(AIRPLANE)->stopAllActions(); // ֹͣһ�еķɻ�����
		this->getChildByTag(AIRPLANE)->runAction(sequence); // ִ��
	}
}

void PlaneLayer::keyBoardEvent(float dt)
{
	if (KEY_DOWN(0x41))
	{
		this->getChildByTag(AIRPLANE)->setPosition(this->getChildByTag(AIRPLANE)->getPosition() + Point(-10, 0));  
	}
	if (KEY_DOWN(0x44))
	{
		this->getChildByTag(AIRPLANE)->setPosition(this->getChildByTag(AIRPLANE)->getPosition() + Point(10, 0));  
	}
	if (KEY_DOWN(0x57))
	{
		this->getChildByTag(AIRPLANE)->setPosition(this->getChildByTag(AIRPLANE)->getPosition() + Point(0, 10));  
	}
	if (KEY_DOWN(0x53))
	{
		this->getChildByTag(AIRPLANE)->setPosition(this->getChildByTag(AIRPLANE)->getPosition() + Point(0, -10));  
	}
}

void PlaneLayer::removePlane()
{
 	this->removeChildByTag(AIRPLANE,true); // �Ƴ��ɻ����� true�ӽڵ��ϵ�����������Ϊ�ͻص�������
	Scene* pScene=GameOverLayer::createScene();
	TransitionMoveInT* animateScene=TransitionMoveInT::create(0.8f, pScene);//�³����������븲�� ��ʱ0.8��
	Director::getInstance()->replaceScene(animateScene); // �滻����
}


