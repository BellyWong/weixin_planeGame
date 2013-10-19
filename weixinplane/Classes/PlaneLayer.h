#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define AIRPLANE 1
class PlaneLayer : public cocos2d::CCLayer
{
public:
	PlaneLayer(void);
	~PlaneLayer(void);

	static PlaneLayer * create();

	virtual bool init();

	static PlaneLayer *sharePlaneLayer;

	bool isAlive;
	int score;
	void MoveTo(CCPoint postion);
	void Blowup(int passScore);
	void RemovePlane();

};

