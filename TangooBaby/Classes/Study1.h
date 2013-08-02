#ifndef __STUDY1_SCENE_H__
#define __STUDY1_SCENE_H__

#include "cocos2d.h"
#include "CCSWFNode.h"

#define PAGE_CAPACITY 6

class Study1 : public cocos2d::CCLayer
{
public:
    virtual bool init();
    ~Study1();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Study1);
//    void test();
    
    
    void setWords(char* words);
    void initWords();
    void deleteWords();
    
private:
//    int flag;
    bool isPlaying;
    
//    int iPages;
    int current_page;
//    int iCharacters;
    int current_character;
    std::vector<std::string> strWords;
//    std::vector<std::string> strSound1;
//    std::vector<std::string> strSound2;
//    std::vector<std::string> strSound3;
//    std::vector<std::string> strSound4;


    std::vector<CCMenuItemImage*> menuWords;
    std::vector<CCLabelTTF*> labelWords;
    std::vector<CCSWFNode*> swfWords1;
    std::vector<CCSWFNode*> swfWords2;
    CCMenuItemImage *pLeft,*pRight;
    
    void displayPage(int page,bool sound);
    void playCurrentCharacter(bool sound);
    void stopCurrentCharacter();
    
    void continueCB(CCObject* pSender);
    void closeCB(CCObject* pSender);
    void leftPageCB(CCObject* pSender);
    void rightPageCB(CCObject* pSender);
    void wordCB(CCObject* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
