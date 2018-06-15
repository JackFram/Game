//
//  exp_icon.cpp
//  helloworld
//
//  Created by 张智昊 on 15/06/2018.
//
//

#include "exp_Icon.hpp"
USING_NS_CC;
exp_Icon::exp_Icon()
{
    
}

exp_Icon::~exp_Icon(){
    
}

bool exp_Icon::init(){
    //创建经验条
    if(!Node::init())
        return false;
    Sprite *bgSprite = Sprite::create("Player/exp_empty.png");
    bgSprite->setPosition(Vec2(0, 140));
    bgSprite->setScale(4);
    this->addChild(bgSprite, 1, 1);
    
    Sprite *hpSprite = Sprite::create("Player/exp_full.png");
    
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
