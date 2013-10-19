#pragma once
#include "cocos2d.h"
USING_NS_CC;
const int ENEMY1_MAXLIFE=10;
const int ENEMY2_MAXLIFE=50;
const int ENEMY3_MAXLIFE=120;
class EnemySprite : public cocos2d::CCSprite
{
public:
	EnemySprite(void);
	~EnemySprite(void);

	int life;
	static EnemySprite * create(CCSpriteFrame *pSpriteFrame,int life);
};

