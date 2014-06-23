#include "ControlLayer.h"
#include "SimpleAudioEngine.h"

ControlLayer::ControlLayer()
{

}

ControlLayer::~ControlLayer()
{

}

bool ControlLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Sprite *normalPause = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
	Sprite *pressedPause = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
	pPauseItem = MenuItemSprite::create(
		normalPause,
		pressedPause,
		NULL,
		CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));

	Point Pos = Point(normalPause->getContentSize().width/2+10, winSize.height-normalPause->getContentSize().height/2-10);
	pPauseItem->setPosition(Pos);

	Menu *menuPause=Menu::create(pPauseItem, NULL);
	menuPause->setPosition(Point::ZERO);
	this->addChild(menuPause);

	return true;
}

void ControlLayer::menuPauseCallback( cocos2d::Ref* pSender )
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	if(!Director::getInstance()->isPaused())
	{
		// ͼ��״̬����
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png")));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png")));
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); // ֹͣ��������
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects(); // ֹͣ���е���Ч
		Director::getInstance()->pause(); // ֹͣ���еĶ������л����У��ӵ�ǰ����
	}
	else
	{
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png")));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png")));
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();// �ָ�
		Director::getInstance()->resume(); // �ָ�
	}
}

