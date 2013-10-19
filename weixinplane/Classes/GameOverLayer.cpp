#include "GameOverLayer.h"
#include "GameScene.h"

GameOverLayer::GameOverLayer(void)
{
}


GameOverLayer::~GameOverLayer(void)
{
}

bool GameOverLayer::init()
{
	if(CCLayer::init())
	{
		CCSprite *background=CCSprite::create("ui/shoot_background/gameover.png");
		background->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
		addChild(background);
		CCSprite *backGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));


		CCMenuItemSprite *backGameItem=CCMenuItemSprite::create(backGame,NULL,NULL,this,menu_selector(GameOverLayer::menu_backGame));
		backGameItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-backGame->getContentSize().width/2,backGame->getContentSize().height/2+10));
			//(ccp(CCDirector::sharedDirector()->getWinSize().width-backGame->getContentSize().width/2-10,backGame->getContentSize().height/2+5));

		CCMenu *menu=CCMenu::create(backGameItem,NULL);
		menu->setPosition(ccp(0,0));
		
		this->addChild(menu);
		return true;
	}
	return false;
}

void GameOverLayer::menu_backGame(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::create());
	this->getParent()->autorelease();
}