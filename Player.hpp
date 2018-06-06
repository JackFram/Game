//
//  Player.hpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#ifndef Player_H
#define Player_H
#include "cocos2d.h"
#include "Bullet.hpp"
#include "Object_Tag.h"
#include "Hp_Icon.hpp"
#include "Strength_Saving_Icon.hpp"
#include "lib.h"
#include <math.h>


USING_NS_CC;
class Player : public Node
{
public:
    Player();
    ~Player();
    CREATE_FUNC(Player);
    virtual bool init();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    void moveToRight();
    void moveToLeft();
    void shoot();
    void logic(float dt);
    void getAttack(int harm);
private:
    static std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::Sprite *playerSp;
    Hp_Icon *hpIcon;
    bool shoot_flag = 0;
    CC_SYNTHESIZE(int, m_iHP, iHP);
    CC_SYNTHESIZE(int, m_rHP, rHP);
    CC_SYNTHESIZE(int, m_original_angle, original_angle);
    CC_SYNTHESIZE(int, m_changed_angle, changed_angle);
};
#endif
