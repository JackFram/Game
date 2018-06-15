//
//  Enemy_1_1.hpp
//  helloworld
//
//  Created by 张智昊 on 15/06/2018.
//
//

#ifndef Enemy_1_1_hpp
#define Enemy_1_1_hpp

#include <cocos2d.h>
#include "lib.h"
#include "Object_Tag.h"
#include "Hp_Icon.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include <time.h>

USING_NS_CC;
class Enemy_1: public Node
{
public:
    Enemy_1();
    ~Enemy_1();
    virtual bool init() override;
    void logic(float dt);
    void getAttack(int harm);
    CREATE_FUNC(Enemy_1);
    void Attack();
private:
    CC_SYNTHESIZE(int, e_iHP, iHP);
    CC_SYNTHESIZE(int, e_mHP, mHP);
};

#endif /* Enemy_1_1_hpp */
