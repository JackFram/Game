//
//  menu.hpp
//  helloworld
//
//  Created by 张智昊 on 07/06/2018.
//
//

#ifndef menu_hpp
#define menu_hpp

#include "cocos2d.h"
#include "lib.h"
#include "Object_Tag.h"
#include "GameScene.hpp"

USING_NS_CC;
class MenuScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    void logic(float dt);
    void OnClickStart(Ref * pSender);
    
    CREATE_FUNC(MenuScene);
    /* collision detection */
};

#endif /* menu_hpp */
