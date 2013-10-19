#pragma once
#include "cocos2d.h"
#include "Enemy1Sprite.h"
USING_NS_CC;
class Enemy2Layer :public cocos2d::CCLayer
{
public:
	Enemy2Layer(void);
	~Enemy2Layer(void);

	virtual bool init();
	CREATE_FUNC(Enemy2Layer);

	CCArray *m_AllEnemy2;

	void addEnemy2Plane(float dt);

	void enemy2MoveFinished(CCNode *pSender);

	void removeEnemy2(CCNode *pSender);

	void enemy2Blowup(EnemySprite *enemy2);


};

