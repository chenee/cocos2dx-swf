//
//  MapMenu1Layer.h
//  ConnectToCustomClass
//
//  Created by jason on 13-2-28.
//
//

#ifndef __ConnectToCustomClass__MapMenu1Layer__
#define __ConnectToCustomClass__MapMenu1Layer__


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MapMenu1Layer : public CCLayer, public CCBSelectorResolver, public CCBMemberVariableAssigner
{
	//static
public:
    
	CREATE_FUNC( MapMenu1Layer );
	
public:
    ~MapMenu1Layer()
	{
	    CC_SAFE_RELEASE_NULL( m_TestLabel );
        
        CC_SAFE_RELEASE_NULL( m_table1 );
        CC_SAFE_RELEASE_NULL( m_table1 );

	}
    
    void loadCCBFile(int i);
	void closeCB( CCObject* node );
    void tableCB( CCObject* node );

	void gameCB( CCObject* node );
//    void showMenu1(CCObject* node);
	void controlButtonTest(CCObject* pObject, CCControlEvent event);
	
	//CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

	//CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    

private:
	CCLabelTTF* m_TestLabel;
    CCSprite *m_table1, *m_table2;
};

class MapMenu1LayerLoader : public CCLayerLoader{
public:
	//CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD( MapMenu1LayerLoader, loader );
	//				||(equal)
	//	static MapMenu1LayerLoader* loader()
	//	{
	//		MapMenu1LayerLoader * ptr = new MapMenu1LayerLoader();
	//		if(ptr != NULL) {
	//			ptr->autorelease();
	//			return ptr;
	//		}
	//		CC_SAFE_DELETE(ptr);
	//		return NULL;
	//	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD( MapMenu1LayerLoader, loader );
	
	//CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD( MapMenu1Layer );
	//				||(equal)
	//	virtual MapMenu1Layer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
	//	{
	//		return MapMenu1Layer::create();
	//	}
    
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD( MapMenu1Layer );
};


#endif /* defined(__ConnectToCustomClass__MapMenu1Layer__) */
