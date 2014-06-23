#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// ����һ���Զ��ͷŵĳ���
    auto scene = Scene::create(); 

	// ����һ���Զ��ͷŵ�layer��
    auto layer = HelloWorld::create();

	// �����м���layer��
    scene->addChild(layer);

    // ���س���
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// ��������ø����virtual���������Լ���ʵ�ֵ�ʱ�򣬾���ôд
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// �����˳���ť
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    // ����Ĵ���ȥ���������Լ��Ĵ���
	// ����OpenGL��ͼ�Ĵ�С
	Size winSize=Director::getInstance()->getWinSize();

	//��Ԥ����ͼƬ������
	PreloadMusicAndPicture();

	// ����ͼ�����飩
	auto background = Sprite::create("ui/shoot_background/background_game.png");
	background->setPosition(Point(winSize.width/2,winSize.height/2)); // ����λ��

	// �����м��뱳��ͼ
	this->addChild(background);

	// ����copyrightͼƬ�����飩
	/*
	auto copyRight = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("shoot_copyright.png"));
	copyRight->setAnchorPoint(Point(0.5, 0)); // ���
	copyRight->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(copyRight);
	*/

	// ����loadingͼƬ�����飩
	auto loading = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	loading->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(loading);

	// Animation������ྫ��֡��ɣ��������ü��ʱ�䣬����ʱ��ȣ���ʵ�����ǰ�����һ������
	Animation* animation=Animation::create();
	animation->setDelayPerUnit(0.2f); // ���ʱ��
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading1.png");
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading2.png");
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading3.png");
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading4.png");

	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));

	// ͨ��֡���ݴ���֡��������������֡������
	Animate* animate=Animate::create(animation);
	Repeat* repeat=Repeat::create(animate,3); // �ظ�һ�������Ĵ��� 
	CallFuncN* repeatdone=CallFuncN::create(CC_CALLBACK_1(HelloWorld::loadingDone, this)); // �����ص����� CC_CALLBACK_1 ����һ������
	Sequence* sequence=Sequence::create(repeat, repeatdone, NULL);// �ö����������ǰ��˳����һִ�� repeatdone ���� repeatǰ�Ļ����Ͳ��Ქ��ִ��3������֡�Ķ���
	loading->runAction(sequence); // ִ����������

	CCParticleSystem * p1=CCParticleFire ::create();
    p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("ui/shoot/bullet1.png"));
    p1->setAutoRemoveOnFinish(true);
	p1->setEndSize(20);
	this->addChild(p1);

	this->setKeypadEnabled(true); // ���ü���Android�İ������緵�ؼ����˵�����Home���ȡ�
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::PreloadMusicAndPicture()
{
	//png����ȫ��cache�� plist�洢��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");
	// ��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/background-music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy1_down.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy2_down.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy3_down.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/game_over.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/use_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/achievement.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/out_porp.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/button.mp3");

	// ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);
}

void HelloWorld::loadingDone( Node* pNode )
{
	auto scene = GameLayer::createScene();
	TransitionCrossFade *pAnimateScene = TransitionCrossFade::create(1, scene);
	Director::getInstance()->replaceScene(pAnimateScene);
}
