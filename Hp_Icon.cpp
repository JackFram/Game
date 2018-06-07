//
//  Hp_Icon.cpp
//  helloworld
//
//  Created by 张智昊 on 05/06/2018.
//
//

#include "Hp_Icon.hpp"
USING_NS_CC;
Hp_Icon::Hp_Icon()
{
    
}

Hp_Icon::~Hp_Icon(){
    
}

bool Hp_Icon::init(){
    if(!Node::init())
        return false;
    Sprite *bgSprite = Sprite::create(BLOOD_EMPTY_PATH);
    bgSprite->setPosition(Vec2(0, 140));
    bgSprite->setScale(4);
    this->addChild(bgSprite, 1, 1);
    
    Sprite *hpSprite = Sprite::create(BLOOD_FULL_PATH);
    
    auto progressTimer = ProgressTimer::create(hpSprite);
    
    progressTimer->setType(ProgressTimer::Type::BAR);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //从左到右
    progressTimer->setMidpoint(Point(0, 0.5));
    progressTimer->setBarChangeRate(Point(1, 0));
    
    progressTimer->setMidpoint(Point(0, 0.5));
    progressTimer->setBarChangeRate(Point(1, 0));
    
    progressTimer->setPosition(Vec2(0, 140));
    progressTimer->setScale(4);
    progressTimer->setTag(ObjectTag_PT);
    this->addChild(progressTimer, 2);
    
    return true;
}

