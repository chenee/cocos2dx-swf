#include "Study3.h"
#include "SimpleAudioEngine.h"

//#include "script_support/CCScriptSupport.h"
//#include "XJLayer.h"

#include "MapScene.h"


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


CCScene* Study3::scene()
{
    CCScene *scene = CCScene::create();
    Study3 *layer = Study3::create();
    
    scene->addChild(layer);
    
    return scene;
}

void Study3::deleteWords()
{
    CCLOG("words deleted");
    
    for (int i=0; i<strWords.size(); i++) {
        cardWords[i]->removeAllChildrenWithCleanup(true);
        cardWords[i]->removeFromParentAndCleanup(true);
    }
    
    strWords.clear();
    cardWords.clear();
}

Study3::~Study3()
{
    unschedule(schedule_selector(Study3::update));

    deleteWords();
    CCTextureCache::sharedTextureCache()->removeTextureForKey("wkszStudy3/wordbg.png");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

}

void Study3::initWords()
{
    if (this->strWords.size() == 0) {
        return;
    }
    CCAssert(strWords.size() > 0, "strWord.size() should > 0");
    CCAssert(strWords.size() < 18, "strWord.size() should < 20");
    
    for (int i=0; i<strWords.size(); i++) {
        //label
        CCLabelTTF* pLabel = CCLabelTTF::create(strWords[i].c_str(), "Thonburi", 60);
        pLabel->setPosition( ccp(40,50) );
        pLabel->setColor(ccBLACK);
        
        
        //bg
        CCSprite *spWordBg = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("wkszStudy3/wordbg.png"));
        cardWords.push_back(spWordBg);        
        spWordBg->setPosition(ccp(120+i%9*100,480-i/9*130));
        
        
        spWordBg->addChild(pLabel);
        addChild(spWordBg,9);
    }
    
 }

void Study3::setWords(char *words)
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
bool Study3::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSprite* spBg = CCSprite::create("wkszStudy3/bg.png");
    spBg->setPosition(ccp(512, 320));
    addChild(spBg,-9);
    
    //buttons 
    CCMenuItemImage *pfollow = CCMenuItemImage::create(
                                                    "wkszStudy3/follow.png",
                                                    "wkszStudy3/follow_p.png",
                                                    this,
                                                    menu_selector(Study3::followCB) );
    CCMenuItemImage *pmyself = CCMenuItemImage::create(
                                                       "wkszStudy3/myself.png",
                                                       "wkszStudy3/myself_p.png",
                                                       this,
                                                       menu_selector(Study3::mySelfCB) );
    CCMenuItemImage *pcontinue = CCMenuItemImage::create(
                                                       "wkszStudy3/continue.png",
                                                       "wkszStudy3/continue_p.png",
                                                       this,
                                                       menu_selector(Study3::continueCB) );

    pfollow->setPosition( ccp(603, 102) );
    pmyself->setPosition( ccp(794, 102) );
    pcontinue->setPosition(ccp(936, 102));
    CCMenu* pMenu = CCMenu::create(pfollow,pmyself,pcontinue,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    CCTextureCache::sharedTextureCache()->addImage("wkszStudy3/wordbg.png");

    hand = CCSprite::create("wkszStudy3/hand.png");
    hand->setPosition(ccp(100, 20));
//    hand->retain();
    addChild(hand,10);
    
    this->setWords("this is a fake string");
    this->currentCard = 0;
    this->totalCards = strWords.size();
    this->isFollow = true;
    
    displayCard(currentCard);
    
    schedule(schedule_selector(Study3::update),5);

    return true;
}
void Study3::update(float dt)
{
    currentCard++;
    if (currentCard < totalCards ) {
        displayCard(currentCard);
    }else{
        CCLOG("play over , goto next page??");
        currentCard = 0;
        displayCard(currentCard);
        
    }
    
}

//void Study3::moveOver(CCNode* sender)
//{
//
//}


void Study3::displayCard(int index)
{
//    hand->removeFromParent();
//    cardWords[index]->addChild(hand,9);
    CCPoint p = cardWords[index]->getPosition();
    hand->setPosition(ccp(p.x+50,p.y-40));
    
    if (isFollow) {
        char strfile[255];
        sprintf(strfile,"wkszSound2/%s.mp3", strWords[index].c_str());
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(strfile, false);
    }
}


void Study3::followCB(CCObject* pSender)
{
    setTouchEnabled(false);
    isFollow = true;
    
    schedule(schedule_selector(Study3::update),5);
    currentCard = 0;
    displayCard(currentCard);
    
}
void Study3::mySelfCB(CCObject* pSender)
{
    isFollow = false;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    unschedule(schedule_selector(Study3::update));
    setTouchEnabled(true);
}
void Study3::continueCB(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    CCScene *pScene = MapScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

}

void Study3::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint location = touch->getLocation();
    
    for (int i= 0; i<cardWords.size(); i++) {
        if (cardWords[i]->boundingBox().containsPoint(location)) {
            displayCard(i);
            return;
        }
    }
    
}
void Study3::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
 
    
}
void Study3::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
 
    
}

