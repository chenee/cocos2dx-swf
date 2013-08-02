#ifndef __STUDY3_SCENE_H__
#define __STUDY3_SCENE_H__

#include "cocos2d.h"
#include "CCSWFNode.h"

#define PAGE_CAPACITY 6

class Study3 : public cocos2d::CCLayer
{
public:
    virtual bool init();
    ~Study3();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Study3);
    
    
    void setWords(char* words);
    void initWords();
    void deleteWords();
    
private:
    int totalCards;
    int currentCard;
    std::vector<std::string> strWords;
    std::vector<CCSprite*> cardWords;
    
    void displayCard(int index);
//    void playCurrentCharacter();
//    void stopCurrentCharacter();
    
    void continueCB(CCObject* pSender);
    void followCB(CCObject* pSender);
    void mySelfCB(CCObject* pSender);
    
    void update(float dt);
//    void moveOver(CCNode* sender);
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    CCSprite *hand;
    bool isFollow;

};

#endif // __HELLOWORLD_SCENE_H__
