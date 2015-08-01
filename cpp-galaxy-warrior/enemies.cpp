#include "warriorObjects.h"
#include "warriorWorld.h"

void Enemy::update(float dt, World* world)
{
    Ship::update(dt, world);
    for (int i = 0; i < world->getObjects().size(); i++)
    {
        GameObject* object = world->getObjects()[i];
        if (object != this && intersects(object))
        {
            if (object->getType() == GameObjectType_Player)
            {
                Player* player = (Player*)object;
                world->planDelete(this);
                if (player->tryKill())
                {
                    world->planDelete(player);
                }
                return;
            }
        }
    }
    if (getX() == 0)
    {
        world->planDelete(this);
        return;
    }
    if (getY() <= 0 || getY() >= SCREEN_HEIGHT-1)
    {
        setYSpeed(-getYSpeed());
    }
    if (canFire())
    {
        shoot(world);
        fire();
    }
}

void Enemy::shoot(World* world)
{
    createBullet(world, this, -BULLET_XSPEED);
}

void Hunter::shoot(World* world)
{
    WarriorWorld* ww = (WarriorWorld*)world;
    GameObject* target = 0;
    if (rand() % ww->getPlayers() == 0)
    {
        target = ww->getPlayer1();
    }
    else
    {
        target = ww->getPlayer2();
    }
    createHomingMissle(world, this, target, -BULLET_XSPEED);
}

void Mammoth::shoot(World* world)
{
    Bullet* b1 = createBullet(world, this, -BULLET_XSPEED);
    Bullet* b2 = createBullet(world, this, -BULLET_XSPEED);

    b1->setY(getY() - 1);
    b2->setY(getY() + 1);
}
