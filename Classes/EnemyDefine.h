#pragma once

// 敌机生命值
const int ENEMY1_MAXLIFE=1;
const int ENEMY2_MAXLIFE=2;
const int ENEMY3_MAXLIFE=3;
const int ENEMY4_MAXLIFE=4;
const int ENEMY5_MAXLIFE=5;


// 敌机分数
const int ENEMY1_SCORE=1;
const int ENEMY2_SCORE=6;
const int ENEMY3_SCORE=30;
const int ENEMY4_SCORE=50;
const int ENEMY5_SCORE=80;

// 随着分数上去，游戏难度也随着提升
enum Level
{
	EASY,
	MIDDLE,
	HARD,
	MOREHARD,
};

// 随着分数上去，游戏难度也随着提升
enum EnemyType
{
	Enemy1 = 1,
	Enemy2,
	Enemy3,
	Enemy4,
	Enemy5,
};