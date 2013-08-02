//
//  CCGameSWF.h
//  CCGameSWF
//
//  Created by dario on 13-02-22.
//  Modify by chenee (chenee543216@gmail.com) on 13-05-20
//  @chenee: 1\change Objective-C to C++ ;2\change opengl es 1.1 to opengl es 2.0
//
//
//@protocol CCSWFFscommandResponder <NSObject>
//@optional
//-(void) movieNamed:(NSString*)movieName sentCommand:(NSString*)command withArguments:(NSString*)args;
//@end
//
//@interface CCGameSWF : NSObject <CCSWFFscommandResponder>
//{
//    NSMutableDictionary *m_fscommandListeners;
//}
//
//+(CCGameSWF*) sharedInstance;
//
//-(void) addFscommandResponder:(id<CCSWFFscommandResponder>)responder forMovieNamed:(NSString*)movieName;
//-(void) removeFscommandResponder:(id<CCSWFFscommandResponder>)responder forMovieNamed:(NSString*)movieName;
//
//@end

#include "cocos2d.h"
class CCGameSWF : public cocos2d::CCNode
{
//    NSMutableDictionary *m_fscommandListeners;
    cocos2d::CCArray *m_fscommandListeners;

public:
    static CCGameSWF* sharedInstance();
    void addFscommandResponder( int responder,cocos2d::CCString* movieName);
    void removeFscommandResponder(int responder, cocos2d::CCString* movieName);

    bool init();
    void dealloc();
};


