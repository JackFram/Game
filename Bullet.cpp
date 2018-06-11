//
//  Bullet.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#include "Bullet.hpp"
#include <math.h>
#include "lib.h"
#include "iostream"

USING_NS_CC;

Bullet::~Bullet(){
    
}

Bullet::Bullet(){
    
}

Bullet::Bullet(std::string path)
{
    this->setbullet_path(path);
}


bool Bullet::init()
{
    Sprite * bullet;
    bullet = Sprite::create(this->getbullet_path());
    if(_direction == RIGHT)
        bullet->setFlippedX(1);
    bullet->setScale(BULLET_SCALE);
    bullet->setAnchorPoint(Vec2(0,0.5));
    
    this->addChild(bullet,10,ObjectTag_BulletSp);
    auto body = PhysicsBody::createCircle((bullet->getContentSize().width)*BULLET_SCALE* 0.2f);
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
        Vec2 velocity = this->getPhysicsBody()->getVelocity();
        this->getChildByTag(ObjectTag_BulletSp)->setRotation((atanf(-velocity.y/velocity.x)*180)/M_PI);
        if(velocity.x<0)
            ((Sprite *)(this->getChildByTag(ObjectTag_BulletSp)))->setFlippedX(0);
        else
            ((Sprite *)(this->getChildByTag(ObjectTag_BulletSp)))->setFlippedX(1);

}
