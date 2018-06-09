//
//  menu.cpp
//  helloworld
//
//  Created by 张智昊 on 07/06/2018.
//
//

#include "MenuScene.hpp"

Scene * MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}



bool MenuScene::init()
{
    if(!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite * bg = Sprite::create(MENU_BG_PATH);
    bg->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    
    auto gameButton = MenuItemImage::create("menu/home1_0.png", "menu/home1.png", CC_CALLBACK_1(MenuScene::OnClickStart, this));
    gameButton->setScale(0.5);
    gameButton->setPosition(Director::getInstance()->convertToGL(Vec2(480,320)));
    
    
    Menu * mu = Menu::create(gameButton, NULL);
    mu->setPosition(Vec2::ZERO);
    this->addChild(mu,1);
    
    this->addChild(bg,0,ObjectTag_BG);
    
    return true;
}

void MenuScene::OnClickStart(cocos2d::Ref *pSender)
{
    auto sc = GameScene::createScene();
    
    Director::getInstance()->pushScene(sc);
}
