#include "Enemy1Sprite.h"


EnemySprite::EnemySprite(void)
{
	life=0;
}


EnemySprite::~EnemySprite(void)
{
}

EnemySprite * EnemySprite::create(CCSpriteFrame *pSpriteFrame,int life)
{
	EnemySprite *pobSprite = new EnemySprite();  
	if(pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->life=life;
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
