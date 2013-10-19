#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ContronLayer : public cocos2d::CCLayer
{
private:
	CCMenuItemImage *menuItem;
public:
	ContronLayer(void);
	~ContronLayer(void);

	virtual bool init();
	CREATE_FUNC(ContronLayer);

	void menu_pause_press(CCObject *pSender);
};

