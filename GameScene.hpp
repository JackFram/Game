//
//  GameScene.hpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Strength_Saving_Icon.hpp"

USING_NS_CC;
class TollgateScene : public Layer
{
public:
    ~TollgateScene();
    static Scene* createScene();
    CREATE_FUNC(TollgateScene);
    virtual bool init();
    virtual void onExit() override;
    void logic(float dt);
    /* collision detection */
    bool onContactBegin(PhysicsContact& contact);
private:
    Player * m_player;
    bool collision_flag;
};

#endif /* GameScene_hpp */
