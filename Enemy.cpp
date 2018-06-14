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
    //让敌人保持静止
    this->getPhysicsBody()->setVelocity(Vec2(0, this->getPhysicsBody()->getVelocity().y));
}

void Enemy::getAttack(int harm)
{
    //被攻击时的逻辑
    this->setiHP(this->getiHP()-harm);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    int res = 100*this->getiHP()/this->getmHP();
    pT->setPercentage(res);
    if(this->getiHP()<=0)
    {
        Player * player = ((Player *)(this->getParent()->getChildByTag(ObjectTag_Player)));
        player->setmoney(player->getmoney()+100);
        this->removeFromParent();
    }
}

void Enemy::Attack()
{
    //AI进行攻击
    auto bullet = Bullet::create(BULLET0_PATH);
    srand( (unsigned)time( NULL ) );
    double strength;
    if(this->getParent()&&this->getParent()->getChildByTag(ObjectTag_Player))
        strength = (this->getPosition().x-this->getParent()->getChildByTag(ObjectTag_Player)->getPosition().x)*1.3+rand()%200+_wind*2;
    int angle = 45;
    double angel_x = cos((double(angle)/180)*M_PI);
    double angel_y = sin((double(angle)/180)*M_PI);
    bullet->setPosition(Vec2(this->getPosition().x-BULLET_FIRE_DIS,this->getPosition().y+BULLET_FIRE_DIS));
    bullet->getPhysicsBody()->applyImpulse(Vec2(-(BASE_STRENGTH*strength*angel_x), BASE_STRENGTH*strength*angel_y));
    this->getParent()->addChild(bullet);
}
