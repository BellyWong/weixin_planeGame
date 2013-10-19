#include "PlaneLayer.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
PlaneLayer *PlaneLayer::sharePlaneLayer=NULL;

PlaneLayer * PlaneLayer::create()
{
	PlaneLayer *planeLayer = new PlaneLayer();
	if(planeLayer && planeLayer->init())
	{
		planeLayer->autorelease();
		sharePlaneLayer = planeLayer;
		return planeLayer;  
	}
	else
	{
		CC_SAFE_DELETE(planeLayer);
		return NULL;
	}
}

PlaneLayer::PlaneLayer(void)
{
	isAlive=true;
	score = 0;
}

void PlaneLayer::MoveTo(CCPoint location)
{
	if(isAlive && !CCDirector::sharedDirector()->isPaused())
	{
		CCPoint actualPoint;  
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();  
		CCSize planeSize=this->getChildByTag(AIRPLANE)->getContentSize();  
		if (location.x<planeSize.width/2)  
		{  
			location.x=planeSize.width/2;  
		}  
		if (location.x>winSize.width-planeSize.width/2)  
		{  
			location.x=winSize.width-planeSize.width/2;  
		}  
		if (location.y<planeSize.height/2)  
		{  
			location.y=planeSize.height/2;  
		}  
		if (location.y>winSize.height-planeSize.height/2)  
		{  
			location.y=winSize.height-planeSize.height/2;  
		}  
		this->getChildByTag(AIRPLANE)->setPosition(location);  
	}
}

void PlaneLayer::Blowup(int passScore)
{
	isAlive =false;
	CCAnimation *animation=CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

	CCAnimate *animate=CCAnimate::create(animation);

	CCCallFunc *animationDone=CCCallFunc::create(this,callfunc_selector(PlaneLayer::RemovePlane));

	CCBlink * blink = CCBlink::create(1,3);

	CCSequence *sequence=CCSequence::create(animate,blink,animationDone,NULL);
	getChildByTag(AIRPLANE)->runAction(sequence);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_over.mp3",false);
	CCDirector::sharedDirector()->replaceScene(GameOverScene::create());
}
void PlaneLayer::RemovePlane()
{
	getChildByTag(AIRPLANE)->setVisible(false);
}

PlaneLayer::~PlaneLayer(void)
{
}

bool PlaneLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winsize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* plane=CCSprite::create("ui/shoot/hero1.png");

		plane->setPosition(ccp(winsize.width/2,plane->getContentSize().height/2));
		this->addChild(plane,0,AIRPLANE);

		
		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrameWithFileName("ui/shoot/hero1.png");
		animation->addSpriteFrameWithFileName("ui/shoot/hero2.png");

		CCAnimate * animate = CCAnimate::create(animation);
		plane->runAction(CCRepeatForever::create(animate));

		bRet=true;
	} while (0);

	return bRet;
}
