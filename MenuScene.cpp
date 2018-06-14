//
//  menu.cpp
//  helloworld
//
//  Created by 张智昊 on 07/06/2018.
//
//

#include "MenuScene.hpp"

int _money = 800;
bool _weapon1 = 1;
bool _weapon2 = 0;
bool _weapon3 = 0;


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
    //我们的第一个菜单页面，加入开始游戏按钮
    
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
    //切换到游戏场景
    auto sc = GameScene::createScene();
    
    Director::getInstance()->pushScene(sc);
}
