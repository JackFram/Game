//
//  Weapon.cpp
//  helloworld
//
//  Created by 张智昊 on 11/06/2018.
//
//

#include "Weapon.hpp"

Weapon::Weapon()
{
    
}

Weapon::Weapon(int weapon_id)
{
    switch (weapon_id) {
        case 1:
            this->setatt(20);
            this->setdef(0.7);
            this->setweapon_path(WEAPON1_PATH);
            this->setbullet_path(BULLET1_PATH);
            break;
            
        case 2:
            this->setatt(400);
            this->setdef(0.1);
            this->setweapon_path(WEAPON2_PATH);
            this->setbullet_path(BULLET2_PATH);
            break;
            
        default:
            break;
    }
}

Weapon::~Weapon()
{
    
}

bool Weapon::init()
{
    if(!Node::init())
        return false;
    Sprite * weapon = Sprite::create(this->getweapon_path());
    weapon->setScale(1.5);
    weapon->setPosition(Vec2(-10, 50));
    this->addChild(weapon,10,ObjectTag_WeaponSp);
    
    return true;
}
