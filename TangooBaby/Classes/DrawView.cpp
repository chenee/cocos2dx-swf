#include "DrawView.h"
#include "LoginScene.h"
using namespace cocos2d;

DrawView::DrawView()
{
}

DrawView::~DrawView()
{
    points.clear();
    lines.clear();
}

cocos2d::CCScene *DrawView::scene()
{
	CCScene *scene = CCScene::create();
	DrawView *layer = DrawView::create();
	scene->addChild(layer);
	return scene;
}

bool DrawView::init()
{
	bool bRet = false;
	do 
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF* rePlay = CCLabelTTF::create("replay", "Thonburi", 34);
		CC_BREAK_IF(!rePlay);
        
        CCLabelTTF* close = CCLabelTTF::create("close", "Thonburi", 34);
		CC_BREAK_IF(!rePlay);

		CCMenuItemLabel* pMenu = CCMenuItemLabel::create(rePlay, this, menu_selector(DrawView::menuCleanCallback));
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(ccp(size.width - pMenu->getContentSize().width/2-100, pMenu->getContentSize().height/2));
        
        CCMenuItemLabel* pMenu2 = CCMenuItemLabel::create(close, this, menu_selector(DrawView::menuCloseCallback));
		CC_BREAK_IF(!pMenu2);
        pMenu2->setPosition(ccp(size.width - pMenu->getContentSize().width/2, pMenu->getContentSize().height/2));

		CCMenu *menu = CCMenu::create(pMenu,pMenu2, NULL);
		menu->setPosition(CCPointZero);
		this->addChild(menu,0);
        
        
//        CCSprite* d1 = CCSprite::create("wyszDraw/大.png");
//        addChild(d1,-8);
//        d1->setPosition(ccp(size.width/2,size.height/2));

        CCSprite* d2 = CCSprite::create("wyszDraw/大3.png");
        addChild(d2,-9);
        d2->setPosition(ccp(size.width/2,size.height/2));
        
//        CCSWFNode* swfWK = CCSWFNode::create("wkszCharacter2/大.swf");
//        swfWK->setPosition(ccp(size.width/2, size.height/2));
//        swfWK->runAction();
//        swfWK->setRepeat(true);
//        addChild(swfWK,-8);
//        swfWK->setScale(4.0f);
        
//        CCLabelTTF* pLabel = CCLabelTTF::create("大", "Thonburi", 512);
//        pLabel->setPosition( ccp(size.width/2,size.height/2) );
//        pLabel->setColor(ccRED);
//        addChild(pLabel,-7);
        
        
        ccDrawColor4B(0,255,0,255);
		this->setTouchEnabled(true);
		bRet = true;
	} while (0);
	return bRet;
}

void DrawView::registerWithTouchDispatcher()
{
	CCDirector *director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool DrawView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint p;
	p.setPoint(pTouch->getLocation().x, pTouch->getLocation().y);
    points.push_back(p);
    lines.push_back(p);

	return true;
}

void DrawView::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint point;
	point.setPoint(pTouch->getLocation().x, pTouch->getLocation().y);
    lines.push_back(point);
}

void DrawView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint point;
	point.setPoint(-1, -1);
    lines.push_back(point);
}

void DrawView::draw()
{
	ccPointSize(8);
	glLineWidth(8 * CC_CONTENT_SCALE_FACTOR());
    

	if(points.size() == 0)
        return;
    
    for (int i=0; i<points.size(); i++) {
		ccDrawPoint(ccp(points[i].x, points[i].y));
    }

	if(lines.size()==0)
        return;
    
    ccVertex2F* v2 = (ccVertex2F*)malloc(sizeof(ccVertex2F)*(lines.size()+1));
    int v2_count = 0;
    
	int count = lines.size();
	bool isFirstPoint = false;
	for (int i = 0;i < count;i++){
		if (lines[i].equals(ccp(-1, -1))){
            ccDrawLines(v2, v2_count);
			isFirstPoint = true;
		}else{
			if (isFirstPoint || i == 0){
				ccDrawPoint(ccp(lines[i].x, lines[i].y));
				isFirstPoint = false;
                
                v2_count = 0;
                v2[v2_count].x = lines[i].x;
                v2[v2_count].y = lines[i].y;
			}else{
                v2_count++;
                v2[v2_count].x = lines[i].x;
                v2[v2_count].y = lines[i].y;
                ccDrawLines(v2, v2_count);

//				ccDrawLine(ccp(lines[i-1].x, lines[i-1].y), ccp(lines[i].x, lines[i].y));
			}
		}
	}
    delete v2;
}

void DrawView::menuCleanCallback( CCObject* pSender )
{
    points.clear();
    lines.clear();
}
void DrawView::menuCloseCallback( CCObject* pSender )
{
    CCScene *pScene = LoginScene::scene();   
    CCDirector::sharedDirector()->replaceScene(pScene);
}

