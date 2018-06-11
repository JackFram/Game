//
//  Enemy.hpp
//  helloworld
//
//  Created by 张智昊 on 08/06/2018.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <cocos2d.h>
#include "lib.h"
#include "Object_Tag.h"
#include "Hp_Icon.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include <time.h>

USING_NS_CC;
class Enemy: public Node
{
public:
    Enemy();
    ~Enemy();
    virtual bool init() override;
    void logic(float dt);
    void getAttack(int harm);
    CREATE_FUNC(Enemy);
    void Attack();
private:
    CC_SYNTHESIZE(int, e_iHP, iHP);
    CC_SYNTHESIZE(int, e_mHP, mHP);
};

#endif /* Enemy_hpp */
