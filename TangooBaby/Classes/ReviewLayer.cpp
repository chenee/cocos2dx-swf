//
//  ReviewLayer.cpp
//  ConnectToCustomClass
//
//  Created by jason on 13-2-28.
//
//

#include "ReviewLayer.h"
#include "ClassRoom.h"
#include "SimpleAudioEngine.h"
#include "MapMenu1Layer.h"
#include "StoryScene.h"

void ReviewLayer::closeCB( CCObject* pObject )
{
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "MapMenu1Layer", MapMenu1LayerLoader::loader());
    CCBReader* reader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
    reader->autorelease();
    CCNode* node = reader->readNodeGraphFromFile("wkszMapMenu/MapMenu1.ccbi");
    this->getParent()->addChild(node);
    
    this->removeFromParentAndCleanup(true);
}


void ReviewLayer::storyCB( CCObject* pObject )
{

    int tag = ((CCNode*)pObject)->getTag();
    if(tag<=0)
        return;
    
    CCScene *pScene = StoryScene::scene(tag);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void ReviewLayer::characterCB( CCObject* pObject )
{

}
void ReviewLayer::soundCB( CCObject* pObject )
{
}
void ReviewLayer::wordCB( CCObject* pObject )
{
}
void ReviewLayer::sentenceCB( CCObject* pObject )
{
}

void ReviewLayer::controlButtonTest(CCObject* pObject, CCControlEvent event)
{
    
}

SEL_MenuHandler ReviewLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "closeCB", ReviewLayer::closeCB);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "storyCB", ReviewLayer::storyCB);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "characterCB", ReviewLayer::characterCB);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "soundCB", ReviewLayer::soundCB);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "wordCB", ReviewLayer::wordCB);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "sentenceCB", ReviewLayer::sentenceCB);

	return NULL;
}

extension::SEL_CCControlHandler ReviewLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "playSound", ReviewLayer::controlButtonTest );
	return NULL;
}

bool ReviewLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
//	CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_table1", CCSprite*, m_table1 );
//	CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_table2", CCSprite*, m_table2 );
    
    
	return false;
}