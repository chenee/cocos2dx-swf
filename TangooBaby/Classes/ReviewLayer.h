//
//  ReviewLayer.h
//  ConnectToCustomClass
//
//  Created by jason on 13-2-28.
//
//

#ifndef __ConnectToCustomClass__ReviewLayer__
#define __ConnectToCustomClass__ReviewLayer__


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ReviewLayer : public CCLayer, public CCBSelectorResolver, public CCBMemberVariableAssigner
{
	//static
public:
    
	CREATE_FUNC( ReviewLayer );
	
public:
    ~ReviewLayer()
	{
	    CC_SAFE_RELEASE_NULL( m_TestLabel );
	}
    
	void closeCB( CCObject* node );
    void storyCB( CCObject* node );
	void characterCB( CCObject* node );
    void soundCB(CCObject* node);
    void wordCB(CCObject* node);
    void sentenceCB(CCObject* node);

	void controlButtonTest(CCObject* pObject, CCControlEvent event);
	
	//CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

	//CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    

private:
	CCLabelTTF* m_TestLabel;
//    CCSprite *m_table1, *m_table2;
};

class ReviewLayerLoader : public CCLayerLoader{
public:
	//CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD( ReviewLayerLoader, loader );
	//				||(equal)
	//	static ReviewLayerLoader* loader()
	//	{
	//		ReviewLayerLoader * ptr = new ReviewLayerLoader();
	//		if(ptr != NULL) {
	//			ptr->autorelease();
	//			return ptr;
	//		}
	//		CC_SAFE_DELETE(ptr);
	//		return NULL;
	//	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD( ReviewLayerLoader, loader );
	
	//CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD( ReviewLayer );
	//				||(equal)
	//	virtual ReviewLayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
	//	{
	//		return ReviewLayer::create();
	//	}
    
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD( ReviewLayer );
};


#endif /* defined(__ConnectToCustomClass__ReviewLayer__) */
