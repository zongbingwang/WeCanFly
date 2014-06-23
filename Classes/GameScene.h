#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"

USING_NS_CC;

enum EnBackground
{
	e_BackgroundA = 1, // ����1 
	e_BackgroundB = 2, // ����2 �뱳��һ����ֻ������ѭ����
};

class GameLayer : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLayer);

public:
	void backgroundMove(float dt); // �����ƶ�
	void gameUpdate(float dt);     // ��ײ���
	void enemyBullet(float dt);    // �о��ӵ�
	bool bulletCollisionEnemy(Sprite* pBullet);   // �ӵ��͵л���ײ
	bool bulletCollisionPlane(Sprite* pBullet);   // �ӵ����һ���ײ
	bool bigBulletCollisionEnemy(Sprite* pBullet);   // ���ӵ�
	bool enemyCollisionPlane();    // �һ��͵л���ײ
	void removeBullet( Node* pNode );
	
public:
	PlaneLayer* returnPlaneLayer();

public:
	PlaneLayer *planeLayer;
	BulletLayer *bulletLayer;
	EnemyLayer *enemyLayer;
	ControlLayer *controlLayer;
	Vector<Sprite*> eneBullet;

};
#endif // __GAME_SCENE_H__