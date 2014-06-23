#ifndef __BULLET_LAYER_H__
#define __BULLET_LAYER_H__
#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "EnemyDefine.h"
#include "EnemyLayer.h"

USING_NS_CC; // �����ռ�

class BulletLayer : public Layer
{
public:
	BulletLayer();
	~BulletLayer();
	virtual bool init();
	CREATE_FUNC(BulletLayer);

public:
	void BeginBulletShoot(float dt=0.0f);	// �����ӵ����
	void StopBulletShoot();					// ֹͣ�ӵ����
	void addBullet(float dt);				// ����ӵ�
	void removeBullet(Node* pNode);	        // �Ƴ��ӵ�
	void removeBigBullet(Node* pNode);
	void keyBoardEvent(float dt);
	void addBigBullet( );

public:
	Vector<Sprite*> vecBullet; // ���û��USING_NS_CC; ��Ҫд��cocos2d::Vector<Sprite*> vecBullet;
	Vector<Sprite*> bigBullet;
};

#endif //__BULLET_LAYER_H__