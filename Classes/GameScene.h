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
	e_BackgroundA = 1, // 背景1 
	e_BackgroundB = 2, // 背景2 与背景一样，只是用来循环用
};

class GameLayer : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLayer);

public:
	void backgroundMove(float dt); // 背景移动
	void gameUpdate(float dt);     // 碰撞检测
	void enemyBullet(float dt);    // 敌军子弹
	bool bulletCollisionEnemy(Sprite* pBullet);   // 子弹和敌机碰撞
	bool bulletCollisionPlane(Sprite* pBullet);   // 子弹和我机碰撞
	bool bigBulletCollisionEnemy(Sprite* pBullet);   // 大子弹
	bool enemyCollisionPlane();    // 我机和敌机碰撞
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