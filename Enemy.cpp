//
//  Enemy.cpp
//  helloworld
//
//  Created by 张智昊 on 08/06/2018.
//
//

#include "Enemy.hpp"

Enemy::Enemy()
{
    this->setiHP(ENEMY_HP);
    this->setmHP(ENEMY_HP);
}

Enemy::~Enemy()
{
    this->removeFromParent();
}

bool Enemy::init()
{
    if(!Node::init())
        return false;
    
    
    Sprite * enemy = Sprite::create(PLAYER_GROVEL_PATH);
    enemy->setScale(0.25);
    if(_direction == LEFT)
        enemy->setFlippedX(1);
    this->addChild(enemy,20,ObjectTag_EnemySp);
    
    
    // physic body added
    
    auto body = PhysicsBody::createCircle((enemy->getContentSize().width) * 0.075f);
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1.0f);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    this->setPhysicsBody(body);
    
    //add hp icon
    auto hpIcon = Hp_Icon::create();
    hpIcon->setScale(0.25);
    this->addChild(hpIcon, 10, ObjectTag_HP);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    pT->setPercentage(100);
    this->setTag(ObjectTag_Player);
    
    return true;
}

void Enemy::logic(float dt)
{
    this->getPhysicsBody()->setVelocity(Vec2::ZERO);
}

void Enemy::getAttack(int harm)
{
    this->setiHP(this->getiHP()-harm);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    int res = 100*this->getiHP()/this->getmHP();
    pT->setPercentage(res);
}
