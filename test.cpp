//
//  test.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//

#include "test.hpp"

USING_NS_CC;

Scene * Test::createScene()
{
    auto scene = Scene::create();
    auto layer = Test::create();
    scene->addChild(layer);
    return scene;
}

bool Test::init()
{
    if(!Layer::init())
    {
        return false;
    }
    sprite = Sprite::create("HelloWorld.png");
    
    sprite->setPosition(Vec2(100,100));
    sprite->setAnchorPoint(Vec2(0,0));
    
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode,Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
        
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };
    
    this->addChild(sprite, 0);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,sprite);
    
    this->scheduleUpdate();
    return true;
}

bool Test::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double Test::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(code))
        return 0;  // Not pressed, so no duration obviously
    
    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void Test::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    //Node::update(delta);
    auto loc = sprite->getPosition();
    Vec2 update_loc(loc);
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
        update_loc.x = loc.x;
        update_loc.y = loc.y+3;
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
        update_loc.x = loc.x+3;
        update_loc.y = loc.y;
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
        update_loc.x = loc.x;
        update_loc.y = loc.y-3;
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
        update_loc.x = loc.x-3;
        update_loc.y = loc.y;
    }
    sprite->setPosition(update_loc);
}

std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::high_resolution_clock::time_point> Test::keys;

