#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameOverLayer : public CCLayer
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	void menu_backGame(CCObject *pSender);
};

