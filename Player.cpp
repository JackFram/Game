//
//  Player.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#include "Player.hpp"
#include "lib.h"

Player::Player()
{
    m_iHP = PLAYER_HP;
    m_rHP = PLAYER_HP;
    m_original_angle = 0;
    m_finished = false;
}

Player::~Player()
{
}
bool Player::init()
{
    /* player img load */
    playerSp = Sprite::create(PLAYER_GROVEL_PATH);
    this->setScale(0.25);
    if(_direction == LEFT)
        playerSp->setFlippedX(1);
    this->addChild(playerSp,20,ObjectTag_PlayerSp);
    
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode,Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
        // lock up our key
        
        if(keyCode == EventKeyboard::KeyCode::KEY_SPACE&&!this->getfini())
        {
            this->removeChildByTag(ObjectTag_PlayerSp);
            playerSp = Sprite::create(PLAYER_STAND_PATH);
            this->setScale(0.25);
            if(_direction == LEFT)
                playerSp->setFlippedX(1);
            this->addChild(playerSp,20,ObjectTag_PlayerSp);
        }
    };
    
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        // unlock our key
        if(keyCode == EventKeyboard::KeyCode::KEY_SPACE&&!this->getfini())
        {
            this->shoot();
            this->removeChildByTag(ObjectTag_PlayerSp);
            playerSp = Sprite::create(PLAYER_GROVEL_PATH);
            this->setScale(0.25);
            if(_direction == LEFT)
                playerSp->setFlippedX(1);
            this->addChild(playerSp,20,ObjectTag_PlayerSp);
        }
        if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW||keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
        {
            int angle = this->getchanged_angle();
            this->setoriginal_angle(angle);
        }
        keys.erase(keyCode);
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
    
    // physic body added

    auto body = PhysicsBody::createCircle((playerSp->getContentSize().width) * 0.3f);
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1.0f);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    this->setPhysicsBody(body);
    
    //add hp icon
    hpIcon = Hp_Icon::create();
    this->addChild(hpIcon, 10, ObjectTag_HP);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    pT->setPercentage(100);
    this->setTag(ObjectTag_Player);

    return true;
}

bool Player::isKeyPressed(EventKeyboard::KeyCode code) {
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double Player::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(code))
        return 0;  // Not pressed, so no duration obviously
    
    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::high_resolution_clock::now() - keys[code]).count();
}


std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::high_resolution_clock::time_point> Player::keys;

void Player::moveToRight()
{
    //this->getPhysicsBody()->applyImpulse(Vect(50000, 0));
    this->getPhysicsBody()->setVelocity(Vec2(150, this->getPhysicsBody()->getVelocity().y));
}
void Player::moveToLeft()
{
    this->getPhysicsBody()->setVelocity(Vec2(-150, this->getPhysicsBody()->getVelocity().y));
}
void Player::shoot()
{
    auto bullet = Bullet::create();
    double strength = keyPressedDuration(EventKeyboard::KeyCode::KEY_SPACE);
    strength = (strength>800) ? 800 : strength;
    int angle = this->getchanged_angle();
    //angle=angle%360;
    double angel_x = cos((double(angle)/180)*M_PI);
    double angel_y = sin((double(angle)/180)*M_PI);
    bullet->setPosition(Vec2(this->getPosition().x+_direction*BULLET_FIRE_DIS,this->getPosition().y+BULLET_FIRE_DIS));
    bullet->getPhysicsBody()->applyImpulse(Vec2((BASE_STRENGTH*strength*angel_x), BASE_STRENGTH*strength*angel_y));
    this->getParent()->addChild(bullet);
    ProgressTimer * pt = (ProgressTimer*)this->getChildByTag(ObjectTag_SSI)->getChildByTag(ObjectTag_PT);
    pt->setVisible(0);
    this->setfini(true);
}

void Player::getAttack(int harm)
{
    this->setiHP(this->getiHP()-harm);
    ProgressTimer* pT = (ProgressTimer*)this->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    int res = 100*this->getiHP()/this->getrHP();
    pT->setPercentage(res);
}


void Player::logic(float dt)
{

    
    /* fire line */
    this->getParent()->getChildByTag(ObjectTag_Shoot_Line)->setPosition(this->getPosition().x+BULLET_FIRE_DIS*_direction, this->getPosition().y+BULLET_FIRE_DIS);
    this->getParent()->getChildByTag(ObjectTag_Shoot_Line)->setRotation(-this->getchanged_angle());
    
    
    /* key action */
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
        this->moveToRight();
        if(_direction == LEFT)
        {
            ((Sprite*)(this->getChildByTag(ObjectTag_PlayerSp)))->setFlippedX(0);
            this->setchanged_angle(180-(this->getchanged_angle()));
            this->setoriginal_angle(this->getchanged_angle());
            _direction = RIGHT;
        }
    }//move to right and change our shoot line
    else if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
        this->moveToLeft();
        if(_direction == RIGHT)
        {
            ((Sprite*)this->getChildByTag(ObjectTag_PlayerSp))->setFlippedX(1);
            this->setchanged_angle(180-(this->getchanged_angle()));
            this->setoriginal_angle(this->getchanged_angle());
            _direction = LEFT;
        }
    }//move to left and change our shoot line
    
    //adjust our shooting angle
    else if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
        this->setchanged_angle(this->getoriginal_angle()+_direction*int(90*(keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW)/800)));
    }
    else if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
        this->setchanged_angle(this->getoriginal_angle()-_direction*int(90*(keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW)/800)));
    }
    
    //pressing space to accumulate strength
    else if(isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE)){
        ProgressTimer * pt = (ProgressTimer*)this->getChildByTag(ObjectTag_SSI)->getChildByTag(ObjectTag_PT);
        pt->setVisible(1);
        if(keyPressedDuration(EventKeyboard::KeyCode::KEY_SPACE)>MAX_STRENGTH)
        {
            pt->setPercentage(100);
        }
        else{
            pt->setPercentage(100*keyPressedDuration(EventKeyboard::KeyCode::KEY_SPACE)/MAX_STRENGTH);
        }
    }
    else{
        //set our player to be stable
        auto velocity = this->getPhysicsBody()->getVelocity();
        this->getPhysicsBody()->setVelocity(Vec2(0, velocity.y));
        ProgressTimer * pt = (ProgressTimer*)this->getChildByTag(ObjectTag_SSI)->getChildByTag(ObjectTag_PT);
        pt->setVisible(0);
    }
}
