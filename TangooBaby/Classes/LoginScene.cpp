#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "MapScene.h"
#include "Map1Layer.h"


#include "Study1.h"
#include "Study2.h"
#include "Study3.h"
#include "DrawView.h"

//#include "script_support/CCScriptSupport.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* LoginScene::scene()
{
    CCScene *scene = CCScene::create();
    LoginScene *layer = LoginScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool LoginScene::init()
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
                                                    menu_selector(LoginScene::registerCB) );
    CCMenuItemImage *pLogin = CCMenuItemImage::create(
                                                     "wkszLogin/login.png",
                                                     "wkszLogin/login_p.png",
                                                     this,
                                                     menu_selector(LoginScene::loginCB) );
    CCMenuItemImage *pSurfer = CCMenuItemImage::create(
                                                    "wkszLogin/surfer.png",
                                                    "wkszLogin/surfer_p.png",
                                                    this,
                                                    menu_selector(LoginScene::surferCB) );
    
    pRegister->setPosition( ccp(500, 100) );
    pLogin->setPosition( ccp(650, 450) );
    pSurfer->setPosition( ccp(650, 380) );
    
    CCMenu* pMenu = CCMenu::create(pRegister,pLogin,pSurfer,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    
    //editbox
    CCScale9Sprite * ssp1 = CCScale9Sprite::create("wkszLogin/editboxBG.png");
    ssp1->setPreferredSize(CCSizeMake(500, 20));
    ssp1->setAnchorPoint(ccp(0.5, 0.5));
    pEditBox = CCEditBox::create(CCSizeMake(200,40),ssp1);
    pEditBox->setPlaceHolder("输入用户名");
    pEditBox->setFontColor(ccc3(255, 0, 255));
    pEditBox->setPosition(ccp(450, 450));
    this->addChild(pEditBox);
    
    CCScale9Sprite * ssp2 = CCScale9Sprite::create("wkszLogin/editboxBG.png");
    ssp2->setPreferredSize(CCSizeMake(500, 20));
    ssp2->setAnchorPoint(ccp(0.5, 0.5));
    pEditBoxPWD = CCEditBox::create(CCSizeMake(200,40),ssp2);
    pEditBoxPWD->setPlaceHolder("输入密码");
    pEditBoxPWD->setFontColor(ccc3(255, 0, 255));
    pEditBoxPWD->setPosition(ccp(450, 380));
    pEditBoxPWD->setInputFlag(kEditBoxInputFlagPassword);
    this->addChild(pEditBoxPWD);

    
    //mssages
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);
    
    swfBg = CCSWFNode::create("wkszLogin/swfBg.swf");
    swfBg->setPosition(ccp(size.width/2+30, size.height/2-100));
    swfBg->setScale(0.8f);
    swfBg->runAction();
    swfBg->setRepeat(true);
    this->addChild(swfBg,-9);
    
    swfWK = CCSWFNode::create("wkszLogin/swfWK.swf");
    swfWK->setPosition(ccp(800, 280));
    swfWK->runAction();
    swfWK->setRepeat(true);
    this->addChild(swfWK,-8);

    
    CCSprite *sptmp = CCSprite::create("wkszLogin/tree.png");
    sptmp->setPosition(ccp(920,80));
    this->addChild(sptmp,-7);
    
    
    swfMovie = NULL;
    flag = 0;
    return true;
}
void LoginScene::registerCB(CCObject* pSender)
{
    if (NULL != swfMovie) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        delete swfMovie, swfMovie = NULL;
    }else{
        swfMovie = CCSWFNode::create("wkszLogin/yf3.swf");
        swfMovie->setPosition(ccp(400,400));
        swfMovie->runAction();
        swfMovie->setRepeat(false);
        swfMovie->addFrameListener(-1, this,menu_selector(LoginScene::registerCB));
        this->addChild(swfMovie,0);

        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("wkszLogin/yf3.mp3", false);
    }

 }
void LoginScene::loginCB(CCObject* pSender)
{
    CCScene *pScene = MapScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LoginScene::surferCB(CCObject* pSender)
{

//    CCLOG("UID: %s, PWD: %s",pEditBox->getText(),pEditBoxPWD->getText());
    
//    CCBReader* pReader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
//    pReader->autorelease();
//    CCDirector::sharedDirector()->replaceScene( pReader->createSceneWithNodeGraphFromFile( "MapScene.ccbi" ) );
    
//    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "Map1Layer", Map1LayerLoader::loader());
//    CCBReader* reader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
//    reader->autorelease();
//    CCDirector::sharedDirector()->replaceScene( reader->createSceneWithNodeGraphFromFile( "MapScene.ccbi" ) );
//    CCNode* node = reader->readNodeGraphFromFile("MapScene.ccbi");
//    addChild(node);
//    node->setPosition(ccp(0,0));
    
    CCScene *pScene = DrawView::scene();
//    CCScene *pScene = Study1::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

    
}


