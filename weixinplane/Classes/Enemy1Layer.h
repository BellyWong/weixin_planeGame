#pragma once
#include "cocos2d.h"
#include "Enemy1Sprite.h"
USING_NS_CC;
class Enemy1Layer : public cocos2d::CCLayer
{
public:
	Enemy1Layer(void);
	~Enemy1Layer(void);

	virtual bool init();

	CREATE_FUNC(Enemy1Layer);

	CCArray *m_pAllEnemy1;

	void addEnemy1Sprite(float dt);

	void enemy1MoveFinished(CCNode *pSender);

	void enemy1Blowup(EnemySprite *enemy1);

	void RemoveEnemy1(CCNode *pSender,void *data);
	
	void RemoveAllEnemy1();
};

