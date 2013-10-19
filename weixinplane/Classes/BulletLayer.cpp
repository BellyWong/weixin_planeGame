#include "BulletLayer.h"
#include "SimpleAudioEngine.h"

BulletLayer::BulletLayer(void)
{
	m_pAllBullet = CCArray::create();
	m_pAllBullet->retain();
}


BulletLayer::~BulletLayer(void)
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}

bool BulletLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		bulletBatchNode = CCSpriteBatchNode::create("ui/shoot.png");
		this->addChild(bulletBatchNode);
		bRet = true;
	} while (0);
	return bRet;
}

void BulletLayer::AddBullet(float dt)
{
	CCSprite* bullet=CCSprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);

	CCPoint planePos = PlaneLayer::sharePlaneLayer->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPos = ccp(planePos.x,planePos.y+PlaneLayer::sharePlaneLayer->getChildByTag(AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPos);

	float length = CCDirector::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2-bullet->getPosition().y;
	float velocity=500/1;
	float realMoveDuration = length/velocity;

	CCFiniteTimeAction *actionMove=CCMoveTo::create(realMoveDuration,ccp(bulletPos.x,CCDirector::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2));

	CCFiniteTimeAction *actionDone=CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));

	CCSequence *sequence =CCSequence::create(actionMove,actionDone,NULL);
	bullet->runAction(sequence);
	m_pAllBullet->addObject(bullet);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3",false);
}

void BulletLayer::bulletMoveFinished(CCNode *pSender)
{
	CCSprite * bullet = (CCSprite *)pSender;
	m_pAllBullet->removeObject(bullet,true);
	this->removeChild(bullet,true);
}

void BulletLayer::removeBullet(CCSprite *bullet)
{
	
	m_pAllBullet->removeObject(bullet,true);
	this->removeChild(bullet,true);
	bullet->cleanup();
	bullet->setVisible(false);
	
}

void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.2f,kCCRepeatForever,delay);
}

void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

