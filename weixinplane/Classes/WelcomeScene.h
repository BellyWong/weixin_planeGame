#pragma once
#include "cocos2d.h"
#include "WelcomeLayer.h"
USING_NS_CC;
class WelcomeScene : public cocos2d::CCScene
{
public:
	WelcomeScene(void);
	~WelcomeScene(void);

	virtual bool init();
	CREATE_FUNC(WelcomeScene);

	WelcomeLayer *welcomeLayer;
};

