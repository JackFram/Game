//
//  Bullet.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#include "Bullet.hpp"
#include "lib.h"

USING_NS_CC;

Bullet::~Bullet(){
    
}

Bullet::Bullet(){
    
}


bool Bullet::init()
{
    auto bullet = Sprite::create("test.png");
    
    bullet->setScale(BULLET_SCALE);
    
    this->addChild(bullet);
    auto body = PhysicsBody::createCircle((bullet->getContentSize().width)*BULLET_SCALE* 0.4f);
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1.0f);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    this->setPhysicsBody(body);
    this->setTag(ObjectTag_Bullet);
    /* 给子弹添加推力 */
    return true;
}

void Bullet::logic(float dt)
{
    
}
