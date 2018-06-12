//
//  GameScene.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//
#include "GameScene.hpp"



GameScene::GameScene()
{
    time_counter = 0;
}

GameScene::~GameScene()
{
    
}

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    /* 微重力世界 */
    Vect gravity(0, -600.0f);
    scene->getPhysicsWorld()->setGravity(gravity);
    /* 开启测试模式 */
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //创建一个边界
    Size visibleSize = Director::getInstance()->getVisibleSize();
    /*
     创建一个空心盒子刚体，作为我们游戏世界的边界（避免游戏内的物体跑出屏幕）
     参数分别是刚体大小、材质（其实就是一些预设的配置数据）、边线厚度
     */
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*2, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    /* 创建一个节点，用于承载刚体，这样刚体就能参与到游戏的物理世界 */
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    auto node = Node::create();
    node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    node->setPhysicsBody(body);
    scene->addChild(node);
    
    auto layer = GameScene::create();
    scene->addChild(layer, 10);
    
    return scene;
}

void GameScene::logic(float dt){
    if(m_player->getChildByTag(ObjectTag_WindLb))
        ((Label *)(m_player->getChildByTag(ObjectTag_WindLb)))->setString(StringUtils::format("Wind: %ds",_wind));
    auto wind = Label::createWithSystemFont("", "Atlas", 30);
    wind->setPosition(0,2400);
    wind->setScale(3);
    m_player->addChild(wind,3,ObjectTag_WindLb);
    if(m_player->getParent()&&m_player->getParent()->getChildByTag(ObjectTag_Bullet))
    {
        ((Bullet *)(m_player->getParent()->getChildByTag(ObjectTag_Bullet)))->logic(dt);
    }
    if( m_player->getfini() == false){
        m_player->logic(dt);
        if(this->getChildByTag(ObjectTag_Enemy))
            ((Enemy *)(this->getChildByTag(ObjectTag_Enemy)))->logic(dt);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        if(this->getChildByTag(ObjectTag_Player)&&this->getChildByTag(ObjectTag_BG))
        {
            auto Player = this->getChildByTag(ObjectTag_Player);
            //跟踪视角
            auto BG = this->getChildByTag(ObjectTag_BG);
            if((Player->getPosition().x-visibleSize.width)>(-BG->getContentSize().width/2)&&(Player->getPosition().x+visibleSize.width)<BG->getContentSize().width/2)
                this->setPosition(visibleSize.width/2-Player->getPosition().x,this->getPosition().y);
        }
        time_counter++;
        
        //show round time 
        if((time_counter%50 == 0)&&(m_player->getChildByTag(ObjectTag_Time)))
            m_player->removeChildByTag(ObjectTag_Time);
        if(this->getChildByTag(ObjectTag_Enemy)){
            if(time_counter%100 == 0)
            {
                auto layer_time = Label::createWithSystemFont("Time Left: 10s", "Atlas", 30);
                layer_time->setScale(2);
                layer_time->setPosition(Vec2(0,1500));
                layer_time->setColor(Color3B(249, 10, 10));
                layer_time->setString(StringUtils::format("Time Left: %ds",10-time_counter/100));
                m_player->addChild(layer_time, 2, ObjectTag_Time);
            }
        }
        if(time_counter%1000 == 0 && this->getChildByTag(ObjectTag_Enemy))
        {
            m_player->setfini(true);
        }
    }
    else if( m_player->getfini() == true && this->getChildByTag(ObjectTag_Enemy))
    {
        m_player->getPhysicsBody()->setVelocity(Vec2::ZERO);
        time_counter = 0;
        if(this->getChildByTag(ObjectTag_Enemy)&&(!this->getChildByTag(ObjectTag_Bullet)))
        {
            this->getChildByTag(ObjectTag_Enemy)->getPhysicsBody()->setVelocity(Vec2::ZERO);
            ((Enemy*)this->getChildByTag(ObjectTag_Enemy))->Attack();
        }
        //m_player->setfini(false);
    }
    ((Label *)(m_player->getChildByTag(ObjectTag_Money)))->setString(StringUtils::format("Money: %d",m_player->getmoney()));
    
    //wind added to bullet
    
    if(this->getChildByTag(ObjectTag_Bullet))
    {
        this->getChildByTag(ObjectTag_Bullet)->getPhysicsBody()->applyImpulse(Vec2(_wind, 0));
    }
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    /* 创建主角 */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_player = Player::create();
    m_player->setPosition(Point(visibleSize.width * 0.5f, 18));
    this->addChild(m_player, 5, ObjectTag_Player);
    
    /* 创建敌人 */
    auto enemy = Enemy::create();
    enemy->setPosition(Point(visibleSize.width * 0.75f, 15));
    this->addChild(enemy, 5, ObjectTag_Enemy);
    
    /* 钻石数量 */
    auto layer_money = Label::createWithSystemFont("Money: 0", "Arial", 30);
    layer_money->setScale(2);
    layer_money->setPosition(Vec2(1650,2400));
    layer_money->setString(StringUtils::format("Money: %d",1));
    layer_money->setTag(ObjectTag_Money);
    m_player->addChild(layer_money, 2);
    
    /* return button */
    auto gameButton = MenuItemImage::create("menu/return_0.png", "menu/return.png", CC_CALLBACK_1(GameScene::OnClickReturn, this));
    gameButton->setScale(0.75);
    gameButton->setPosition(Director::getInstance()->convertToGL(Vec2(0,480)));
    
    /* restart button */
    auto gameReturnButton = MenuItemImage::create("menu/game3_0.png", "menu/game3.png", CC_CALLBACK_1(GameScene::OnClickReStart, this));
    gameReturnButton->setScale(0.8);
    gameReturnButton->setPosition(Director::getInstance()->convertToGL(Vec2(0,580)));
    
    Menu * mu = Menu::create(gameButton, gameReturnButton, NULL);
    mu->setPosition(Vec2(-1750,2250));
    m_player->addChild(mu,1);
    
    //add strength saving icon
    auto ssBar = Strength_Saving_Icon::create();
    m_player->addChild(ssBar, 10, ObjectTag_SSI);
    
    Sprite * bg = Sprite::create(SCENE1_MAP_PATH);
    bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(bg , 0, ObjectTag_BG);
    
    
    //add shooting line
    auto shoot_line = Sprite::create(SHOOT_LINE_PATH);
    auto player_position = ((Player*)this->getChildByTag(ObjectTag_Player))->getPosition();
    shoot_line->setAnchorPoint(Vec2(0,0.5));
    shoot_line->setPosition(player_position.x, player_position.y);
    shoot_line->setScale(1,2);
    shoot_line->setRotation(0);
    this->addChild(shoot_line, 20, ObjectTag_Shoot_Line);
    
    //particle system
    this->setTag(ObjectTag_GameScene);
    
    this->schedule(schedule_selector(GameScene::logic));

    return true;
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    /* collision detection */
    auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();
    if (nodeA == NULL || nodeB == NULL)
    {
        return true;
    }
    
    if(nodeB->getTag() == ObjectTag_Bullet)
    {
        
        if(nodeA->getTag() == ObjectTag_Player)
        {
            Player * player = (Player *)nodeA;
            player->getAttack(10);
        }
        else if(nodeA->getTag() == ObjectTag_Enemy)
        {
            Enemy * enemy = (Enemy *)nodeA;
            enemy->getAttack(10);
        }
        auto explode = ParticleSun::create();
        explode->setTexture(Director::getInstance()->getTextureCache()->addImage("explode.png"));
        explode->setPosition(nodeB->getPosition());
        explode->setDuration(0.5);
        explode->setLife(0.1);
        if(this->getChildByTag(ObjectTag_Explode)!=NULL)
            this->removeChildByTag(ObjectTag_Explode);
        this->addChild(explode, 30, ObjectTag_Explode);
        nodeB->removeFromParent();
        if(!m_player->getfini()&&this->getChildByTag(ObjectTag_Enemy))
            m_player->setfini(true);
        else if(m_player->getfini())
            m_player->setfini(false);
        _wind = -_wind;
    }
    else if(nodeA->getTag() == ObjectTag_Bullet)
    {
        
        if(nodeB->getTag() == ObjectTag_Player)
        {
            Player * player = (Player *)nodeB;
            player->getAttack(10);
        }
        else if(nodeB->getTag() == ObjectTag_Enemy)
        {
            Enemy * enemy = (Enemy *)nodeB;
            if(this->getChildByTag(ObjectTag_Player))
                enemy->getAttack(((Weapon *)(this->getChildByTag(ObjectTag_Player)->getChildByTag(ObjectTag_Weapon)))->getatt());
        }
        auto explode = ParticleSun::create();
        explode->setTexture(Director::getInstance()->getTextureCache()->addImage("explode.png"));
        explode->setPosition(nodeA->getPosition());
        explode->setDuration(0.5);
        explode->setLife(0.1);
        if(this->getChildByTag(ObjectTag_Explode)!=NULL)
            this->removeChildByTag(ObjectTag_Explode);
        this->addChild(explode, 30, ObjectTag_Explode);
        nodeA->removeFromParent();
        if(!m_player->getfini()&&this->getChildByTag(ObjectTag_Enemy))
            m_player->setfini(true);
        else if(m_player->getfini())
            m_player->setfini(false);
        _wind = -_wind;
    }
    return true;
    
}

void GameScene::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListenersForTarget(this);
}

void GameScene::OnClickReturn(cocos2d::Ref *pSender)
{
    
    Director::getInstance()->popScene();
}

void GameScene::OnClickReStart(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
