//
//  Strength_Saving_Icon.hpp
//  helloworld
//
//  Created by 张智昊 on 06/06/2018.
//
//

#ifndef Strength_Saving_Icon_hpp
#define Strength_Saving_Icon_hpp

#include <cocos2d.h>
#include "Object_Tag.h"

class Strength_Saving_Icon : public cocos2d::Node{
public:
    Strength_Saving_Icon();
    ~Strength_Saving_Icon();
    virtual bool init() override;
    CREATE_FUNC(Strength_Saving_Icon);
};


#endif /* Strength_Saving_Icon_hpp */
