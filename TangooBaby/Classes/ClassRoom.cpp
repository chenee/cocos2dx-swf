#include "ClassRoom.h"
#include "SimpleAudioEngine.h"

//#include "script_support/CCScriptSupport.h"
//#include "XJLayer.h"

#include "Study1.h"


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


CCScene* ClassRoom::scene()
{
    CCScene *scene = CCScene::create();
    ClassRoom *layer = ClassRoom::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ClassRoom::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    //buttons 
    CCMenuItemImage *pRegister = CCMenuItemImage::create(
                                                    "wkszLogin/register.png",
                                                    "wkszLogin/register_p.png",
                                                    this,
                                                    menu_selector(ClassRoom::registerCB) );
//    CCMenuItemImage *pLogin = CCMenuItemImage::create(
//                                                     "wkszLogin/login.png",
//                                                     "wkszLogin/login_p.png",
//                                                     this,
//                                                     menu_selector(ClassRoom::loginCB) );
//    CCMenuItemImage *pSurfer = CCMenuItemImage::create(
//                                                    "wkszLogin/surfer.png",
//                                                    "wkszLogin/surfer_p.png",
//                                                    this,
//                                                    menu_selector(ClassRoom::surferCB) );
    
    pRegister->setPosition( ccp(200, 500) );
//    pLogin->setPosition( ccp(650, 450) );
//    pSurfer->setPosition( ccp(650, 380) );
    
    CCMenu* pMenu = CCMenu::create(pRegister,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    //mssages
//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//    this->addChild(pLabel, 1);
    
    swfBg = CCSWFNode::create("wkszClassRoom/classroom.swf");
    swfBg->setPosition(ccp(509.8,320));
    swfBg->setScale(0.8f);
    swfBg->runAction();
    swfBg->setRepeat(true);
    this->addChild(swfBg,-9);
    
    
//    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "XJLayer", XJLayerLoader::loader());
//    CCBReader* reader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
//    reader->autorelease();
    
    // run
//    CCDirector::sharedDirector()->replaceScene( reader->createSceneWithNodeGraphFromFile( "ClassRoom.ccbi" ) );
//    CCNode* node = reader->readNodeGraphFromFile("ClassRoom.ccbi");
//    addChild(node);
//    node->setPosition(ccp(0,0));
   
    
    swfMovie = NULL;
    flag = 0;
    return true;
}
void ClassRoom::registerCB(CCObject* pSender)
{

    CCScene *pScene = Study1::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

}
void ClassRoom::loginCB(CCObject* pSender)
{

}

void ClassRoom::surferCB(CCObject* pSender)
{

}


