#include "Enemy2Layer.h"
#include "SimpleAudioEngine.h"

Enemy2Layer::Enemy2Layer(void)
{
}


Enemy2Layer::~Enemy2Layer(void)
{
}

bool Enemy2Layer::init()
{
	if(CCLayer::init())
	{
		m_AllEnemy2=CCArray::create();
		m_AllEnemy2->retain();
		this->schedule(schedule_selector(Enemy2Layer::addEnemy2Plane),2.3f);
		return true;
	}
	return false;
}

void Enemy2Layer::addEnemy2Plane(float dt)
{
	EnemySprite *enemy2=EnemySprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png"),ENEMY2_MAXLIFE);

	int minX=enemy2->getContentSize().width/2;
	int maxX=CCDirector::sharedDirector()->getWinSize().width-enemy2->getContentSize().width/2;
	int rangX=maxX-minX;
	int posX=rand()%rangX+minX;
	int posY=CCDirector::sharedDirector()->getWinSize().height+enemy2->getContentSize().height/2;
	enemy2->setPosition(ccp(posX,posY));
	this->addChild(enemy2);
	m_AllEnemy2->addObject(enemy2);

	int temp=rand()%2;
	float duration;
	if(temp==0)
		duration=12.0f;
	else duration=10.0f;
	CCFiniteTimeAction *actionMove=CCMoveTo::create(duration,ccp(posX,0-enemy2->getContentSize().height/2));

	CCCallFuncN *actionDone=CCCallFuncN::create(this,callfuncN_selector(Enemy2Layer::enemy2MoveFinished));

	CCSequence *sequence=CCSequence::create(actionMove,actionDone,NULL);
	enemy2->runAction(sequence);
}

void Enemy2Layer::enemy2MoveFinished(CCNode *pSender)
{
	EnemySprite *enemy2=(EnemySprite *)pSender;
	m_AllEnemy2->removeObject(enemy2);
	this->removeChild(enemy2,true);
}

void Enemy2Layer::enemy2Blowup(EnemySprite *enemy2)
{
	CCAnimation *animation=CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));

	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

	CCAnimate *animate=CCAnimate::create(animation);

	CCCallFuncN * blowupDone=CCCallFuncN::create(this,callfuncN_selector(Enemy2Layer::removeEnemy2));
	CCSequence *sequence=CCSequence::create(animate,blowupDone,NULL);
	enemy2->runAction(sequence);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.mp3",false);
}

void Enemy2Layer::removeEnemy2(CCNode *pSender)
{
	EnemySprite *enemy2=(EnemySprite *)pSender;
	m_AllEnemy2->removeObject(enemy2,true);
	this->removeChild(enemy2,true);
}

