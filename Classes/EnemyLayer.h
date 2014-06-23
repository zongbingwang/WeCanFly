#pragma once
#include "cocos2d.h"
#include "EnemyDefine.h"
#include "Enemy.h"

USING_NS_CC;

class EnemyLayer : public Layer
{
public:
	EnemyLayer();
	~EnemyLayer();
	virtual bool init();
	CREATE_FUNC(EnemyLayer);

public:
	void addEnemy1(float dt); // ��ӵл�1
	void addEnemy2(float dt); // ��ӵл�2
	void addEnemy3(float dt); // ��ӵл�3
	void addEnemy4(float dt); // ��ӵл�2
	void addEnemy5(float dt); // ��ӵл�3


	void blowupEnemy(EnemySprite* pEnemySprite);	// �л�3��ը
	void removeEnemy(Node *pNode);					// �Ƴ��л�pNode

	void setScore(int nScore);						// ���÷���
	int  getScore();								// ��÷���
	void updateScore(int score);					// ���·���

public:
	Vector<EnemySprite*> vecEnemy;	// �л����������ڱ�����ײ����
	static int m_score;				// ����
	LabelBMFont* scoreItem;			// �����ı��˵�
};