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
	// 不需要手动释放create出来的对象
	PlaneLayer *pRet = new PlaneLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease(); //将它交由内存管理器进行内存释放管理
		sharedPlane = pRet; // 赋给指针
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet); // 使用delete操作符删除一个C++对象pRet,如果pRet为NULL,则不进行操作
		return NULL;
	}
}

bool PlaneLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 我机
	Size winSize = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("ui/shoot/hero1.png");
	sprite->setPosition(Point(winSize.width/2,sprite->getContentSize().height/2));
	sprite->setTag(AIRPLANE);
	this->addChild(sprite);

	// 我机触摸
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

	//将触摸监听添加到eventDispacher中去  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite); 

	// 每帧都调用的函数
	this->schedule(schedule_selector(PlaneLayer::checkBorder));
	this->schedule(schedule_selector(PlaneLayer::keyBoardEvent));

	return true;
}

void PlaneLayer::checkBorder( float dt )
{
	//进行边界判断,不可超出屏幕  
	Point location = this->getChildByTag(AIRPLANE)->getPosition();  
	Size winSize=Director::sharedDirector()->getWinSize();  // 获取opengl视图窗口大小

	Size planeSize=this->getChildByTag(AIRPLANE)->getContentSize();  // 返回的就是这个矩形的大小,只是是逻辑尺寸, 而不是像素的
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
		isAlive=false; // 把飞机生命标识设置为死亡
		this->unscheduleAllSelectors(); // 停止飞机的所有行动

		Animation* animation=Animation::create();
		animation->setDelayPerUnit(0.3f); // 下面4个图片切换 每张间隔0.2秒
		animation->addSpriteFrameWithFileName("ui/shoot/dead1.png");
		animation->addSpriteFrameWithFileName("ui/shoot/dead2.png");
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png")); // 数据
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
		//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));

		Animate* animate=Animate::create(animation);
		CallFunc* removePlane=CallFunc::create(this,callfunc_selector(PlaneLayer::removePlane)); // 移除飞机的回调函数
		Sequence* sequence=Sequence::create(animate,removePlane,NULL); // 当执行完动作，就移除掉飞机
		this->getChildByTag(AIRPLANE)->stopAllActions(); // 停止一切的飞机动作
		this->getChildByTag(AIRPLANE)->runAction(sequence); // 执行
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
 	this->removeChildByTag(AIRPLANE,true); // 移除飞机精灵 true子节点上的所有运行行为和回调将清理
	Scene* pScene=GameOverLayer::createScene();
	TransitionMoveInT* animateScene=TransitionMoveInT::create(0.8f, pScene);//新场景从上移入覆盖 用时0.8秒
	Director::getInstance()->replaceScene(animateScene); // 替换场景
}


