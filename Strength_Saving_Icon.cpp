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
    Sprite *bgSprite = Sprite::create("Player/blood_empty.png");
    this->addChild(bgSprite, 0, 1);
    
    Sprite *ssSprite = Sprite::create("Player/blood_full.png");
    
    auto progressTimer = ProgressTimer::create(ssSprite);
    
    progressTimer->setType(ProgressTimer::Type::BAR);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //从左到右
    progressTimer->setMidpoint(Point(0, 0.5));
    progressTimer->setBarChangeRate(Point(1, 0));
        
    progressTimer->setMidpoint(Point(0, 0.5));
    progressTimer->setBarChangeRate(Point(1, 0));
    
    
    progressTimer->setPosition(Vec2(0, 2400));
    progressTimer->setScale(80, 16);
    progressTimer->setTag(ObjectTag_PT);
    this->addChild(progressTimer, 0);
    
    return true;
}
