//
//  test.hpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#ifndef test_hpp
#define test_hpp

#pragma once
#include <cocos2d.h>
class Test: public cocos2d::Layer{
public:
    static cocos2d::Scene * createScene();
    virtual bool init() override;
    
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    
    
    CREATE_FUNC(Test);
private:
    static std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::Sprite *sprite;
    
public:
    virtual void update(float delta) override;
};
#endif /* test_hpp */
