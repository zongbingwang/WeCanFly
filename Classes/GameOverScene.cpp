#include "GameOverScene.h"
#include "..\cocos2d\cocos\audio\include\SimpleAudioEngine.h"
#include "GameScene.h"
#include "EnemyLayer.h"
#include "GameBegin.h"

cocos2d::Scene* GameOverLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}

	Size winSize=Director::getInstance()->getWinSize();

	// 结束界面
	Sprite* background=Sprite::create("ui/shoot_background/gameover.png");
	background->setPosition(Point(winSize.width/2, winSize.height/2));
	this->addChild(background);

	// 显示结束后的分数 （整型转换为字符串）
	char temp[64];
	int nScore = EnemyLayer::m_score;
	sprintf_s(temp, "%d", nScore);
	std::string str(temp);
	str = "Score:" + str;

	TTFConfig configTTF("fonts/Marker Felt.ttf",30, GlyphCollection::DYNAMIC, nullptr, true);//初始化TTFConfig,要想开启荧光效果，必须设置最后一个参数为true 
	auto pLabel = Label::createWithTTF(configTTF, str, TextHAlignment::LEFT);//创建label，并向左对其
	pLabel->setColor(Color3B(225, 100, 56)); // 设置颜色
	pLabel->setPosition(Point(winSize.width/2, winSize.height/2 + 300));  
	pLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);//设置锚点居中
	// pLabel->enableGlow(Color3B::GREEN);//荧光颜色为绿色 rc1用Color3B V3.0正式版用 Color4B
	this->addChild(pLabel);

	// 再次开始
	Sprite* normalBackToGame=Sprite::create("ui/shoot_background/playagain.png");
	Sprite* pressedBackToGame=Sprite::create("ui/shoot_background/playagain.png");
	MenuItemSprite* pBackItem=MenuItemSprite::create(normalBackToGame,pressedBackToGame,NULL,CC_CALLBACK_1(GameOverLayer::menuBackCallback, this));
	pBackItem->setPosition(Point(683, 200));
	Menu *menuBack=Menu::create(pBackItem, NULL);
	menuBack->setPosition(Point::ZERO);
	this->addChild(menuBack);


	//回到主菜单
	Sprite* normalBackToGame1=Sprite::create("ui/shoot_background/menu.png");
	Sprite* pressedBackToGame1=Sprite::create("ui/shoot_background/menu.png");
	MenuItemSprite* pBackItem1=MenuItemSprite::create(normalBackToGame1,pressedBackToGame1,NULL,CC_CALLBACK_1(GameOverLayer::menuBackCallback1, this));
	pBackItem1->setPosition(Point(683, 80));
	Menu *menuBack1=Menu::create(pBackItem1, NULL);
	menuBack1->setPosition(Point::ZERO);
	this->addChild(menuBack1);
}

void GameOverLayer::menuBackCallback( cocos2d::Ref* pSender )
{
	Scene* pScene = GameLayer::createScene();
	TransitionSlideInL* animateScene=TransitionSlideInL::create(1.0f, pScene); // 要替换的场景 从左边进去
	Director::getInstance()->replaceScene(animateScene);
}
void GameOverLayer::menuBackCallback1( cocos2d::Ref* pSender )
{
	Scene* pScene = HelloScene::create();
	TransitionSlideInL* animateScene=TransitionSlideInL::create(1.0f, pScene); // 要替换的场景 从左边进去
	Director::getInstance()->replaceScene(animateScene);
}

