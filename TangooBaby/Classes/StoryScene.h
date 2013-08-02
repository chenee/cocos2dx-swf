#ifndef __STORY_SCENE_H__
#define __STORY_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSWFNode.h"

USING_NS_CC_EXT;

class StoryScene : public cocos2d::CCLayer
{
public:
    ~StoryScene();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene(int id);
    
//    void surferCB(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(StoryScene);
    
private:
    int storyID;
    void setStoryID(int id);

    int currentPage;
    
    std::vector<CCSWFNode*> swfPages;
    void playStory(int page);
    void initStory(int storyID);
    void deleteStory();
    
    void closeCB(CCObject* pSender);
    void continueCB(CCObject* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
