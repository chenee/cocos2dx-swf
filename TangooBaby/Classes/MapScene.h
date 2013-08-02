#ifndef __MAPSCENE_SCENE_H__
#define __MAPSCENE_SCENE_H__

#include "cocos2d.h"
#include "CCSWFNode.h"



class MapScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    
    void registerCB(CCObject* pSender);
    void loginCB(CCObject* pSender);
    void surferCB(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MapScene);
    
    void test();
    
private:
    int flag;
    CCSWFNode *swfBg;
    CCSWFNode *swfWK;
    CCSWFNode *swfMovie;
};

#endif // __HELLOWORLD_SCENE_H__
