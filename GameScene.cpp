//
//  GameScene.cpp
//  helloworld
//
//  Created by 张智昊 on 04/06/2018.
//
//
#include "GameScene.hpp"
#include <iostream>


TollgateScene::~TollgateScene()
{
}
Scene* TollgateScene::createScene()
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
    
    auto layer = TollgateScene::create();
    scene->addChild(layer, 10);
    
    return scene;
}

void TollgateScene::logic(float dt){
    m_player->logic(dt);
}

bool TollgateScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    /* 创建主角 */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_player = Player::create();
    m_player->setPosition(Point(visibleSize.width * 0.5f, 25));
    this->addChild(m_player, 5, ObjectTag_Player);
    
    //add strength saving icon
    auto ssBar = Strength_Saving_Icon::create();
    this->addChild(ssBar, 10, ObjectTag_SSI);
    
    
    //add shooting line
    auto shoot_line = Sprite::create("blood_full.png");
    auto player_position = ((Player*)this->getChildByTag(ObjectTag_Player))->getPosition();
    shoot_line->setPosition(player_position.x+BULLET_FIRE_DIS, player_position.y+BULLET_FIRE_DIS);
    shoot_line->setAnchorPoint(Vec2(0,0.5));
    shoot_line->setScale(2);
    shoot_line->setRotation(0);
    this->addChild(shoot_line, 20, ObjectTag_Shoot_Line);
    
    
    this->schedule(schedule_selector(TollgateScene::logic));
    
    return true;
}

bool TollgateScene::onContactBegin(PhysicsContact& contact)
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
        nodeB->removeFromParent();
    }
    else if(nodeA->getTag() == ObjectTag_Bullet)
    {
        
        if(nodeB->getTag() == ObjectTag_Player)
        {
            Player * player = (Player *)nodeB;
            player->getAttack(10);
        }
        nodeA->removeFromParent();
    }
    
    return true;
    
}

void TollgateScene::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListenersForTarget(this);
}
