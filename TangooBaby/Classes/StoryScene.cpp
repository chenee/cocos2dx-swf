#include "StoryScene.h"
#include "SimpleAudioEngine.h"
#include "MapScene.h"


USING_NS_CC;
USING_NS_CC_EXT;

CCScene* StoryScene::scene(int id)
{
    CCScene *scene = CCScene::create();
    StoryScene *layer = StoryScene::create();
    layer->setStoryID(id);

    scene->addChild(layer);
    
    return scene;
}
StoryScene::~StoryScene()
{
    deleteStory();
}
bool StoryScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    //buttons 
    CCMenuItemImage *pContinue = CCMenuItemImage::create(
                                                    "wkszStory/continue.png",
                                                     "wkszStory/continue_p.png",
                                                    this,
                                                    menu_selector(StoryScene::continueCB) );
    CCMenuItemImage *pClose = CCMenuItemImage::create(
                                                     "wkszMapMenu/close.png",
                                                      "wkszMapMenu/close_p.png",
                                                     this,
                                                     menu_selector(StoryScene::closeCB) );
    
    pContinue->setPosition( ccp(950, 100) );
    pClose->setPosition( ccp(950, 600) );
    
    CCMenu* pMenu = CCMenu::create(pContinue,pClose,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu,9);
    
    
    currentPage = 0;
    return true;
}
void StoryScene::initStory(int storyID)
{
    const int MAX_STORY_PAGE = 7;
    for (int i = 0; i<MAX_STORY_PAGE; i++) {
        char strSwf[255];
        sprintf(strSwf, "wkszStory/%d/%d.swf",storyID,i+1);
        
        //@chenee: FIXME judge the file exsit!!
//        CCFileUtils
        CCSWFNode *swf = CCSWFNode::create(strSwf);
        if (NULL == swf) {
            return;
        }
        
        swf->setPosition(ccp(512,320));
        swf->setVisible(false);
        swf->setRepeat(true);
        swf->setScale(0.8f);
        addChild(swf);

        swfPages.push_back(swf);
    }
}
void StoryScene::deleteStory()
{
    for (int i=0; i<swfPages.size(); i++) {
        swfPages[i]->removeFromParent();
        delete swfPages[i],swfPages[i]=NULL;
    }
    swfPages.clear();
}

void StoryScene::setStoryID(int id)
{
    this->storyID = id;
    initStory(id);
    playStory(currentPage);
}
void StoryScene::playStory(int page)
{
    for (int i=0; i<swfPages.size(); i++) {
        swfPages[i]->stopAction();
        swfPages[page]->setVisible(false);
    }
    swfPages[page]->setVisible(true);
    swfPages[page]->runAction();
    
    
    //voice over
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    char strMp3[255];
    sprintf(strMp3, "wkszStory/%d/%d.mp3",storyID,page+1);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(strMp3, false);
}


void StoryScene::closeCB(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    CCScene *pScene = MapScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void StoryScene::continueCB(CCObject* pSender)
{
    currentPage++;
    if(currentPage<swfPages.size()){
        playStory(currentPage);
    }else{
        closeCB(NULL);
    }
}



