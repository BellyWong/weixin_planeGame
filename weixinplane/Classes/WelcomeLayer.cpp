#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

WelcomeLayer::WelcomeLayer(void)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init()
{
	if(CCLayer::init())
	{
		CCSprite *background1=CCSprite::create("ui/shoot_background/background_w.png");
		background1->setAnchorPoint(ccp(0,0));  
		background1->setPosition(ccp(0,0));  
		this->addChild(background1);  

		//CCSprite *welcomeSprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
		//welcomeSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2-welcomeSprite->getContentSize().height/2));
		//this->addChild(welcomeSprite);

		CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));  
		loading->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2-40));  
		this->addChild(loading);

		CCAnimation* animation=CCAnimation::create();//帧动画  
		animation->setDelayPerUnit(0.2f);  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));  

		CCAnimate* animate=CCAnimate::create(animation);  
		CCRepeat* repeat=CCRepeat::create(animate,2);//重复2次  
		CCCallFuncN* repeatdone=CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));//loadingDone用来转换场景  
		CCSequence* sequence=CCSequence::create(repeat,repeatdone,NULL);  
		loading->runAction(sequence);  
		return true;
	}
	return false;
}

void WelcomeLayer::loadingDone(CCNode *pSender)
{
	//CCTransitionScene* transiton = CCTransitionProgressRadialCW::create(1.2f,GameScene::create());
	CCDirector::sharedDirector()->replaceScene(GameScene::create());
}