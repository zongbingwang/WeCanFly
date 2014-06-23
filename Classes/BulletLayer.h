#ifndef __BULLET_LAYER_H__
#define __BULLET_LAYER_H__
#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "EnemyDefine.h"
#include "EnemyLayer.h"

USING_NS_CC; // 命名空间

class BulletLayer : public Layer
{
public:
	BulletLayer();
	~BulletLayer();
	virtual bool init();
	CREATE_FUNC(BulletLayer);

public:
	void BeginBulletShoot(float dt=0.0f);	// 开启子弹射击
	void StopBulletShoot();					// 停止子弹射击
	void addBullet(float dt);				// 添加子弹
	void removeBullet(Node* pNode);	        // 移除子弹
	void removeBigBullet(Node* pNode);
	void keyBoardEvent(float dt);
	void addBigBullet( );

public:
	Vector<Sprite*> vecBullet; // 如果没加USING_NS_CC; 则要写成cocos2d::Vector<Sprite*> vecBullet;
	Vector<Sprite*> bigBullet;
};

#endif //__BULLET_LAYER_H__