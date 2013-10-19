#include "ContronLayer.h"


ContronLayer::ContronLayer(void)
{
}


ContronLayer::~ContronLayer(void)
{
}

bool ContronLayer::init()
{
	if(!CCLayer::init())
		return false;
	CCSprite *pPauseNor = CCSprite::create();
	pPauseNor->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));

	CCSprite *pPausePress=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));


	menuItem=CCMenuItemImage::create();
	menuItem->initWithNormalSprite(pPauseNor,pPausePress,NULL,this,menu_selector(ContronLayer::menu_pause_press));
	menuItem->setPosition(ccp(pPauseNor->getContentSize().width/2+10,
		CCDirector::sharedDirector()->getWinSize().height-pPauseNor->getContentSize().height/2-10));
	CCMenu *menu=CCMenu::create(menuItem,NULL);
	addChild(menu);
	menu->setPosition(ccp(0,0));
	return true;
}

void ContronLayer::menu_pause_press(CCObject *pSender)
{
	if(CCDirector::sharedDirector()->isPaused())
	{
		menuItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
			menuItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
			CCDirector::sharedDirector()->resume();
	}
	else
	{
		menuItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
		menuItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
		CCDirector::sharedDirector()->pause();
	}
}
