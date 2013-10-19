#include "GameLayer.h"
#include "SimpleAudioEngine.h"

GameLayer::GameLayer(void)
{
}


GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()  
{  
    bool bRet=false;  
    do   
    {  
        CC_BREAK_IF(!CCLayer::init());  
		this->setTouchEnabled(true);
		this->scheduleUpdate();
		this->setKeypadEnabled(true);
          
        //加载background1，background1和background2是CCSprite*型成员变量
	
		background1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));  
        background1->setAnchorPoint(ccp(0,0));  
        background1->setPosition(ccp(0,0));  
        this->addChild(background1);  
  
        //加载background2  
        background2=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));  
        background2->setAnchorPoint(ccp(0,0));  
        background2->setPosition(ccp(0,background2->getContentSize().height-2));//这里减2的目的是为了防止图片交界的黑线  
  
        this->addChild(background2);  
  
        //执行任务计划，实现背景滚动  
        this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);  

		controlLayer=ContronLayer::create();
		addChild(controlLayer);

		this->bulletLayer = BulletLayer::create();
		this->addChild(bulletLayer);
		this->planeLayer = PlaneLayer::create();
		this->addChild(planeLayer);
		this->bulletLayer->StartShoot(0.05f);
		this->enemy3Layer = Enemy3Layer::create();
		this->addChild(enemy3Layer);
		this->enemy2Layer = Enemy2Layer::create();
		this->addChild(enemy2Layer);
		this->enemy1Layer = Enemy1Layer::create();
		this->addChild(enemy1Layer);
		
		
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
        bRet=true;  
    } while (0);  
    return bRet;  
}  

//背景滚动  
void GameLayer::backgroundMove(float dt)  
{  
    background1->setPositionY(background1->getPositionY()-2);  
    background2->setPositionY(background1->getPositionY()+background1->getContentSize().height-2);  
    if (background2->getPositionY()==0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败  
    {  
        background1->setPositionY(0);  
    }  
}  

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector *director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

	if(this->planeLayer->isAlive)
	{
		CCPoint beginPoint=pTouch->getLocationInView();
		beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint);
		CCRect rect=PlaneLayer::sharePlaneLayer->getChildByTag(AIRPLANE)->boundingBox();
		rect.origin.x-=15;
		rect.origin.y-=15;
		rect.size.width+=30;
		rect.size.height+=30;

		if(rect.containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch)))
		{
			CCPoint endPoint=pTouch->getPreviousLocationInView();
			endPoint=CCDirector::sharedDirector()->convertToGL(endPoint);

			CCPoint offset=ccpSub(beginPoint,endPoint);
			CCPoint pos=ccpAdd(planeLayer->getChildByTag(AIRPLANE)->getPosition(),offset);
			planeLayer->MoveTo(pos);
		}
	}
}

void GameLayer::update(float delta)
{
	if(planeLayer->isAlive)
	{
		enemy1DeleteDetect();
		heroDetect();
	}
	
}

void GameLayer::heroDetect()
{
	CCObject *et;
	CCRect planeRect=planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	planeRect.origin.x+=22.5;
	planeRect.size.width=45;
	planeRect.size.height=95;

	CCARRAY_FOREACH(this->enemy1Layer->m_pAllEnemy1,et)
	{
		EnemySprite *enemy=(EnemySprite *)et;
		CCRect enemyRect=enemy->boundingBox();
		if(planeRect.intersectsRect(enemyRect))
		{
			planeLayer->Blowup(0);
			bulletLayer->StopShoot();
			return;
		}
	}

	CCARRAY_FOREACH(this->enemy2Layer->m_AllEnemy2,et)
	{
		EnemySprite *enemy=(EnemySprite *)et;
		if(planeRect.intersectsRect(enemy->boundingBox()))
		{
			planeLayer->Blowup(0);
			bulletLayer->StopShoot();
			return;
		}
	}

	CCARRAY_FOREACH(this->enemy3Layer->m_AllEnemy3,et)
	{
		EnemySprite *enemy=(EnemySprite *)et;
		if(planeRect.intersectsRect(enemy->boundingBox()))
		{
			planeLayer->Blowup(0);
			bulletLayer->StopShoot();
			return;
		}
	}
}
void GameLayer::enemy1DeleteDetect()
{
	CCObject* bt,*et;
	CCARRAY_FOREACH(bulletLayer->m_pAllBullet,bt)
	{
		CCSprite *bullet=(CCSprite *)bt;
		CCARRAY_FOREACH(this->enemy1Layer->m_pAllEnemy1,et)
		{
			EnemySprite *enemy1=(EnemySprite *)et;
			if(bullet->boundingBox().intersectsRect(enemy1->boundingBox()))
			{
				if(enemy1->life>1)
				{
					enemy1->life--;
					this->bulletLayer->removeBullet(bullet);
				}
				else if(enemy1->life==1)
				{
					enemy1->life--;
					this->bulletLayer->removeBullet(bullet);
					this->enemy1Layer->enemy1Blowup(enemy1);
				}
			}

			CCARRAY_FOREACH(this->enemy2Layer->m_AllEnemy2,et)
			{
				EnemySprite *enemy2=(EnemySprite *)et;
				if(bullet->boundingBox().intersectsRect(enemy2->boundingBox()))
				{
					if(enemy2->life>1)
					{
						enemy2->life--;
						this->bulletLayer->removeBullet(bullet);
						CCAnimation *animation =CCAnimation::create();
						animation->setDelayPerUnit(0.1f);
						animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_hit.png"));
						animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png"));

						CCAnimate *animate=CCAnimate::create(animation);
						enemy2->runAction(animate);
					}
					else if(enemy2->life==1)
					{
						enemy2->life--;
						this->bulletLayer->removeBullet(bullet);
						this->enemy2Layer->enemy2Blowup(enemy2);
					}
				}
			}

			CCARRAY_FOREACH(this->enemy3Layer->m_AllEnemy3,et)
			{
				EnemySprite *enemy3=(EnemySprite *)et;
				if(bullet->boundingBox().intersectsRect(enemy3->boundingBox()))
				{
					if(enemy3->life>1)
					{
						enemy3->life--;
						this->bulletLayer->removeBullet(bullet);
						CCAnimation *animation =CCAnimation::create();
						animation->setDelayPerUnit(0.1f);
						animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_hit.png"));
						animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png"));

						CCAnimate *animate=CCAnimate::create(animation);
						enemy3->runAction(animate);

					}
					else if(enemy3->life==1)
					{
						enemy3->life--;
						this->bulletLayer->removeBullet(bullet);
						this->enemy3Layer->enemy3Blowup(enemy3);
					}
				}
			}
		}
	}
}


void GameLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

void GameLayer::keyMenuClicked()
{
	CCDirector::sharedDirector()->end();
}