#include "MapScene.h"
#include "SimpleAudioEngine.h"

//#include "script_support/CCScriptSupport.h"
#include "Map1Layer.h"

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


CCScene* MapScene::scene()
{
    CCScene *scene = CCScene::create();
    MapScene *layer = MapScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MapScene::init()
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
                                                    menu_selector(MapScene::registerCB) );
    CCMenuItemImage *pLogin = CCMenuItemImage::create(
                                                     "wkszLogin/login.png",
                                                     "wkszLogin/login_p.png",
                                                     this,
                                                     menu_selector(MapScene::loginCB) );
    CCMenuItemImage *pSurfer = CCMenuItemImage::create(
                                                    "wkszLogin/surfer.png",
                                                    "wkszLogin/surfer_p.png",
                                                    this,
                                                    menu_selector(MapScene::surferCB) );
    
    pRegister->setPosition( ccp(500, 100) );
    pLogin->setPosition( ccp(650, 450) );
    pSurfer->setPosition( ccp(650, 380) );
    
    CCMenu* pMenu = CCMenu::create(pRegister,pLogin,pSurfer,NULL);
    pMenu->setPosition( CCPointZero );
//    this->addChild(pMenu);
    
    //mssages
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);
    
    swfBg = CCSWFNode::create("wkszMap/map.swf");
    swfBg->setPosition(ccp(509.8,320));
    swfBg->setScale(0.8f);
    swfBg->runAction();
    swfBg->setRepeat(true);
    this->addChild(swfBg,-9);
    
    
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "Map1Layer", Map1LayerLoader::loader());
    CCBReader* reader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
    reader->autorelease();
    
    // run
//    CCDirector::sharedDirector()->replaceScene( reader->createSceneWithNodeGraphFromFile( "MapScene.ccbi" ) );
    CCNode* node = reader->readNodeGraphFromFile("MapScene.ccbi");
    addChild(node);
//    node->setPosition(ccp(0,0));
   
    
    swfMovie = NULL;
    flag = 0;
    return true;
}
void MapScene::registerCB(CCObject* pSender)
{
    if (NULL != swfMovie) {
        delete swfMovie, swfMovie = NULL;
    }else{
        swfMovie = CCSWFNode::create("wkszLogin/yf3.swf");
        swfMovie->setPosition(ccp(400,400));
        swfMovie->runAction();
        swfMovie->setRepeat(false);
        this->addChild(swfMovie,9);
    }

 }
void MapScene::loginCB(CCObject* pSender)
{

}

void MapScene::surferCB(CCObject* pSender)
{

}


