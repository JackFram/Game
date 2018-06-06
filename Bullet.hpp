//
//  Bullet.hpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "cocos2d.h"
#include "Object_Tag.h"

USING_NS_CC;

class Bullet : public Node
{
public:
    Bullet();
    ~Bullet();
    CREATE_FUNC(Bullet);
    virtual bool init();
    void logic(float dt);
private:
    float born_x;
    float born_y;
};

#endif /* Bullet_hpp */
