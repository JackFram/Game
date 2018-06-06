//
//  Strength_Saving_Icon.cpp
//  helloworld
//
//  Created by 张智昊 on 06/06/2018.
//
//

#include "Strength_Saving_Icon.hpp"

USING_NS_CC;
Strength_Saving_Icon::Strength_Saving_Icon()
{
    
}

Strength_Saving_Icon::~Strength_Saving_Icon(){
    
}

bool Strength_Saving_Icon::init(){
    if(!Node::init())
        return false;
    Sprite *bgSprite = Sprite::create("blood_empty.png");
    this->addChild(bgSprite, 1, 1);
    
    Sprite *ssSprite = Sprite::create("blood_full.png");
    
    auto progressTimer = ProgressTimer::create(ssSprite);
    
    progressTimer->setType(ProgressTimer::Type::BAR);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //从左到右
    progressTimer->setMidpoint(Point(0, 0.5));
    progressTimer->setBarChangeRate(Point(1, 0));
    progressTimer->setVisible(0);
    
    progressTimer->setMidpoint(Point(0, 0.5));
    progressTimer->setBarChangeRate(Point(1, 0));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    progressTimer->setPosition(Vec2(visibleSize.width*0.5f, 400));
    progressTimer->setScale(18, 4);
    progressTimer->setTag(ObjectTag_PT);
    this->addChild(progressTimer, 0);
    
    return true;
}
