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
#include "Weapon.hpp"

USING_NS_CC;

class Bullet : public Node
{
public:
    Bullet();
    Bullet(std::string path);
    ~Bullet();
    
    
    static Bullet* create(std::string path)
    {
        Bullet *pRet = new(std::nothrow) Bullet(path);
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
    
    
    virtual bool init();
    void logic(float dt);
private:
    float born_x;
    float born_y;
    CC_SYNTHESIZE(std::string, b_path, bullet_path);
};

#endif /* Bullet_hpp */
