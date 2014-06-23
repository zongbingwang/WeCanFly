#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 创建一个自动释放的场景
    auto scene = Scene::create(); 

	// 创建一个自动释放的layer层
    auto layer = HelloWorld::create();

	// 场景中加入layer层
    scene->addChild(layer);

    // 返回场景
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// 当你想调用父类的virtual，又想有自己的实现的时候，就这么写
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// 创建退出按钮
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
    // 下面的代码去掉，加入自己的代码
	// 返回OpenGL视图的大小
	Size winSize=Director::getInstance()->getWinSize();

	//　预加载图片和音乐
	PreloadMusicAndPicture();

	// 背景图（精灵）
	auto background = Sprite::create("ui/shoot_background/background_game.png");
	background->setPosition(Point(winSize.width/2,winSize.height/2)); // 设置位置

	// 场景中加入背景图
	this->addChild(background);

	// 加入copyright图片（精灵）
	/*
	auto copyRight = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("shoot_copyright.png"));
	copyRight->setAnchorPoint(Point(0.5, 0)); // 描点
	copyRight->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(copyRight);
	*/

	// 加入loading图片（精灵）
	auto loading = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	loading->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(loading);

	// Animation是由许多精灵帧组成，可以设置间隔时间，持续时间等，它实际上是包含着一组数据
	Animation* animation=Animation::create();
	animation->setDelayPerUnit(0.2f); // 间隔时间
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading1.png");
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading2.png");
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading3.png");
	animation->addSpriteFrameWithFile("ui/shoot_background/game_loading4.png");

	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	//animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));

	// 通过帧数据创建帧动作（创建序列帧动画）
	Animate* animate=Animate::create(animation);
	Repeat* repeat=Repeat::create(animate,3); // 重复一个动作的次数 
	CallFuncN* repeatdone=CallFuncN::create(CC_CALLBACK_1(HelloWorld::loadingDone, this)); // 创建回调函数 CC_CALLBACK_1 代表一个参数
	Sequence* sequence=Sequence::create(repeat, repeatdone, NULL);// 让多个动作按照前后顺序逐一执行 repeatdone 放在 repeat前的话，就不会播放执行3次序列帧的动画
	loading->runAction(sequence); // 执行上述动画

	CCParticleSystem * p1=CCParticleFire ::create();
    p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("ui/shoot/bullet1.png"));
    p1->setAutoRemoveOnFinish(true);
	p1->setEndSize(20);
	this->addChild(p1);

	this->setKeypadEnabled(true); // 设置监听Android的按键，如返回键、菜单键、Home键等。
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
	//png加入全局cache中 plist存储了
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");
	// 音效
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

	// 背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);
}

void HelloWorld::loadingDone( Node* pNode )
{
	auto scene = GameLayer::createScene();
	TransitionCrossFade *pAnimateScene = TransitionCrossFade::create(1, scene);
	Director::getInstance()->replaceScene(pAnimateScene);
}
