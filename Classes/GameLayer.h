#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__


#include "cocos2d.h"

USING_NS_CC;

class HelloBGLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(HelloBGLayer);
};

class HelloInputLayer : public Layer
{
public:
	~HelloInputLayer();
	virtual bool init();
	CREATE_FUNC(HelloInputLayer);
	void menuCloseCallback(Ref* pSender);
	void StartCallback(Ref* pSender);
	void menuShopCallback(Ref* pSender);
	void menuHelpCallback(Ref* pSender);
	void menuAboutUsCallback(Ref* pSender);

	void menuSelectLeftCallback(Ref* pSender);
	void menuSelectRightCallback(Ref* pSender);

	int FlightNumber;
	Sprite * LeiFlight0;
	Sprite * LeiFlight1;
	Sprite * LeiFlight2;

	bool IsLeiShopDown ;
	bool IsLeiAboutUsDown ;
	bool IsLeiHelpDown ; 
	Sprite * LeiShop;
	Sprite * LeiAboutUs;
	Sprite * LeiHelp;


};

#endif // !__GAME_LAYER_H__
