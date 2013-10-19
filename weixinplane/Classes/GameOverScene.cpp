#include "GameOverScene.h"


GameOverScene::GameOverScene(void)
{
}


GameOverScene::~GameOverScene(void)
{
}

bool GameOverScene::init()
{
	if(CCScene::init())
	{
		gameoverLayer=GameOverLayer::create();
		addChild(gameoverLayer);
		return true;
	}
	return false;
}
