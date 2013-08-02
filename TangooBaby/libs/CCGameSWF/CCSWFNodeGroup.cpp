//
//  CCSWFNodeGroup.cpp
//  TangooBaby
//
//  Created by chenee on 13-5-20.
//  Copyright chenee543216@gmail.com 2013. All rights reserved.
//

#import "CCSWFNodeGroup.h"

CCSWFNodeGroup::CCSWFNodeGroup()
{
    isSingleton = true;
}
CCSWFNodeGroup::~CCSWFNodeGroup()
{
    CCLOG("delete group");
   
    stopAction();
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
}
void CCSWFNodeGroup::addChild(cocos2d::CCNode *child,int zOrder)
{
    CCNode::addChild(child,zOrder);
    ((CCSWFNode*)child)->setGrouped(true);
}
void CCSWFNodeGroup::addChild(cocos2d::CCNode *child)
{
    this->addChild(child, 0);
}

void CCSWFNodeGroup::setFlipX(bool flipX)
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        pNode->setFlipX(flipX);
    }
}
void CCSWFNodeGroup::setFlipY(bool flipY)
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        pNode->setFlipX(flipY);
    }
}
float CCSWFNodeGroup::scale()
{
}

void CCSWFNodeGroup::setScale(float scale)
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        pNode->setScale(scale);
    }
}

float CCSWFNodeGroup::scaleX()
{
}

void CCSWFNodeGroup::setScaleX(float scaleX)
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        pNode->setScaleX(scaleX);
    }
}

float CCSWFNodeGroup::scaleY()
{
    return 1.0f;
}

void CCSWFNodeGroup::setScaleY(float scaleY)
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        pNode->setScaleY(scaleY);
    }
}

void CCSWFNodeGroup::runAction(CCSWFNode* swf)
{
    if (isSingleton) {
        CCObject* child;
        CCARRAY_FOREACH(this->getChildren(), child)
        {
            CCSWFNode* pNode = (CCSWFNode*) child;
            if (pNode != swf) {
                pNode->stopAction();
            }
        }
    }
    
    swf->runAction();
}
void CCSWFNodeGroup::stopAction()
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        pNode->stopAction();
    }
}
bool CCSWFNodeGroup::Runing()
{
    CCObject* child;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        CCSWFNode* pNode = (CCSWFNode*) child;
        if(pNode->Runing()){
            return true;
        }
    }
    return false;
}


