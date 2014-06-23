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

	// ��������
	Sprite* background=Sprite::create("ui/shoot_background/gameover.png");
	background->setPosition(Point(winSize.width/2, winSize.height/2));
	this->addChild(background);

	// ��ʾ������ķ��� ������ת��Ϊ�ַ�����
	char temp[64];
	int nScore = EnemyLayer::m_score;
	sprintf_s(temp, "%d", nScore);
	std::string str(temp);
	str = "Score:" + str;

	TTFConfig configTTF("fonts/Marker Felt.ttf",30, GlyphCollection::DYNAMIC, nullptr, true);//��ʼ��TTFConfig,Ҫ�뿪��ӫ��Ч���������������һ������Ϊtrue 
	auto pLabel = Label::createWithTTF(configTTF, str, TextHAlignment::LEFT);//����label�����������
	pLabel->setColor(Color3B(225, 100, 56)); // ������ɫ
	pLabel->setPosition(Point(winSize.width/2, winSize.height/2 + 300));  
	pLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);//����ê�����
	// pLabel->enableGlow(Color3B::GREEN);//ӫ����ɫΪ��ɫ rc1��Color3B V3.0��ʽ���� Color4B
	this->addChild(pLabel);

	// �ٴο�ʼ
	Sprite* normalBackToGame=Sprite::create("ui/shoot_background/playagain.png");
	Sprite* pressedBackToGame=Sprite::create("ui/shoot_background/playagain.png");
	MenuItemSprite* pBackItem=MenuItemSprite::create(normalBackToGame,pressedBackToGame,NULL,CC_CALLBACK_1(GameOverLayer::menuBackCallback, this));
	pBackItem->setPosition(Point(683, 200));
	Menu *menuBack=Menu::create(pBackItem, NULL);
	menuBack->setPosition(Point::ZERO);
	this->addChild(menuBack);


	//�ص����˵�
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
	TransitionSlideInL* animateScene=TransitionSlideInL::create(1.0f, pScene); // Ҫ�滻�ĳ��� ����߽�ȥ
	Director::getInstance()->replaceScene(animateScene);
}
void GameOverLayer::menuBackCallback1( cocos2d::Ref* pSender )
{
	Scene* pScene = HelloScene::create();
	TransitionSlideInL* animateScene=TransitionSlideInL::create(1.0f, pScene); // Ҫ�滻�ĳ��� ����߽�ȥ
	Director::getInstance()->replaceScene(animateScene);
}

