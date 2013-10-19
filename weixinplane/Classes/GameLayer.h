#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "Enemy1Layer.h"
#include "Enemy2Layer.h"
#include "Enemy3Layer.h"
#include "ContronLayer.h"
USING_NS_CC;
class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();
    
    CREATE_FUNC(GameLayer);

	CCSprite * background1;
	CCSprite * background2;
	PlaneLayer *planeLayer;
	BulletLayer *bulletLayer;
	Enemy1Layer *enemy1Layer;
	Enemy2Layer *enemy2Layer;
	Enemy3Layer *enemy3Layer;
	ContronLayer *controlLayer;

	void backgroundMove(float dt);

	void registerWithTouchDispatcher();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	void update(float delta);

	void enemy1DeleteDetect();
	
	void heroDetect();

	void keyBackClicked();
	void keyMenuClicked();
};

