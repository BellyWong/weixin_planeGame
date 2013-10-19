#include "Enemy3Layer.h"
#include "SimpleAudioEngine.h"

Enemy3Layer::Enemy3Layer(void)
{
}


Enemy3Layer::~Enemy3Layer(void)
{
}

bool Enemy3Layer::init()
{
	if(CCLayer::init())
	{
		m_AllEnemy3=CCArray::create();
		m_AllEnemy3->retain();
		schedule(schedule_selector(Enemy3Layer::addEnemy3),10.0f);
		return true;
	}
	return false;
}

void Enemy3Layer::addEnemy3(float dt)
{
	EnemySprite *enemy3=EnemySprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png"),ENEMY3_MAXLIFE);

	int minX=enemy3->getContentSize().width/2;
	int maxX=CCDirector::sharedDirector()->getWinSize().width-enemy3->getContentSize().width/2;
	int rangX=maxX-minX;
	int posX=rand()%rangX+minX;
	int posY=CCDirector::sharedDirector()->getWinSize().height+enemy3->getContentSize().height/2;
	enemy3->setPosition(ccp(posX,posY));
	this->addChild(enemy3);
	m_AllEnemy3->addObject(enemy3);

	CCAnimation *animationEnemy3=CCAnimation::create();
	animationEnemy3->setDelayPerUnit(0.1f);
	animationEnemy3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png"));
	animationEnemy3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png"));

	CCAnimate *animateEnemy3=CCAnimate::create(animationEnemy3);
	CCRepeatForever *repeatEnemy3=CCRepeatForever::create(animateEnemy3);

	CCFiniteTimeAction *actionMove=CCMoveTo::create(20.0f,ccp(posX,0-enemy3->getContentSize().height/2));

	CCCallFuncN *actionDone=CCCallFuncN::create(this,callfuncN_selector(Enemy3Layer::enemy3MoveFinished));
	CCSequence *sequence=CCSequence::create(actionMove,actionDone,NULL);
	enemy3->runAction(repeatEnemy3);
	enemy3->runAction(sequence);
}

void Enemy3Layer::enemy3MoveFinished(CCNode *pSender)
{
	EnemySprite *enemy3=(EnemySprite *)pSender;
	m_AllEnemy3->removeObject(enemy3);
	this->removeChild(enemy3,true);
}

void Enemy3Layer::enemy3Blowup(EnemySprite *enemy3)
{
	CCAnimation *animation=CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));

	CCAnimate *animate=CCAnimate::create(animation);
	CCCallFuncN *blowupDone=CCCallFuncN::create(this,callfuncN_selector(Enemy3Layer::removeEnemy3));

	CCSequence *sequence=CCSequence::create(animate,blowupDone,NULL);
	enemy3->runAction(sequence);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.mp3",false);
}

void Enemy3Layer::removeEnemy3(CCNode *pSender)
{
	EnemySprite *enemy3=(EnemySprite *)pSender;
	m_AllEnemy3->removeObject(enemy3);
	this->removeChild(enemy3,true);
}