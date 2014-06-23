#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum Enum_Plane
{
	AIRPLANE = 1,
};

class PlaneLayer : public Layer
{
public:
	PlaneLayer();

	~PlaneLayer();

	static PlaneLayer* create(); // 实现创建

	virtual bool init(); 

public:
	void checkBorder(float dt); // 边界检测
	void keyBoardEvent(float dt);
	void blowUp();				// 飞机爆炸
	void removePlane();			// 移除飞机


public:
	static PlaneLayer* sharedPlane; // 提供全局的指针 类似单例
	bool isAlive; // 飞机是否活着
};