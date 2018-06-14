//
//  Boss.cpp
//  helloworld
//
//  Created by 张智昊 on 12/06/2018.
//
//

#include "Boss.hpp"


Boss::Boss()
{
    this->setiHP(BOSS_HP);
    this->setmHP(BOSS_HP);
}

Boss::~Boss()
{
    this->removeFromParent();
}

bool Boss::init()
{
    if(!Node::init())
        return false;
    
    
    Sprite * Boss = Sprite::create(BOSS_PATH);
    Boss->setScale(1);
    Boss->setFlippedX(0);
    this->addChild(Boss,20,ObjectTag_BossSp);
    
    
    // physic body added
    
    auto body = PhysicsBody::createBox(Size(300, 450));
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1.0f);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    this->setPhysicsBody(body);
    
    //add hp icon
    auto hpIcon = Hp_Icon::create();
    hpIcon->setScale(3,1);
    hpIcon->setPosition(Vec2(0, 150));
    this->addChild(hpIcon, 10, ObjectTag_HP);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    pT->setPercentage(100);
    this->setTag(ObjectTag_Player);
    
    return true;
}

void Boss::logic(float dt)
{
    this->getPhysicsBody()->setVelocity(Vec2(0, this->getPhysicsBody()->getVelocity().y));
}

void Boss::getAttack(int harm)
{
    this->setiHP(this->getiHP()-harm);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    int res = 100*this->getiHP()/this->getmHP();
    pT->setPercentage(res);
    if(this->getiHP()<=0)
    {
        Player * player = ((Player *)(this->getParent()->getChildByTag(ObjectTag_Player)));
        player->setmoney(player->getmoney()+500);
        this->removeFromParent();
    }
}

void Boss::Attack()
{
    // boss 的攻击逻辑，三颗子弹
    auto bullet = Bullet::create(THUNDER_PATH);
    srand( (unsigned)time( NULL ) );
    double strength;
    if(this->getParent()&&this->getParent()->getChildByTag(ObjectTag_Player))
        strength = (this->getPosition().x-this->getParent()->getChildByTag(ObjectTag_Player)->getPosition().x)*1+rand()%200+_wind*15;
    int angle = 45;
    double angel_x = cos((double(angle)/180)*M_PI);
    double angel_y = sin((double(angle)/180)*M_PI);
    bullet->setPosition(Vec2(this->getPosition().x-170,this->getPosition().y-50));
    bullet->getPhysicsBody()->applyImpulse(Vec2(-(BASE_STRENGTH*strength*angel_x), BASE_STRENGTH*strength*angel_y));
    this->getParent()->addChild(bullet);
    
    auto bullet1 = Bullet::create(THUNDER_PATH);
    srand( (unsigned)time( NULL ) );
    if(this->getParent()&&this->getParent()->getChildByTag(ObjectTag_Player))
        strength = (this->getPosition().x-this->getParent()->getChildByTag(ObjectTag_Player)->getPosition().x)*0.7+rand()%200+_wind*15;
    angle = 45;
    angel_x = cos((double(angle)/180)*M_PI);
    angel_y = sin((double(angle)/180)*M_PI);
    bullet1->setPosition(Vec2(this->getPosition().x-170,this->getPosition().y+50));
    bullet1->getPhysicsBody()->applyImpulse(Vec2(-(BASE_STRENGTH*strength*angel_x), BASE_STRENGTH*strength*angel_y));
    this->getParent()->addChild(bullet1);
    
    auto bullet2 = Bullet::create(THUNDER_PATH);
    srand( (unsigned)time( NULL ) );
    if(this->getParent()&&this->getParent()->getChildByTag(ObjectTag_Player))
        strength = (this->getPosition().x-this->getParent()->getChildByTag(ObjectTag_Player)->getPosition().x)*0.3+rand()%200+_wind*15;
    angle = 45;
    angel_x = cos((double(angle)/180)*M_PI);
    angel_y = sin((double(angle)/180)*M_PI);
    bullet2->setPosition(Vec2(this->getPosition().x-170,this->getPosition().y+150));
    bullet2->getPhysicsBody()->applyImpulse(Vec2(-(BASE_STRENGTH*strength*angel_x), BASE_STRENGTH*strength*angel_y));
    this->getParent()->addChild(bullet2);
}
