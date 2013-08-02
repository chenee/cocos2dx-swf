//
//  MapMenu1Layer.cpp
//  ConnectToCustomClass
//
//  Created by jason on 13-2-28.
//
//

#include "MapMenu1Layer.h"
#include "ClassRoom.h"
#include "SimpleAudioEngine.h"
#include "ReviewLayer.h"

void MapMenu1Layer::closeCB( CCObject* pObject )
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    this->removeFromParentAndCleanup(true);
}
//void MapMenu1Layer::tableCB( CCObject* pObject )
//{
//    CCMenuItemImage *mi = (CCMenuItemImage*)pObject;
//    int tag = mi->getTag();
//    switch (tag) {
//        case 1:
//            m_table1->setVisible(true);
//            m_table2->setVisible(false);
//            break;
//        case 2:
//            m_table1->setVisible(false);
//            m_table2->setVisible(true);
//            break;
//        default:
//            break;
//    }
//}
void MapMenu1Layer::loadCCBFile(int i)
{
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "ReviewLayer", ReviewLayerLoader::loader());
    CCBReader* reader = new CCBReader( CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() );
    reader->autorelease();
    
    
    char str[255];
    sprintf(str,"wkszReview/ReviewLayer%d.ccbi",i);
    CCNode* node = reader->readNodeGraphFromFile(str);
    this->getParent()->addChild(node);
    
    this->closeCB(NULL);
}
void MapMenu1Layer::gameCB( CCObject* pObject )
{
    CCNode *node = (CCNode*)pObject;
    int tag = node->getTag();
    switch (tag) {
        case 1:
            loadCCBFile(1);
            break;
        case 2:
            CCLOG("no yet finished!!");
            break;
        default:
            break;
    }
 

}
//void MapMenu1Layer::showMenu1( CCObject* pObject )
//{
////    CCScene *pScene = ClassRoom::scene();
////    CCDirector::sharedDirector()->replaceScene(pScene);
//    CCLOG("show menu 1......");
//}

void MapMenu1Layer::controlButtonTest(CCObject* pObject, CCControlEvent event)
{
//	CCLog( "CGStartGameLayer::controlButtonEventhandle" );
//    m_TestLabel->setString("chenee is pig");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    CCNode* node = (CCNode*)pObject;
    int tag = node->getTag();
    if (1 == tag) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("wkszMapMenu/1/sound1.mp3", false);
    }else if(2 == tag){
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("wkszMapMenu/1/sound2.mp3", false);
    }
    
}

SEL_MenuHandler MapMenu1Layer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "closeCB", MapMenu1Layer::closeCB);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "tbButtonCB", MapMenu1Layer::tableCB);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "gameCB", MapMenu1Layer::gameCB);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE( this, "m1b2CB", MapMenu1Layer::showMenu1);

	return NULL;
}

extension::SEL_CCControlHandler MapMenu1Layer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "playSound", MapMenu1Layer::controlButtonTest );
	return NULL;
}

bool MapMenu1Layer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_table1", CCSprite*, m_table1 );
	CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_table2", CCSprite*, m_table2 );
    
    
	return false;
}