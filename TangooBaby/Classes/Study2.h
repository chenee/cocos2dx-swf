#ifndef __STUDY2_SCENE_H__
#define __STUDY2_SCENE_H__

#include "cocos2d.h"
#include "CCSWFNode.h"

#define PAGE_CAPACITY 6

class Study2 : public cocos2d::CCLayer
{
public:
    virtual bool init();
    ~Study2();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Study2);
    
    
    void setWords(char* words);
    void initWords();
    void deleteWords();
    
private:
    int totalCards;
    int currentCard;
    std::vector<std::string> strWords;

    std::vector<CCSprite*> cardWords;
    std::vector<CCSWFNode*> swfWords1;
    
    void displayCard(int index);
    void playCurrentCharacter();
    void stopCurrentCharacter();
    
    void continueCB(CCObject* pSender);
    void closeCB(CCObject* pSender);
    
    void update(float dt);
    void moveOver(CCNode* sender);

};

#endif // __HELLOWORLD_SCENE_H__
