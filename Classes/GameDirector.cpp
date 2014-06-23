#include "GameDirector.h"
#include "GameBegin.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

bool GameDirector::Main()
{
	auto scene = HelloScene::create();

	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create( 2 , scene ));
	Director::getInstance()->runWithScene(scene);

	return true;
}
