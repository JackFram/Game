//
//  Enemy_1_1.cpp
//  helloworld
//
//  Created by 张智昊 on 15/06/2018.
//
//

#include "Enemy_1.hpp"

Enemy_1::Enemy_1()
{
    this->setiHP(ENEMY_HP+130);
    this->setmHP(ENEMY_HP+130);
}

Enemy_1::~Enemy_1()
{
    this->removeFromParent();
}

bool Enemy_1::init()
{
    if(!Node::init())
        return false;
    
    
    Sprite * Enemy_1 = Sprite::create("Player/Enemy_1.png");
    Enemy_1->setScale(0.5);
    Enemy_1->setFlippedX(0);
    this->addChild(Enemy_1,20,ObjectTag_EnemySp);
    
    
    // physic body added
    
    auto body = PhysicsBody::createCircle((Enemy_1->getContentSize().width) * 0.16f);
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1.0f);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    this->setPhysicsBody(body);
    
    //add hp icon
    auto hpIcon = Hp_Icon::create();
    hpIcon->setScale(0.5);
    this->addChild(hpIcon, 10, ObjectTag_HP);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    pT->setPercentage(100);
    this->setTag(ObjectTag_Player);
    
    return true;
}

void Enemy_1::logic(float dt)
{
    //让敌人保持静止
    this->getPhysicsBody()->setVelocity(Vec2(0, this->getPhysicsBody()->getVelocity().y));
}

void Enemy_1::getAttack(int harm)
{
    //被攻击时的逻辑
    this->setiHP(this->getiHP()-harm-(_exp/200)*30);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    int res = 100*this->getiHP()/this->getmHP();
    pT->setPercentage(res);
    if(this->getiHP()<=0)
    {
        Player * player = ((Player *)(this->getParent()->getChildByTag(ObjectTag_Player)));
        player->setmoney(player->getmoney()+700);
        this->removeFromParent();
        _exp += 73;
    }
}

void Enemy_1::Attack()
{
    //AI进行攻击
    auto bullet = Bullet::create(BULLET0_PATH);
    srand( (unsigned)time( NULL ) );
    double strength;
    if(this->getParent()&&this->getParent()->getChildByTag(ObjectTag_Player))
        strength = (this->getPosition().x-this->getParent()->getChildByTag(ObjectTag_Player)->getPosition().x)*2+rand()%200+_wind*2;
    int angle = 45;
    double angel_x = cos((double(angle)/180)*M_PI);
    double angel_y = sin((double(angle)/180)*M_PI);
    bullet->setPosition(Vec2(this->getPosition().x-50,this->getPosition().y+30));
    bullet->getPhysicsBody()->applyImpulse(Vec2(-(BASE_STRENGTH*strength*angel_x), BASE_STRENGTH*strength*angel_y));
    this->getParent()->addChild(bullet);
}
