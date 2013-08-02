#include "Study2.h"
#include "SimpleAudioEngine.h"

//#include "script_support/CCScriptSupport.h"
//#include "XJLayer.h"

#include "MapScene.h"
#include "Study3.h"

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


CCScene* Study2::scene()
{
    CCScene *scene = CCScene::create();
    Study2 *layer = Study2::create();
    
    scene->addChild(layer);
    
    return scene;
}

void Study2::deleteWords()
{
    CCLOG("words deleted");
    
    for (int i=0; i<strWords.size(); i++) {
        cardWords[i]->removeAllChildrenWithCleanup(true);
        cardWords[i]->removeFromParentAndCleanup(true);

        swfWords1[i]->removeFromParent();
        delete swfWords1[i];
    }
    
    strWords.clear();
    cardWords.clear();
    swfWords1.clear();
}

Study2::~Study2()
{
    unschedule(schedule_selector(Study2::update));

    deleteWords();
    CCTextureCache::sharedTextureCache()->removeTextureForKey("wkszStudy2/wordbg.png");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

}

void Study2::initWords()
{
    if (this->strWords.size() == 0) {
        return;
    }
    
    
    //1 flash card
    char str[100];
    int zorder = 9;
    for (int i=0; i<strWords.size(); i++) {
        //label
        CCLabelTTF* pLabel = CCLabelTTF::create(strWords[i].c_str(), "Thonburi", 34);
        pLabel->setPosition( ccp(30,290) );
        pLabel->setColor(ccBLACK);
        
        //swf
        sprintf(str, "wkszCharacter1/%s.swf",strWords[i].c_str());
        CCSWFNode* swf1 = CCSWFNode::create(str);
        swf1->setPosition(ccp(160,160));
//        swf1->setScale(0.8f);
//        swf1->runAction();
        swf1->setRepeat(true);
//        swf1->setVisible(false);
        swfWords1.push_back(swf1);
        
        //bg
        CCSprite *spWordBg = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("wkszStudy2/wordbg.png"));
        cardWords.push_back(spWordBg);
        spWordBg->setVisible(false);
        spWordBg->setPosition(ccp(500,390));
        
        
        spWordBg->addChild(pLabel);
        spWordBg->addChild(swf1);
        addChild(spWordBg,zorder++);
    }
    
    //2 word card
    for (int i=0; i<strWords.size(); i++) {
        //label
        CCLabelTTF* pLabel = CCLabelTTF::create(strWords[i].c_str(), "Thonburi", 200);
        pLabel->setPosition( ccp(160,160) );
        pLabel->setColor(ccBLACK);
        

        //bg
        CCSprite *spWordBg = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("wkszStudy2/wordbg.png"));
        cardWords.push_back(spWordBg);
        spWordBg->setVisible(false);
        spWordBg->setPosition(ccp(500,390));
        
        
        spWordBg->addChild(pLabel);
        addChild(spWordBg,zorder++);
    }
}

void Study2::setWords(char *words)
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
bool Study2::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSprite* spBg = CCSprite::create("wkszStudy2/bg.png");
    spBg->setPosition(ccp(512, 320));
    addChild(spBg,-9);
    
    //buttons 
    CCMenuItemImage *pContinue = CCMenuItemImage::create(
                                                    "wkszStudy1/btnContinue.png",
                                                    "wkszStudy1/btnContinue_p.png",
                                                    this,
                                                    menu_selector(Study2::continueCB) );
    CCMenuItemImage *pClose = CCMenuItemImage::create(
                                                     "wkszStudy1/btnClose.png",
                                                     "wkszStudy1/btnClose_p.png",
                                                     this,
                                                     menu_selector(Study2::closeCB) );

    pContinue->setPosition( ccp(940, 52) );
    pClose->setPosition( ccp(980, 600) );
    CCMenu* pMenu = CCMenu::create(pContinue,pClose,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    CCTextureCache::sharedTextureCache()->addImage("wkszStudy2/wordbg.png");

    
    this->setWords("this is a fake string");
    this->currentCard = 0;
    this->totalCards = strWords.size()*2;
    
    displayCard(currentCard);
    
    schedule(schedule_selector(Study2::update),5);

    return true;
}
void Study2::update(float dt)
{
    currentCard++;
    if (currentCard < totalCards ) {
        displayCard(currentCard);
    }else{
        CCLOG("play over , goto next page??");
//        currentCard = 0;
        this->continueCB(NULL);
    }
    
}
//void Study2::playCurrentCharacter()
//{
//    swfWords1[currentCard]->setVisible(true);
//    swfWords1[currentCard]->runAction();
//}
//void Study2::stopCurrentCharacter()
//{
//    swfWords1[currentCard]->setVisible(false);
//    swfWords1[currentCard]->stopAction();
//}
void Study2::moveOver(CCNode* sender)
{
    
    //call back
    for (int i=0; i<totalCards; i++) {
        if (i == currentCard) {
            continue;
        }
        
        cardWords[i]->setVisible(false);
        if (i<strWords.size()) {
            swfWords1[i]->stopAction();
        }
    }

}


void Study2::displayCard(int index)
{
#define DEFAULT_MOVE_DURATION 1
    
    CCAssert(index < totalCards, "currentCard NO. >= totalCards");
    
    cardWords[index]->setPosition(ccp(1200, 390));
    cardWords[index]->setVisible(true);
    
    if (currentCard < swfWords1.size()) {
        swfWords1[index]->runAction();
    }
    
    
    CCActionInterval *move = CCMoveTo::create(DEFAULT_MOVE_DURATION, ccp(500,390));
//    CCActionInterval *opacity = CCFadeTo::create(DEFAULT_MOVE_DURATION*2, 0);
//    CCSpawn *spwan = CCSpawn::create(move,/*scale,*/opacity,NULL);
    
    CCSequence* seq = CCSequence::create(move,
                                         CCCallFuncN::create(this, callfuncN_selector(Study2::moveOver)),
                                         NULL);
    
    cardWords[index]->runAction(seq);
    
    char strfile[255];
    sprintf(strfile,"wkszSound2/%s.mp3", strWords[index % strWords.size()].c_str());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(strfile, false);

    
//    playCurrentCharacter();
}
void Study2::continueCB(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    CCScene *pScene = Study3::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

}
void Study2::closeCB(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    CCScene *pScene = MapScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

}



