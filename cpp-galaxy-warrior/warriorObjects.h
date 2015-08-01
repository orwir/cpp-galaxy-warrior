#pragma once

#include "world.h"

using namespace consolity;

static const float PLAYER_STRENGTH = 3;
static const float PLAYER_FIRE_COOLDOWN = 0.23;
static const float PLAYER_SPEED = 25;

static const float INTERCEPTER_STRENGTH = 1;
static const float INTERCEPTER_XSPEED = -10;
static const float INTERCEPTER_YSPEED = 15;
static const float INTERCEPTER_FIRE_COOLDOWN = .78;
static const float INTERCEPTER_WORTH = 2;

static const float HUNTER_STRENGTH = 2;
static const float HUNTER_XSPEED = -5;
static const float HUNTER_YSPEED = 8;
static const float HUNTER_FIRE_COOLDOWN = 1.02;
static const float HUNTER_WORTH = 4;

static const float MAMMOTH_STRENGTH = 8;
static const float MAMMOTH_XSPEED = -1;
static const float MAMMOTH_YSPEED = 4;
static const float MAMMOTH_FIRE_COOLDOWN = .9;
static const float MAMMOTH_WORTH = 9;

static const float MOTHERSHIP_STRENGTH = 5;
static const float MOTHERSHIP_XSPEED = -2;
static const float MOTHERSHIP_YSPEED = 4;
static const float MOTHERSHIP_FIRE_COOLDOWN = .8;
static const float MOTHERSHIP_WORTH = 11;

static const float BULLET_XSPEED = 35;
static const float BULLET_YSPEED = 5;

enum WarriorObjectType : GameObjectType
{
    GameObjectType_Player,
    GameObjectType_Bullet,
    GameObjectType_Intercepter,
    GameObjectType_Hunter,
    GameObjectType_Mammoth,
    GameObject_type_MotherShip
};

class Bullet : public GameObject
{
public:
    Bullet(GameObject* shooter)
    {
        m_shooter = shooter;
    }

    void update(float dt, World* world) override;

    GameObject* getShooter() { return m_shooter; }

private:
    GameObject* m_shooter;
};

class HomingMissle : public Bullet
{
public:
    HomingMissle(GameObject* shooter, GameObject* target) : Bullet(shooter)
    {
        m_target = target;
    }

    void update(float dt, World* wolrd) override;

private:
    GameObject* m_target;
};

class Ship : public GameObject
{
public:
    Ship(int strength, float fireCooldown)
    {
        m_strength = strength;
        m_fireCooldown = fireCooldown;
        m_currFireCooldown = 0;
    }

    void update(float dt, World* world) override
    {
        GameObject::update(dt, world);
        if (m_currFireCooldown > 0)
        {
            m_currFireCooldown -= dt;
        }
    }

    void setStrength(int strength) { m_strength = strength; }
    int getStrength() { return m_strength; }
    bool tryKill() { return ((--m_strength) <= 0); }
    bool canFire() { return m_currFireCooldown <= 0; }
    void fire() { m_currFireCooldown = m_fireCooldown; }

private:
    int m_strength;
    float m_fireCooldown;
    float m_currFireCooldown;
};

class Player : public Ship
{
public:
    Player(int index) : Ship(PLAYER_STRENGTH, PLAYER_FIRE_COOLDOWN)
    {
        m_index = index;
        m_score = 0;
    }

    void update(float dt, World* world) override;

    int getScore() { return m_score; }
    void addScore(int score) { m_score += score; }

private:
    int m_index;
    int m_score;
};

class Enemy : public Ship
{
public:
    Enemy(int strength, float fireCooldown, int worth) : Ship(strength, fireCooldown)
    {
        m_worth = worth;
    }

    void update(float dt, World* world) override;

    int getWorth() { return m_worth; }

protected:
    virtual void shoot(World* world);

private:
    int m_worth;
};

class Hunter : public Enemy
{
public:
    Hunter(int strength, float fireCooldown, int worth) : Enemy(strength, fireCooldown, worth) {}
protected:
    void shoot(World* world) override;
};

class Mammoth : public Enemy
{
public:
    Mammoth(int strength, float fireCooldown, int worth) : Enemy(strength, fireCooldown, worth) {}

protected:
    void shoot(World* world) override;
};

static Player* createPlayer(int index, World* world)
{
    Player* player = new Player(index);
    ConsoleColor color = index == 1 ? ConsoleColor_Magenta : ConsoleColor_Yellow;
    ConsoleColor bgColor = index == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_DarkYellow;
    world->initializeObject(player, GameObjectType_Player, 0, SCREEN_HEIGHT / 2, 16, color, bgColor);

    return player;
}

static Bullet* createBullet(World* world, GameObject* shooter, float xSpeed)
{
    Bullet* bullet = new Bullet(shooter);
    world->initializeObject(bullet, GameObjectType_Bullet, shooter->getX(), shooter->getY(), '-', ConsoleColor_Red, ConsoleColor_Black);
    bullet->setXSpeed(xSpeed);
    return bullet;
}

static HomingMissle* createHomingMissle(World* world, GameObject* shooter, GameObject* target, float xSpeed)
{
    HomingMissle* missle = new HomingMissle(shooter, target);
    world->initializeObject(missle, GameObjectType_Bullet, shooter->getX(), shooter->getY(), '-', ConsoleColor_Red, ConsoleColor_Black);
    missle->setXSpeed(xSpeed);
    return missle;
}

static Ship* createEnemy(World* world, GameObjectType type, int x, int y)
{
    Enemy* enemy = 0;
    char symbol = ' ';
    ConsoleColor color = ConsoleColor_Black;
    ConsoleColor backgroundColor = ConsoleColor_Black;
    switch (type)
    {
    case GameObjectType_Intercepter:
        enemy = new Enemy(INTERCEPTER_STRENGTH, INTERCEPTER_FIRE_COOLDOWN, INTERCEPTER_WORTH);
        enemy->setXSpeed(INTERCEPTER_XSPEED);
        enemy->setYSpeed(INTERCEPTER_YSPEED);
        symbol = 17;
        color = ConsoleColor_Green;
        backgroundColor = ConsoleColor_DarkGreen;
        break;
    case GameObjectType_Hunter:
        enemy = new Hunter(HUNTER_STRENGTH, HUNTER_FIRE_COOLDOWN, HUNTER_WORTH);
        enemy->setXSpeed(HUNTER_XSPEED);
        enemy->setYSpeed(HUNTER_YSPEED);
        symbol = 15;
        color = ConsoleColor_Grey;
        backgroundColor = ConsoleColor_DarkGrey;
        break;
    case GameObjectType_Mammoth:
        enemy = new Mammoth(MAMMOTH_STRENGTH, MAMMOTH_FIRE_COOLDOWN, MAMMOTH_WORTH);
        enemy->setXSpeed(MAMMOTH_XSPEED);
        enemy->setYSpeed(MAMMOTH_YSPEED);
        symbol = 4;
        color = ConsoleColor_Red;
        backgroundColor = ConsoleColor_DarkRed;
        break;
    }
    world->initializeObject(enemy, type, x, y, symbol, color, backgroundColor);
    return enemy;
}
