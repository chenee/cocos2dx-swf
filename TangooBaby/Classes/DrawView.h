#ifndef __DRAW_VIEW_H_
#define __DRAW_VIEW_H_

#include "cocos2d.h"

USING_NS_CC;

class DrawView : public cocos2d::CCLayerColor
{
public:

	DrawView();
	~DrawView();
    std::vector<CCPoint> points;
    std::vector<CCPoint> lines;

//	cocos2d::CCArray *points;
//	cocos2d::CCArray *lines;
	static cocos2d::CCScene *scene();
	virtual bool init();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void draw();

	virtual void menuCleanCallback(cocos2d::CCObject* pSender);
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);
	virtual void registerWithTouchDispatcher(void);

	CREATE_FUNC(DrawView);
};
#endif