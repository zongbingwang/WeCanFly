#include "GameLayer.h"
#include "GameDirector.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#define	KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)

using namespace CocosDenshion;



bool HelloBGLayer::init()
{
	auto pic = Sprite::create("img/Lei/background.png");
	pic->setPosition(Point(683,385));
	this->addChild(pic);
	return true;
}



HelloInputLayer:: ~HelloInputLayer()
{
	this->unscheduleAllSelectors();
}
bool HelloInputLayer::init()
{

	IsLeiHelpDown = false;
	
	
	IsLeiShopDown = false ;
	

	IsLeiAboutUsDown = false ; 
	
	Sprite* menulist = Sprite::create();
	menulist->setPosition(1500,600);
	MoveBy* c = MoveBy::create(3.0f,Point(-425,0));
	Action* t = EaseExponentialOut::create(c);
	menulist->runAction(t);
	this->addChild(menulist);

	Size winSize = Director::getInstance()->getWinSize();
	MenuItemImage *menuNewGame = MenuItemImage::create("img/Lei/new game 1.png", "img/lei/new game 2.png",CC_CALLBACK_1(HelloInputLayer::StartCallback,this));
	menuNewGame->setPosition(Point(40, 0));
	menuNewGame->setScale(0.75f,0.75f);
	MenuItemImage *menuQuitGame = MenuItemImage::create("img/Lei/exit 1.png", "img/Lei/exit 2.png",CC_CALLBACK_1(HelloInputLayer::menuCloseCallback,this));
	menuQuitGame->setPosition(Point(0, -375));
	menuQuitGame->setScale(0.75f,0.75f);
	MenuItemImage *menuShop = MenuItemImage::create("img/Lei/shop 1.png","img/Lei/shop 2.png",CC_CALLBACK_1(HelloInputLayer::menuShopCallback,this));
	menuShop->setPosition(Point(100, -125));
	menuShop->setScale(0.75f,0.75f);
	MenuItemImage *menuHelp = MenuItemImage::create("img/Lei/help 1.png","img/Lei/help 2.png",CC_CALLBACK_1(HelloInputLayer::menuHelpCallback,this));
	menuHelp->setPosition(Point(120, -250));
	menuHelp->setScale(0.75f,0.75f);
	
	Menu *menu = Menu::create(menuNewGame,menuHelp,menuShop,menuQuitGame, NULL);
	menu->setPosition(0,0);
	menulist->addChild(menu);


	MenuItemImage *menuAboutUsItem = MenuItemImage::create("img/Lei/word_ABOUTUS.png","img/Lei/word_ABOUTUS.png",CC_CALLBACK_1(HelloInputLayer::menuAboutUsCallback,this));
	menuAboutUsItem->setPosition(Point(0, 0));
	
	Menu *menuAboutUs = Menu::create(menuAboutUsItem,NULL);
	menuAboutUs->setPosition(1300,60);
	this->addChild(menuAboutUs);


	MenuItemImage *menuSelectLeft= MenuItemImage::create("img/Lei/button_left.png","img/Lei/button_left_2.png",CC_CALLBACK_1(HelloInputLayer::menuSelectLeftCallback,this));
	menuSelectLeft->setPosition(Point(0, 0));
	MenuItemImage *menuSelectRight= MenuItemImage::create("img/Lei/button_right.png","img/Lei/button_right_2.png",CC_CALLBACK_1(HelloInputLayer::menuSelectRightCallback,this));
	menuSelectRight->setPosition(Point(132,3));
	Menu *menuSelectFlight = Menu::create(menuSelectLeft,menuSelectRight,NULL);
	menuSelectFlight->setPosition(Point(300,100));
	this->addChild(menuSelectFlight);
	

	FlightNumber = 0;
	LeiFlight0 = Sprite::create("img/Lei/0.png");

	LeiFlight1 = Sprite::create("img/Lei/1.png");
	LeiFlight1->setPosition(Point(-500,400));
	LeiFlight2= Sprite::create("img/Lei/2.png");
	LeiFlight2->setPosition(Point(-500,400));
	
	LeiFlight0->setScale(0.01f,0.01f);
	LeiFlight0->setPosition(Point(280,520));


	LeiFlight0->runAction(MoveTo::create(0.5f,Point(450,400)));
	LeiFlight0->runAction(ScaleTo::create(0.5f,1.0f,1.0f));
	
	this->addChild(LeiFlight0);
	this->addChild(LeiFlight1);
	this->addChild(LeiFlight2);
	LeiHelp = Sprite::create("img/Lei/help.png");
	
	LeiHelp->setPosition(450,1050);
	LeiHelp->setScale(0.8f,0.8f);



	LeiShop= Sprite::create("img/Lei/shop.png");
	LeiShop->setPosition(450,1050);
	LeiShop->setScale(0.8f,0.8f);


	LeiAboutUs= Sprite::create("img/Lei/about_us.png");
		LeiAboutUs->setPosition(450,1050);
		LeiAboutUs->setScale(0.7f,0.7f);


	this->addChild(LeiHelp);
	this->addChild(LeiShop);
	this->addChild(LeiAboutUs);

	return true;
}
void HelloInputLayer::StartCallback(cocos2d::Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	TransitionCrossFade *pAnimateScene = TransitionCrossFade::create(1, scene);
	Director::getInstance()->replaceScene(pAnimateScene);
}
void HelloInputLayer::menuShopCallback(cocos2d::Ref* pSender)
{
	
	
	if (IsLeiAboutUsDown){
		LeiAboutUs->runAction(MoveBy::create(0.5,Point(0,600)));
		IsLeiAboutUsDown = false;
	}
	if (IsLeiHelpDown){
		LeiHelp->runAction(MoveBy::create(0.5,Point(0,600)));
		IsLeiHelpDown = false;
	}
	if (!IsLeiShopDown){
		LeiShop->runAction(MoveBy::create(0.5,Point(0,-600)));

		IsLeiShopDown  = true;
	}else{
		LeiShop->runAction(MoveBy::create(0.5,Point(0,600)));
		IsLeiShopDown = false;

	}

}
void HelloInputLayer::menuHelpCallback(cocos2d::Ref* pSender)
{
	if (IsLeiShopDown){
		LeiShop->runAction(MoveBy::create(0.5,Point(0,600)));
		IsLeiShopDown = false;
	}
	if (IsLeiAboutUsDown){
		LeiAboutUs->runAction(MoveBy::create(0.5,Point(0,600)));
		IsLeiAboutUsDown = false;
	}
	if (!IsLeiHelpDown){
		LeiHelp->runAction(MoveBy::create(0.5,Point(0,-600)));

		IsLeiHelpDown = true;
	}else{LeiHelp->runAction(MoveBy::create(0.5f,Point(0,600)));
	IsLeiHelpDown = false;}
}


