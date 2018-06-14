//
//  Shop.cpp
//  helloworld
//
//  Created by 张智昊 on 12/06/2018.
//
//

#include "ShopScene.hpp"


Scene * ShopScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}



bool ShopScene::init()
{
    if(!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //背景显示
    Sprite * bg = Sprite::create(SHOP_PATH);
    bg->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    
    
    //武器图标显示
    Sprite * weapon1 = Sprite::create(WEAPON1_PATH);
    Sprite * weapon2 = Sprite::create(WEAPON2_PATH);
    Sprite * weapon3 = Sprite::create(WEAPON3_PATH);
    Sprite * recover = Sprite::create("Weapon/recover.png");
    weapon1->setPosition(Vec2(295, 485));
    weapon2->setPosition(Vec2(295, 340));
    weapon3->setPosition(Vec2(645, 488));
    recover->setPosition(Vec2(645, 340));
    recover->setScale(1.2);
    weapon2->setRotation(-13);
    weapon3->setScale(0.8);
    weapon3->setRotation(-10);
    
    
    auto gameButton = MenuItemImage::create("menu/return_0.png", "menu/return.png", CC_CALLBACK_1(ShopScene::OnClickReturn, this));
    gameButton->setScale(0.4);
    gameButton->setPosition(Director::getInstance()->convertToGL(Vec2(100,120)));
    //购买图标显示
    auto buy_button1 = MenuItemImage::create("menu/buy.png", "menu/buy_0.png", CC_CALLBACK_1(ShopScene::OnClickBuy1, this));
    auto buy_button2 = MenuItemImage::create("menu/buy.png", "menu/buy_0.png", CC_CALLBACK_1(ShopScene::OnClickBuy2, this));
    auto buy_button3 = MenuItemImage::create("menu/buy.png", "menu/buy_0.png", CC_CALLBACK_1(ShopScene::OnClickBuy3, this));
    auto buy_button4 = MenuItemImage::create("menu/buy.png", "menu/buy_0.png", CC_CALLBACK_1(ShopScene::OnClickBuy4, this));
    
    buy_button1->setPosition(Vec2(400, 445));
    buy_button2->setPosition(Vec2(400, 300));
    buy_button3->setPosition(Vec2(750, 446));
    buy_button4->setPosition(Vec2(750, 300));
    
    Menu * mu = Menu::create(gameButton, buy_button1, buy_button2, buy_button3, buy_button4, NULL);
    mu->setPosition(Vec2::ZERO);
    this->addChild(mu,1);
    
    this->addChild(weapon1,1);
    this->addChild(weapon2,1);
    this->addChild(weapon3,1);
    this->addChild(recover,1);
    
    
    //价格显示
    auto layer_1 = Label::createWithTTF("300$", "fonts/arial.ttf", 30);
    layer_1->setScale(1);
    layer_1->setPosition(Vec2(400, 495));
    layer_1->setTag(ObjectTag_Tag);
    this->addChild(layer_1,2);
    
    auto layer_2 = Label::createWithTTF("700$", "fonts/arial.ttf", 30);
    layer_2->setScale(1);
    layer_2->setPosition(Vec2(400, 350));
    layer_2->setTag(ObjectTag_Tag);
    this->addChild(layer_2,2);
    
    auto layer_3 = Label::createWithTTF("900$", "fonts/arial.ttf", 30);
    layer_3->setScale(1);
    layer_3->setPosition(Vec2(750, 496));
    layer_3->setTag(ObjectTag_Tag);
    this->addChild(layer_3,2);
    
    auto layer_4 = Label::createWithTTF("100$", "fonts/arial.ttf", 30);
    layer_4->setScale(1);
    layer_4->setPosition(Vec2(750, 350));
    layer_4->setTag(ObjectTag_Tag);
    this->addChild(layer_4,2);
    
    
    auto layer_money = Label::createWithSystemFont("", "Arial", 30);
    layer_money->setScale(1);
    layer_money->setPosition(Vec2(800, 600));
    layer_money->setTag(ObjectTag_Money);
    this->addChild(layer_money,2);
    this->setfm(0);
    
    
    this->addChild(bg,0,ObjectTag_BG);
    
    this->schedule(schedule_selector(ShopScene::logic));
    
    
    
    return true;
}

//场景切换
void ShopScene::OnClickReturn(cocos2d::Ref *pSender)
{
    Director::getInstance()->popScene();
}


//点击购买时出发
void ShopScene::OnClickBuy1(Ref * pSender)
{
    if(_money<300)
    {
        auto layer_money = Label::createWithSystemFont("You couldn't afford it", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480, 320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else if(_weapon1)
    {
        auto layer_money = Label::createWithSystemFont("You don't need to buy it!", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480,320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else
    {
        _weapon1 = 1;
        _money -= 300;
    }
}

void ShopScene::OnClickBuy2(Ref * pSender)
{
    if(_money<700)
    {
        auto layer_money = Label::createWithSystemFont("You couldn't afford it", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480,320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else if(_weapon2)
    {
        auto layer_money = Label::createWithSystemFont("You don't need to buy it!", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480,320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else
    {
        _weapon2 = 1;
        _money -= 700;
    }
}

void ShopScene::OnClickBuy3(Ref * pSender)
{
    if(_money<900)
    {
        auto layer_money = Label::createWithSystemFont("You couldn't afford it!", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480,320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else if(_weapon3)
    {
        auto layer_money = Label::createWithSystemFont("You don't need to buy it!", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480,320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else
    {
        _weapon3 = 1;
        _money -= 900;
    }
}

void ShopScene::OnClickBuy4(Ref * pSender)
{
    if(_money<100)
    {
        auto layer_money = Label::createWithSystemFont("You couldn't afford it!", "Arial", 30);
        layer_money->setScale(2);
        layer_money->setPosition(Vec2(480,320));
        layer_money->setTag(ObjectTag_Buy);
        this->addChild(layer_money,2);
    }
    else
    {
        _recover += 30;
        _money -= 100;
    }
}

void ShopScene::logic(float dt)
{
    if(this->getChildByTag(ObjectTag_Buy))
    {
        this->setfm(this->getfm()+1);
    }
    if(this->getfm()==20)
    {
        this->setfm(0);
        this->removeChildByTag(ObjectTag_Buy);
    }
    
    if(this->getChildByTag(ObjectTag_Money))
    {
        ((Label *)(this->getChildByTag(ObjectTag_Money)))->setString(StringUtils::format("Money: %d$",_money));
    }
    
}


