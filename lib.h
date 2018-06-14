//
//  lib.h
//  helloworld
//
//  Created by 张智昊 on 05/06/2018.
//
//

#ifndef lib_h
#define lib_h
#define PLAYER_ROUND  1
#define ENEMY_ROUND  2
#define PLAYER_HP (100)
#define ENEMY_HP  (100)
#define BOSS_HP   (2000)
#define BULLET_FIRE_DIS (20)
#define BULLET_SCALE (0.3)
#define MAX_STRENGTH (1600)
#define BASE_STRENGTH (23)
#define LEFT  (-1)
#define RIGHT (1)
#define BLOOD_FULL_PATH "Player/blood_full.png"
#define BLOOD_EMPTY_PATH "Player/blood_empty.png"
#define SHOOT_LINE_PATH "Player/shoot_line.png"
#define PLAYER_GROVEL_PATH "Player/player_grovel.png"
#define PLAYER_STAND_PATH "Player/player_stand.png"
#define SCENE1_MAP_PATH "background/bg1.jpeg"
#define MENU_BG_PATH "background/bg3.jpg"
#define BULLET0_PATH  "Bullet/bullet1.png"
#define BULLET1_PATH  "Bullet/bullet2.png"
#define BULLET2_PATH  "Bullet/bullet3.png"
#define BULLET3_PATH  "Bullet/bullet4.png"
#define WEAPON1_PATH  "Weapon/weapon4.png"
#define WEAPON2_PATH  "Weapon/weapon.png"
#define WEAPON3_PATH  "Weapon/weapon3.png"
#define BOSS_PATH     "Player/boss.png"
#define THUNDER_PATH  "Bullet/thunder.png"
#define SHOP_PATH     "background/shopScene.png"


static int _direction = RIGHT;
static int _wind = 0;
static int _killed = 0;


#endif /* lib_h */
