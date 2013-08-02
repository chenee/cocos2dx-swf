//
//  Map1Layer.h
//  ConnectToCustomClass
//
//  Created by jason on 13-2-28.
//
//

#ifndef __ConnectToCustomClass__Map1Layer__
#define __ConnectToCustomClass__Map1Layer__


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Map1Layer : public CCLayer, public CCBSelectorResolver, public CCBMemberVariableAssigner
{
	//static
public:
    
	CREATE_FUNC( Map1Layer );
	
public:
    ~Map1Layer()
	{
	    CC_SAFE_RELEASE_NULL( m_TestLabel );
	}
	void menuSelectorChangeAccount( CCObject* node );
	void gotoClassRom( CCObject* node );
    void showMenu1(CCObject* node);
	void controlButtonTest(CCObject* pObject, CCControlEvent event);
	
	//CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

	//CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    

private:
	CCLabelTTF* m_TestLabel;
};

class Map1LayerLoader : public CCLayerLoader{
public:
	//CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD( Map1LayerLoader, loader );
	//				||(equal)
	//	static Map1LayerLoader* loader()
	//	{
	//		Map1LayerLoader * ptr = new Map1LayerLoader();
	//		if(ptr != NULL) {
	//			ptr->autorelease();
	//			return ptr;
	//		}
	//		CC_SAFE_DELETE(ptr);
	//		return NULL;
	//	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD( Map1LayerLoader, loader );
	
	//CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD( Map1Layer );
	//				||(equal)
	//	virtual Map1Layer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
	//	{
	//		return Map1Layer::create();
	//	}
    
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD( Map1Layer );
};


#endif /* defined(__ConnectToCustomClass__Map1Layer__) */
