//
//  Boss.hpp
//  helloworld
//
//  Created by 张智昊 on 12/06/2018.
//
//

#ifndef Boss_hpp
#define Boss_hpp

#include <cocos2d.h>
#include "lib.h"
#include "Object_Tag.h"
#include "Hp_Icon.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include <time.h>

USING_NS_CC;
class Boss: public Node
{
public:
    Boss();
    ~Boss();
    virtual bool init() override;
    void logic(float dt);
    void getAttack(int harm);
    CREATE_FUNC(Boss);
    void Attack();
private:
    CC_SYNTHESIZE(int, e_iHP, iHP);
    CC_SYNTHESIZE(int, e_mHP, mHP);
};

#endif /* Boss_hpp */
