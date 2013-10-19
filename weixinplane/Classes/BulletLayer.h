#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
USING_NS_CC;
class BulletLayer : public cocos2d::CCLayer
{	
public:
	CCArray * m_pAllBullet;
	BulletLayer(void);
	~BulletLayer(void);

	virtual bool init();
	CREATE_FUNC(BulletLayer);

	void AddBullet(float dt);
	CCSpriteBatchNode * bulletBatchNode ;

	void StartShoot(float delay);

	void StopShoot();

	void removeBullet(CCSprite *bullet);

	void bulletMoveFinished(CCNode *pSender);
};

