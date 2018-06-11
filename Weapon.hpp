//
//  Weapon.hpp
//  helloworld
//
//  Created by 张智昊 on 11/06/2018.
//
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <cocos2d.h>
#include "lib.h"
#include "Object_Tag.h"
#include <string>


USING_NS_CC;

class Weapon: public Node{
public:
    Weapon();
    Weapon(int weapon_id);
    ~Weapon();
    virtual bool init() override;
    static Weapon* create(int weapon_id)
    {
        Weapon *pRet = new(std::nothrow) Weapon(weapon_id);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
private:
    CC_SYNTHESIZE(int, w_att, att);
    CC_SYNTHESIZE(double, w_def, def);
    CC_SYNTHESIZE(std::string, w_path, weapon_path);
    CC_SYNTHESIZE(std::string, b_path, bullet_path);
};

#endif /* Weapon_hpp */
