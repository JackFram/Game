//
//  exp_icon.hpp
//  helloworld
//
//  Created by 张智昊 on 15/06/2018.
//
//

#ifndef exp_icon_hpp
#define exp_icon_hpp

#include "cocos2d.h"
#include "Object_Tag.h"
#include "lib.h"

class exp_Icon : public cocos2d::Node{
public:
    exp_Icon();
    ~exp_Icon();
    virtual bool init() override;
    CREATE_FUNC(exp_Icon);
};

#endif /* exp_icon_hpp */
