//
//  GameScene.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//
#include "GameScene.hpp"


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
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    /* 创建一个节点，用于承载刚体，这样刚体就能参与到游戏的物理世界 */
    auto node = Node::create();
    node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    node->setPhysicsBody(body);
    scene->addChild(node);
    
    auto layer = GameScene::create();
    scene->addChild(layer, 10);
    
    return scene;
}

void GameScene::logic(float dt){
    m_player->logic(dt);
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
    m_player->setPosition(Point(visibleSize.width * 0.5f, 25));
    this->addChild(m_player, 5, ObjectTag_Player);
    
    //add strength saving icon
    auto ssBar = Strength_Saving_Icon::create();
    this->addChild(ssBar, 10, ObjectTag_SSI);
    
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
    this->schedule(schedule_selector(Bullet::logic));
    
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
            auto explode = ParticleSun::create();
            explode->setTexture(Director::getInstance()->getTextureCache()->addImage("explode.png"));
            explode->setPosition(nodeB->getPosition());
            explode->setDuration(0.5);
            explode->setLife(0.1);
            if(this->getChildByTag(ObjectTag_Explode)!=NULL)
                this->removeChildByTag(ObjectTag_Explode);
            this->addChild(explode, 30, ObjectTag_Explode);
            //this->removeChild(explode);
        }
        nodeB->removeFromParent();
        _is_shooting = false;
    }
    else if(nodeA->getTag() == ObjectTag_Bullet)
    {
        
        if(nodeB->getTag() == ObjectTag_Player)
        {
            Player * player = (Player *)nodeB;
            player->getAttack(10);
            auto explode = ParticleSun::create();
            explode->setTexture(Director::getInstance()->getTextureCache()->addImage("explode.png"));
            explode->setPosition(nodeA->getPosition());
            explode->setDuration(0.5);
            explode->setLife(0.1);
            if(this->getChildByTag(ObjectTag_Explode)!=NULL)
                this->removeChildByTag(ObjectTag_Explode);
            this->addChild(explode, 30, ObjectTag_Explode);
            //this->removeChild(explode);
        }
        nodeA->removeFromParent();
        _is_shooting = false;
    }
    
    return true;
    
}

void GameScene::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListenersForTarget(this);
}
