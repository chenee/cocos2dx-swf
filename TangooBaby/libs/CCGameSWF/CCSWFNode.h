//
//  CCSWFNode.h
//  GSGGameSWF
//
//  Created by dario on 13-02-25.
//  Modify by chenee (chenee543216@gmail.com) on 13-05-20
//  @chenee: 1\change Objective-C to C++ ;2\change opengl es 1.1 to opengl es 2.0
//
#ifndef CCSWF_NODE
#define CCSWF_NODE

#import "cocos2d.h"
#import "CCTouchDelegateProtocol.h"
#include "cocos2d.h"
#include "gameswf.h"
#include "CCSWFNodeGroup.h"

using namespace cocos2d;
//@class CCSWFNode_imp;
//
//@interface CCSWFNode : CCSprite <CCTargetedTouchDelegate>
//{
//    CCSWFNode_imp *imp;
//    GLfloat m_movieWidth;
//    GLfloat m_movieHeight;
//    GLfloat m_localScaleX;
//    GLfloat m_localScaleY;
//    GLfloat m_scaleX;
//    GLfloat m_scaleY;
//    NSMutableArray *m_touchEvents;
//
//}
//
//@property (nonatomic, assign) NSString *movieName;
//
//+(id) nodeWithSWFFile:(NSString*)file;
//-(id) initWithSWFFile:(NSString*)file;
//
//@end
//@interface CCSWFNode_imp : NSObject
//{
//@public
//    gameswf::gc_ptr<gameswf::player> m_player;
//    gameswf::gc_ptr<gameswf::root>	m_movie;
//}
//
//-(id) initWithSWFFile:(NSString*)file;
//
//@end



class CCSWFNode_imp;
class CCSWFNodeGroup;

class CCSWFNode : public cocos2d::CCSprite
{
private:
    bool isGrouped;
    bool isRuning;
    CCSWFNode_imp *imp;
    GLfloat m_movieWidth;
    GLfloat m_movieHeight;
    GLfloat m_localScaleX;
    GLfloat m_localScaleY;
    GLfloat m_scaleX;
    GLfloat m_scaleY;
//    NSMutableArray *m_touchEvents;
    CCArray* m_touchEvents;
    
    CCObject* m_listener;
    SEL_MenuHandler    m_pfnSelector;
    int iListenFrame;
    
    CCObject* m_endListener;
    SEL_MenuHandler m_pfnEndSelector;
    
    bool repeat;
    int iFrameCount;
public:
    CCSWFNode();
    ~CCSWFNode();

    void setGrouped(bool flag){ isGrouped = flag;};
    bool getGrouped(){ return isGrouped;};
    
    
    
    CCString* movieName();
    void setMovieName(char *movieName);
//    CCSWFNode(char* file);
    static CCSWFNode* create(const char* file);
    bool initWithSWFFile(const char* file);
    void setFlipX(bool flipX);
    void setFlipY(bool flipY);

    float scale();
    void setScale(float scale);
    float scaleX();
    void setScaleX(float scaleX);
    float scaleY();
    void setScaleY(float scaleY);
//    void dealloc();
    void onEnterTransitionDidFinish();
    void onExit();
    void update(float dt);
    void draw();
    
    void stopAction();
    void runAction();
    bool Runing(){return isRuning;};
    void addFrameListener(int iFrame, CCObject* target,SEL_MenuHandler selector);
    void setNextAction(CCSWFNode* target);

    void setRepeat(bool flag);
    bool getRepeat();



};


#endif
