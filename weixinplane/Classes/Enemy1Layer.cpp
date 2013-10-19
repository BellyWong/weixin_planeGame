#include "Enemy1Layer.h"
#include "SimpleAudioEngine.h"

Enemy1Layer::Enemy1Layer(void)
{
}


Enemy1Layer::~Enemy1Layer(void)
{
	m_pAllEnemy1->release();
	m_pAllEnemy1=NULL;
}

bool Enemy1Layer::init()
{
	if(CCLayer::init())
	{
		m_pAllEnemy1 = CCArray::create();
		m_pAllEnemy1->retain();
		schedule(schedule_selector(Enemy1Layer::addEnemy1Sprite),0.4f);
		return true;
	}
	return false;
}

void Enemy1Layer::addEnemy1Sprite(float dt)
{
	CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");

	EnemySprite *enemySprite=EnemySprite::create(spriteFrame,1);
	int minX=enemySprite->getContentSize().width/2;
	int maxX=CCDirector::sharedDirector()->getWinSize().width-enemySprite->getContentSize().width/2;
	int rangX=maxX-minX;

	int posX=rand()%rangX+minX;
	int posY=CCDirector::sharedDirector()->getWinSize().height+enemySprite->getContentSize().height/2;
	enemySprite->setPosition(ccp(posX,posY));
	this->addChild(enemySprite);

	int minDuration=5;  
	int maxDuration=8;  
	int rangeDuration=maxDuration-minDuration;//获取速度范围  
	int actualDuration=(rand()%rangeDuration)+minDuration;//实际速度  

	CCFiniteTimeAction *actionMove=CCMoveTo::create(actualDuration,ccp(posX,0-enemySprite->getContentSize().height/2));

	CCFiniteTimeAction *actionDone=CCCallFuncN::create(this,callfuncN_selector(Enemy1Layer::enemy1MoveFinished));

	CCSequence *sequence=CCSequence::create(actionMove,actionDone,NULL);
	enemySprite->runAction(sequence);
	m_pAllEnemy1->addObject(enemySprite);
}

void Enemy1Layer::enemy1MoveFinished(CCNode *pSender)
{
	EnemySprite *enemy1Sprite=(EnemySprite *)pSender;
	if(enemy1Sprite!=NULL)
	{
		m_pAllEnemy1->removeObject(enemy1Sprite,true);
		this->removeChild(enemy1Sprite,true);
	}
}

void Enemy1Layer::enemy1Blowup(EnemySprite *enemy1)
{
	CCAnimation *animation =CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

	CCAnimate *animate = CCAnimate::create(animation);
	CCCallFuncND *blowupDone=CCCallFuncND::create(this,callfuncND_selector(Enemy1Layer::RemoveEnemy1),enemy1);

	CCSequence *sequence=CCSequence::create(animate,blowupDone,NULL);
	enemy1->runAction(sequence);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy1_down.mp3",false);
}

void Enemy1Layer::RemoveEnemy1(CCNode *pSender,void *data)
{
	EnemySprite *enemy1=(EnemySprite *)data;
	if(enemy1)
	{
		m_pAllEnemy1->removeObject(enemy1);
		this->removeChild(enemy1,true);
	}
}
void Enemy1Layer::RemoveAllEnemy1()  
{  
	CCObject* obj;  
	CCARRAY_FOREACH(m_pAllEnemy1,obj)//遍历所有敌机  
	{  
		EnemySprite* enemy1=(EnemySprite*)obj;  
		if (enemy1->life>0)  
		{  
			enemy1Blowup(enemy1);//全部爆炸  
		}  
	}  
}  
