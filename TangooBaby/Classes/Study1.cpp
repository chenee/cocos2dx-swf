#include "Study1.h"
#include "SimpleAudioEngine.h"

//#include "script_support/CCScriptSupport.h"
//#include "XJLayer.h"

#include "MapScene.h"
#include "Study2.h"


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


CCScene* Study1::scene()
{
    CCScene *scene = CCScene::create();
    Study1 *layer = Study1::create();
    
    scene->addChild(layer);
    
    return scene;
}
void Study1::deleteWords()
{
    CCLOG("words deleted");
    
    for (int i=0; i<strWords.size(); i++) {
        labelWords[i]->removeFromParentAndCleanup(true);

        swfWords1[i]->removeFromParent();
        delete swfWords1[i];
      
        swfWords2[i]->removeFromParent();
        delete swfWords2[i];
    }
    
    strWords.clear();
    labelWords.clear();
    swfWords1.clear();
    swfWords2.clear();
    
}
Study1::~Study1()
{
    deleteWords();
    CCTextureCache::sharedTextureCache()->removeTextureForKey("wkszStudy1/wordbg3.png");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

}
void Study1::initWords()
{
    if (this->strWords.size() == 0) {
        return;
    }
    
    CCPoint wordPoint[6] = {
        ccp(296,110),
        ccp(383,110),
        ccp(466,110),
        ccp(552,110),
        ccp(636,110),
        ccp(720,110),};
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    addChild(pMenu);

    char str[100];
    for (int i=0; i<strWords.size(); i++) {

        CCMenuItemImage *pi = CCMenuItemImage::create(
                                                      "wkszStudy1/wordbg1.png",
                                                      "wkszStudy1/wordbg2.png",
                                                      this,
                                                      menu_selector(Study1::wordCB) );
        if (i == 0) {
            CCNode *img = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("wkszStudy1/wordbg3.png"));
            pi->setNormalImage(img);
        }
        pi->setPosition(wordPoint[i%PAGE_CAPACITY]);
        pi->setTag(i);
        pi->setVisible(false);
        menuWords.push_back(pi);
        pMenu->addChild(pi);
        

        CCLOG("str:%s",strWords[i].c_str());
        CCLabelTTF* pLabel = CCLabelTTF::create(strWords[i].c_str(), "Thonburi", 34);
        pLabel->setPosition( ccp(297+i%PAGE_CAPACITY*85,112) );
        pLabel->setColor(ccBLACK);
        pLabel->setVisible(false);
        labelWords.push_back(pLabel);
        this->addChild(pLabel, 9);

        sprintf(str, "wkszCharacter1/%s.swf",strWords[i].c_str());
        CCSWFNode* swf1 = CCSWFNode::create(str);
        swf1->setPosition(ccp(506,445));
        //    swf1->setScale(0.8f);
//        swf1->runAction();
        swf1->setRepeat(true);
        swf1->setVisible(false);
        swfWords1.push_back(swf1);
        this->addChild(swf1,9);
        
        sprintf(str, "wkszCharacter2/%s.swf",strWords[i].c_str());
        CCSWFNode* swf2 = CCSWFNode::create(str);
        swf2->setPosition(ccp(280,243));
        //    swf2->setScale(0.8f);
//        swf2->runAction();
        swf2->setRepeat(true);
        swf2->setVisible(false);
        swfWords2.push_back(swf2);
        this->addChild(swf2,9);


    }
}

