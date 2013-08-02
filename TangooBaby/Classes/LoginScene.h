#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSWFNode.h"

USING_NS_CC_EXT;

class LoginScene : public cocos2d::CCLayer
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
    CREATE_FUNC(LoginScene);
    
private:
    int flag;
    CCSWFNode *swfBg;
    CCSWFNode *swfWK;
    CCSWFNode *swfMovie;
    CCEditBox *pEditBox,*pEditBoxPWD;
};

#endif // __HELLOWORLD_SCENE_H__
