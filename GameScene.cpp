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
    //时刻更新风向，并显示
    if(m_player->getChildByTag(ObjectTag_WindLb))
        ((Label *)(m_player->getChildByTag(ObjectTag_WindLb)))->setString(StringUtils::format("Wind: %ds",_wind));
    
    /* wind tag */
    auto wind = Label::createWithSystemFont("", "Atlas", 30);
    wind->setPosition(0,2400);
    wind->setScale(3);
    m_player->addChild(wind,3,ObjectTag_WindLb);
    
    /* player round */
    // getfini 用来获取玩家回合是否已结束
    // 没有结束时，返回false，所以为玩家回合
    if( m_player->getfini() == false){
        //执行玩家的逻辑回合
        m_player->logic(dt);
        //若有敌人，执行敌人的逻辑回合
        if(this->getChildByTag(ObjectTag_Enemy))
            ((Enemy *)(this->getChildByTag(ObjectTag_Enemy)))->logic(dt);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        //跟随视角判断
        if(this->getChildByTag(ObjectTag_Player)&&this->getChildByTag(ObjectTag_BG))
        {
            auto Player = this->getChildByTag(ObjectTag_Player);
            //跟踪视角，若没有到地图边界则跟踪，否则不跟踪
            auto BG = this->getChildByTag(ObjectTag_BG);
            if((Player->getPosition().x-visibleSize.width)>(-BG->getContentSize().width/2)&&(Player->getPosition().x+visibleSize.width)<BG->getContentSize().width/2)
                this->setPosition(visibleSize.width/2-Player->getPosition().x,this->getPosition().y);
        }
        time_counter++;
        
        //用来记录回合剩余时间
        if((time_counter%50 == 0)&&(m_player->getChildByTag(ObjectTag_Time)))
            m_player->removeChildByTag(ObjectTag_Time);
        if(this->getChildByTag(ObjectTag_Enemy)||this->getChildByTag(ObjectTag_Boss)){
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
        //如果时间倒了的话，结束玩家回合
        if(time_counter%1000 == 0 && (this->getChildByTag(ObjectTag_Enemy)||this->getChildByTag(ObjectTag_Boss)))
        {
            m_player->setfini(true);
        }
    }
    //玩家结束后进入敌人游戏回合
    else if( m_player->getfini() == true && (this->getChildByTag(ObjectTag_Enemy)||this->getChildByTag(ObjectTag_Boss)))
    {
        m_player->getPhysicsBody()->setVelocity(Vec2::ZERO);
        time_counter = 0;
        if(this->getChildByTag(ObjectTag_Enemy)&&(!this->getChildByTag(ObjectTag_Bullet)))
        {
            this->getChildByTag(ObjectTag_Enemy)->getPhysicsBody()->setVelocity(Vec2::ZERO);
            ((Enemy*)this->getChildByTag(ObjectTag_Enemy))->Attack();
        }
        if(this->getChildByTag(ObjectTag_Boss)&&(!this->getChildByTag(ObjectTag_Bullet)))
        {
            this->getChildByTag(ObjectTag_Boss)->getPhysicsBody()->setVelocity(Vec2::ZERO);
            ((Boss*)this->getChildByTag(ObjectTag_Boss))->Attack();
        }
        //m_player->setfini(false);
    }
    
    //实时更新金钱
    ((Label *)(m_player->getChildByTag(ObjectTag_Money)))->setString(StringUtils::format("Money: %d$",m_player->getmoney()));
    
    //风力则是每时对子弹加一个固定的冲力即可
    
    if(this->getChildByTag(ObjectTag_Bullet))
    {
        this->getChildByTag(ObjectTag_Bullet)->getPhysicsBody()->applyImpulse(Vec2(_wind, 0));
    }
    
    //敌人的创建
    if(!this->getChildByTag(ObjectTag_Enemy)&&_killed<1)
    {
        /* 创建敌人 */
        auto enemy = Enemy::create();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        enemy->setPosition(Point(visibleSize.width * 0.75f, 15));
        this->addChild(enemy, 5, ObjectTag_Enemy);
        _killed += 1;
    }
    
    //boss的判断
    if(!this->getChildByTag(ObjectTag_Boss)&&!this->getChildByTag(ObjectTag_Enemy))
    {
        auto enemy = Boss::create();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        enemy->setPosition(Point(visibleSize.width * 0.75f, 15));
        this->addChild(enemy, 5, ObjectTag_Boss);
    }
    
    //不让boss移动
    if(this->getChildByTag(ObjectTag_Boss))
    {
        this->getChildByTag(ObjectTag_Boss)->getPhysicsBody()->setVelocity(Vec2(0, this->getChildByTag(ObjectTag_Boss)->getPhysicsBody()->getVelocity().y));
    }
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    
    /* 创建主角 */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_player = Player::create();
    m_player->setPosition(Point(visibleSize.width * 0.5f, 18));
    this->addChild(m_player, 6, ObjectTag_Player);
    
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
    
    /* shop button */
    auto shopButton = MenuItemImage::create("menu/shop.png", "menu/shop_0.png", CC_CALLBACK_1(GameScene::OnClickShop, this));
    shopButton->setScale(1.7);
    shopButton->setPosition(Director::getInstance()->convertToGL(Vec2(0,780)));
    
    //创建菜单
    Menu * mu = Menu::create(gameButton, gameReturnButton, shopButton, NULL);
    mu->setPosition(Vec2(-1750,2250));
    m_player->addChild(mu,1);
    
    //add strength saving icon
    auto ssBar = Strength_Saving_Icon::create();
    ssBar->setPosition(Vec2(0, 2280));
    ssBar->setScale(3);
    m_player->addChild(ssBar, 10, ObjectTag_SSI);
    
    // 背景设置
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
    // 检测是否是子弹发生了碰撞
    if(nodeB->getTag() == ObjectTag_Bullet)
    {
        
        //如果另一个物体是玩家
        if(nodeA->getTag() == ObjectTag_Player)
        {
            Player * player = (Player *)nodeA;
            //玩家受到50点攻击
            player->getAttack(50);
        }
        else if(nodeA->getTag() == ObjectTag_Enemy)
        {
            //如果是敌人的话，根据玩家武器的攻击力来对其造成伤害
            Enemy * enemy = (Enemy *)nodeA;
            enemy->getAttack(((Weapon *)(this->getChildByTag(ObjectTag_Player)->getChildByTag(ObjectTag_Weapon)))->getatt());
        }
        else if(nodeA->getTag() == ObjectTag_Boss)
        {
            //如果是boss的话同样
            Boss * boss = (Boss *)nodeA;
            boss->getAttack(((Weapon *)(this->getChildByTag(ObjectTag_Player)->getChildByTag(ObjectTag_Weapon)))->getatt());
        }
        //这里是子弹爆炸时的5毛钱特效，粒子系统
        auto explode = ParticleSun::create();
        explode->setTexture(Director::getInstance()->getTextureCache()->addImage("explode.png"));
        explode->setPosition(nodeB->getPosition());
        explode->setDuration(0.5);
        explode->setLife(0.1);
        if(this->getChildByTag(ObjectTag_Explode)!=NULL)
            this->removeChildByTag(ObjectTag_Explode);
        this->addChild(explode, 30, ObjectTag_Explode);
        //销毁子弹并更换回合
        nodeB->removeFromParent();
        if(!m_player->getfini()&&(this->getChildByTag(ObjectTag_Enemy)||this->getChildByTag(ObjectTag_Boss)))
            m_player->setfini(true);
        else if(m_player->getfini())
            m_player->setfini(false);
        srand( (unsigned)time( NULL ) );
        _wind = rand()%200-100;
    }
    //逻辑同上
    else if(nodeA->getTag() == ObjectTag_Bullet)
    {
        
        if(nodeB->getTag() == ObjectTag_Player)
        {
            Player * player = (Player *)nodeB;
            player->getAttack(100);
        }
        else if(nodeB->getTag() == ObjectTag_Enemy)
        {
            Enemy * enemy = (Enemy *)nodeB;
            if(this->getChildByTag(ObjectTag_Player))
                enemy->getAttack(((Weapon *)(this->getChildByTag(ObjectTag_Player)->getChildByTag(ObjectTag_Weapon)))->getatt());
        }
        else if(nodeB->getTag() == ObjectTag_Boss)
        {
            Boss * boss = (Boss *)nodeB;
            boss->getAttack(((Weapon *)(this->getChildByTag(ObjectTag_Player)->getChildByTag(ObjectTag_Weapon)))->getatt());
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
        if(!m_player->getfini()&&(this->getChildByTag(ObjectTag_Enemy)||this->getChildByTag(ObjectTag_Boss)))
            m_player->setfini(true);
        else if(m_player->getfini())
            m_player->setfini(false);
        _wind = rand()%200-100;
    }
    return true;
    
}

void GameScene::onEnter()
{
    Layer::onEnter();
    
    // update money
    m_player->setmoney(_money);

    //update hp
    m_player->setiHP(((m_player->getiHP()+_recover)>100 ? 100 : m_player->getiHP()+_recover));
    ProgressTimer* pT = (ProgressTimer*)m_player->getChildByTag(ObjectTag_HP)->getChildByTag(ObjectTag_PT);
    int res = 100*m_player->getiHP()/m_player->getrHP();
    pT->setPercentage(res);
    _recover = 0;
    //在进入场景时，执行更新场景的函数
    this->schedule(schedule_selector(GameScene::logic));
    
    this->scheduleUpdate();
    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
    //退出的时候取消事件监听
    _eventDispatcher->removeEventListenersForTarget(this);
    _money = m_player->getmoney();
}

void GameScene::OnClickReturn(cocos2d::Ref *pSender)
{
    //场景切换
    Director::getInstance()->popScene();
}

void GameScene::OnClickReStart(cocos2d::Ref *pSender)
{
    //场景切换
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void GameScene::OnClickShop(cocos2d::Ref *pSender)
{
    //场景切换
    auto sc = ShopScene::createScene();
    Director::getInstance()->pushScene(sc);
}

int GameScene::GetMoney()
{
    return m_player->getmoney();
}
