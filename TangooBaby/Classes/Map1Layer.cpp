//
//  Map1Layer.cpp
//  ConnectToCustomClass
//
//  Created by jason on 13-2-28.
//
//

#include "Map1Layer.h"
#include "Study1.h"
#include "MapMenu1Layer.h"

void Map1Layer::menuSelectorChangeAccount( CCObject* pObject )
{
	CCLog( "CGStartGameLayer::menuSelectorChangeAccount" );
    CCLOG("m_label:%s",m_TestLabel->getString());
}
void Map1Layer::gotoClassRom( CCObject* pObject )
{
    CCScene *pScene = Study1::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void Map1Layer::showMenu1( CCObject* pObject )
{
//    CCScene *pScene = ClassRoom::scene();
//    CCDirector::sharedDirector()->replaceScene(pScene);
    CCLOG("show menu 1......");
    
    
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "MapMenu1Layer", MapMenu1LayerLoader::loader());
    CCBReader* reader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
    reader->autorelease();
    CCNode* node = reader->readNodeGraphFromFile("wkszMapMenu/MapMenu1.ccbi");
    addChild(node);

}

void Map1Layer::controlButtonTest(CCObject* pObject, CCControlEvent event)
{
	CCLog( "CGStartGameLayer::controlButtonEventhandle" );
    m_TestLabel->setString("chenee is pig");
}

SEL_MenuHandler Map1Layer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "hgsCB", Map1Layer::gotoClassRom);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "dntgCB", Map1Layer::showMenu1);

	return NULL;
}

extension::SEL_CCControlHandler Map1Layer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "btnCB", Map1Layer::controlButtonTest );
	return NULL;
}

bool Map1Layer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_TestLabel", CCLabelTTF*, m_TestLabel );
	return false;
}