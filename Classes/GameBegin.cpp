#include "GameBegin.h"
#include "GameDirector.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool HelloScene::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("For the Win.mp3",true);
	auto bglayer = HelloBGLayer::create();
	this->addChild(bglayer);
	auto inputlayer = HelloInputLayer::create();
	this->addChild(inputlayer);
	return true;
}
