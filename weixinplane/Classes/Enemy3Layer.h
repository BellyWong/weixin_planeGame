#pragma once
#include "cocos2d.h"
#include "Enemy1Sprite.h"
USING_NS_CC;
class Enemy3Layer :public CCLayer
{
public:
	Enemy3Layer(void);
	~Enemy3Layer(void);

	virtual bool init();
	CREATE_FUNC(Enemy3Layer);

	CCArray *m_AllEnemy3;

	void addEnemy3(float dt);

	void enemy3MoveFinished(CCNode *pSender);

	void enemy3Blowup(EnemySprite *enemy3);

	void removeEnemy3(CCNode *pSender);
};

