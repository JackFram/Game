//
//  Shop.hpp
//  helloworld
//
//  Created by 张智昊 on 12/06/2018.
//
//

#ifndef Shop_hpp
#define Shop_hpp

#include "cocos2d.h"
#include "lib.h"
#include "Object_Tag.h"
#include "GameScene.hpp"

USING_NS_CC;
class ShopScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    void logic(float dt);
    void OnClickReturn(Ref * pSender);
    void OnClickBuy1(Ref * pSender);
    void OnClickBuy2(Ref * pSender);
    void OnClickBuy3(Ref * pSender);
    
    CREATE_FUNC(ShopScene);
private:
    CC_SYNTHESIZE(int, flag_time, fm);
    
};

#endif /* Shop_hpp */