void Study1::setWords(char *words)
{
//get words from web!!
    
    
    std::string str1,str2,str3,str4,str5,str6;
    str1.assign("虫");
    str2.assign("牛");
    str3.assign("鸟");
    str4.assign("鱼");
    str5.assign("马");
    str6.assign("鸭");
    strWords.push_back(str1);
    strWords.push_back(str2);
    strWords.push_back(str3);
    strWords.push_back(str4);
    strWords.push_back(str5);
    strWords.push_back(str6);

    str1.assign("云");
    str2.assign("日");
    str3.assign("月");
    str4.assign("山");
    str5.assign("水");
    str6.assign("田");
    strWords.push_back(str1);
    strWords.push_back(str2);
    strWords.push_back(str3);
    strWords.push_back(str4);
    strWords.push_back(str5);
    strWords.push_back(str6);

    
    
    initWords();
    
    
}
bool Study1::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSprite* spBg = CCSprite::create("wkszStudy1/bg.png");
    spBg->setPosition(ccp(512, 320));
    addChild(spBg,-9);
    
    //buttons 
    CCMenuItemImage *pContinue = CCMenuItemImage::create(
                                                    "wkszStudy1/btnContinue.png",
                                                    "wkszStudy1/btnContinue_p.png",
                                                    this,
                                                    menu_selector(Study1::continueCB) );
    CCMenuItemImage *pClose = CCMenuItemImage::create(
                                                     "wkszStudy1/btnClose.png",
                                                     "wkszStudy1/btnClose_p.png",
                                                     this,
                                                     menu_selector(Study1::closeCB) );
    pLeft = CCMenuItemImage::create(
                                                       "wkszStudy1/btnLeft.png",
                                                       "wkszStudy1/btnLeft_p.png",
                                                    this,
                                                    menu_selector(Study1::leftPageCB) );
    pRight = CCMenuItemImage::create(
                                                       "wkszStudy1/btnRight.png",
                                                       "wkszStudy1/btnRight_p.png",
                                                       this,
                                                      menu_selector(Study1::rightPageCB) );

    pContinue->setPosition( ccp(940, 52) );
    pClose->setPosition( ccp(980, 600) );
    pLeft->setPosition( ccp(220, 110) ); pLeft->setVisible(false);
    pRight->setPosition( ccp(795, 110) );pRight->setVisible(true);
    CCMenu* pMenu = CCMenu::create(pContinue,pClose,pLeft,pRight,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    CCTextureCache::sharedTextureCache()->addImage("wkszStudy1/wordbg3.png");
    
    
    
    
    
    this->setWords("this is a fake string");
    this->current_character = 0;
    this->current_page = 0;
    this->isPlaying = false;
    
    this->displayPage(current_page,true);
    
//    swfMovie = NULL;
//    flag = 0;
    return true;
}
void Study1::playCurrentCharacter(bool sound)
{
    char strfile[255];
    if (sound) {
        sprintf(strfile,"wkszSound1/%sm.mp3", strWords[current_character].c_str());
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(strfile, false);
    }
    swfWords1[current_character]->setVisible(true);
    swfWords1[current_character]->runAction();
    
    swfWords2[current_character]->setVisible(true);
    swfWords2[current_character]->runAction();
}
void Study1::stopCurrentCharacter()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    swfWords1[current_character]->setVisible(false);
    swfWords1[current_character]->stopAction();
    
    swfWords2[current_character]->setVisible(false);
    swfWords2[current_character]->stopAction();
}
void Study1::displayPage(int page,bool sound)
{
    //set visible = false to all children;
    for (int i=0; i<strWords.size(); i++) {
        menuWords[i]->setVisible(false);
        
        labelWords[i]->setVisible(false);
        
        swfWords1[i]->setVisible(false);
        swfWords1[i]->stopAction();

        swfWords2[i]->setVisible(false);
        swfWords2[i]->stopAction();
    }

    
    for (int i=0; i<PAGE_CAPACITY; i++) {
        int current = i + page*PAGE_CAPACITY;
        
        if (current<labelWords.size()) {
            labelWords[current]->setVisible(true);
            menuWords[current]->setVisible(true);
        }
    }
    
    if (current_page>0) {
        pLeft->setVisible(true);
    }else{
        pLeft->setVisible(false);
    }
    if (current_page<(swfWords1.size()-1)/PAGE_CAPACITY) {
        pRight->setVisible(true);
    }else{
        pRight->setVisible(false);
    }
        
    playCurrentCharacter(sound);
}
void Study1::continueCB(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    CCScene *pScene = Study2::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

}
void Study1::closeCB(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    CCScene *pScene = MapScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

}
void Study1::leftPageCB(CCObject* pSender)
{
    if (current_page>0) {
        current_page--;
    }
    displayPage(current_page,false);
}
void Study1::rightPageCB(CCObject* pSender)
{
    int totalPages = (swfWords1.size() -1 )/ PAGE_CAPACITY ;
    if (current_page < totalPages) {
        current_page ++;
    }
    displayPage(current_page,false);
}


void Study1::wordCB(CCObject* pSender)
{
    CCMenuItemImage *pi = (CCMenuItemImage*)pSender;
    int tag = pi->getTag();
    CCLOG("menu item:%d",tag);
    
    CCNode *img = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("wkszStudy1/wordbg3.png"));
    pi->setNormalImage(img);
    
    if (tag != current_character) {
        stopCurrentCharacter();
        current_character = tag;
        playCurrentCharacter(true);
    }
    
}