void HelloInputLayer::menuAboutUsCallback(cocos2d::Ref* pSender)
{
	
	if (IsLeiShopDown){
		LeiShop->runAction(MoveBy::create(0.5,Point(0,500)));
		IsLeiShopDown = false;
	}
	if (IsLeiHelpDown){
		LeiHelp->runAction(MoveBy::create(0.5,Point(0,500)));
		IsLeiHelpDown  = false;
	}
	if (!IsLeiAboutUsDown){
		LeiAboutUs->runAction(MoveBy::create(0.5,Point(0,-600)));

		IsLeiAboutUsDown = true;
	}else{
		LeiAboutUs->runAction(MoveBy::create(0.5f,Point(0,600)));
		IsLeiAboutUsDown = false;
	}
}

void HelloInputLayer::menuSelectLeftCallback(cocos2d::Ref* pSender)
{
	if(0 == (FlightNumber%=3)){
		FlightNumber++ ;
		MoveTo *moveLeft = MoveTo::create(0.3f,Point(-500,400)) ;
		LeiFlight0->runAction(moveLeft) ;
		LeiFlight1->setScale(0.01f,0.01f) ;
		LeiFlight1->setPosition(Point(280,520)) ; 
	
		MoveTo* move = MoveTo::create(0.5f,Point(450,400)) ;
		ScaleTo* scale = ScaleTo::create(0.5f,1.0f,1.0f) ;


		LeiFlight1->runAction(move) ;
		LeiFlight1->runAction(scale) ;

	}else if (1 == (FlightNumber%=3)){
		FlightNumber++ ;
		MoveTo *moveLeft = MoveTo::create(0.5f,Point(-500,400)) ;
		LeiFlight1->runAction(moveLeft) ;
		LeiFlight2->setScale(0.01f,0.01f);
		LeiFlight2->setPosition(Point(280,520));
		MoveTo* move = MoveTo::create(0.5f,Point(450,400));
		ScaleTo* scale = ScaleTo::create(0.5f,1.0f,1.0f);

		LeiFlight2->runAction(move);
		LeiFlight2->runAction(scale);

	}else{
		FlightNumber=0;
		MoveTo *moveLeft = MoveTo::create(0.5f,Point(-500,400));
		LeiFlight2->runAction(moveLeft);
		LeiFlight0->setScale(0.01f,0.01f);
		LeiFlight0->setPosition(Point(280,520));
		MoveTo* move = MoveTo::create(0.5f,Point(450,400));
		ScaleTo* scale = ScaleTo::create(0.5f,1.0f,1.0f);


		LeiFlight0->runAction(move);
		LeiFlight0->runAction(scale);

	}
}
void HelloInputLayer::menuSelectRightCallback(cocos2d::Ref* pSender)
{
	if(0 == (FlightNumber%=3)){
		FlightNumber=2;
		MoveTo *moveLeft = MoveTo::create(0.3f,Point(-500,400));
		LeiFlight0->runAction(moveLeft);
		LeiFlight2->setScale(0.01f,0.01f);
		LeiFlight2->setPosition(Point(280,520));
		MoveTo* move = MoveTo::create(0.5f,Point(450,400));
		ScaleTo* scale = ScaleTo::create(0.5f,1.0f,1.0f);


		LeiFlight2->runAction(move);
		LeiFlight2->runAction(scale);



	}else if (1 == (FlightNumber%=3)){
		FlightNumber--;
		MoveTo *moveLeft = MoveTo::create(0.5f,Point(-500,400));
		LeiFlight1->runAction(moveLeft);
		LeiFlight0->setScale(0.01f,0.01f);
		LeiFlight0->setPosition(Point(280,520));
		MoveTo* move = MoveTo::create(0.5f,Point(450,400));
		ScaleTo* scale = ScaleTo::create(0.5f,1.0f,1.0f);


		LeiFlight0->runAction(move);
		LeiFlight0->runAction(scale);
		 
	}else{
		FlightNumber--;
		MoveTo *moveLeft = MoveTo::create(0.5f,Point(-500,400));
		LeiFlight2->runAction(moveLeft);
		LeiFlight1->setScale(0.01f,0.01f);
		LeiFlight1->setPosition(Point(280,520));
		MoveTo* move = MoveTo::create(0.5f,Point(450,400));
		ScaleTo* scale = ScaleTo::create(0.5f,1.0f,1.0f);

		LeiFlight1->runAction(move);
		LeiFlight1->runAction(scale);

	}
}


void HelloInputLayer::menuCloseCallback(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

