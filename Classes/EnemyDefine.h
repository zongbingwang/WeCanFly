#pragma once

// �л�����ֵ
const int ENEMY1_MAXLIFE=1;
const int ENEMY2_MAXLIFE=2;
const int ENEMY3_MAXLIFE=3;
const int ENEMY4_MAXLIFE=4;
const int ENEMY5_MAXLIFE=5;


// �л�����
const int ENEMY1_SCORE=1;
const int ENEMY2_SCORE=6;
const int ENEMY3_SCORE=30;
const int ENEMY4_SCORE=50;
const int ENEMY5_SCORE=80;

// ���ŷ�����ȥ����Ϸ�Ѷ�Ҳ��������
enum Level
{
	EASY,
	MIDDLE,
	HARD,
	MOREHARD,
};

// ���ŷ�����ȥ����Ϸ�Ѷ�Ҳ��������
enum EnemyType
{
	Enemy1 = 1,
	Enemy2,
	Enemy3,
	Enemy4,
	Enemy5,
};