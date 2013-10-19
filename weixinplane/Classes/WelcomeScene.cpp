#include "WelcomeScene.h"


WelcomeScene::WelcomeScene(void)
{
}


WelcomeScene::~WelcomeScene(void)
{
}

bool WelcomeScene::init()
{
	if(CCScene::init())
	{
		//png加入全局cache中  
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");  
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");
		this->welcomeLayer=WelcomeLayer::create();
		this->addChild(welcomeLayer);
		return true;
	}
	return false;
}
