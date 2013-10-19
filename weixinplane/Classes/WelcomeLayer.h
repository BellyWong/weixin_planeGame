#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class WelcomeLayer:public cocos2d::CCLayer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

	void loadingDone(CCNode *pSender);
};

