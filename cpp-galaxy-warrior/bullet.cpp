#include "warriorObjects.h"

void Bullet::update(float dt, World* world)
{
    GameObject::update(dt, world);
    if (getX() <= 0 || getX() >= SCREEN_WIDTH - 1)
    {
        world->planDelete(this);
        return;
    }

    for (int i = 0; i < world->getObjects().size(); i++)
    {
        GameObject* object = world->getObjects()[i];
        if (object != this && intersects(object))
        {
            if (getShooter()->getType() == GameObjectType_Player
                && object->getType() != GameObjectType_Player
                && object->getType() != GameObjectType_Bullet)
            {
                Player* player = (Player*)getShooter();
                Enemy* enemy = (Enemy*)object;
                world->planDelete(this);
                if (enemy->tryKill())
                {
                    world->planDelete(enemy);
                    player->addScore(enemy->getWorth());
                }
            }
            else if (getShooter()->getType() != GameObjectType_Player
                && object->getType() == GameObjectType_Player)
            {
                Player* player = (Player*)object;
                Enemy* enemy = (Enemy*)getShooter();
                world->planDelete(this);
                if (player->tryKill())
                {
                    world->planDelete(player);
                }
            }
        }
    }
}

void HomingMissle::update(float dt, World* world)
{
    Bullet::update(dt, world);

    if (m_target->getY() < getY())
    {
        setYSpeed(-BULLET_YSPEED);
    }
    else if (m_target->getY() > getY())
    {
        setYSpeed(BULLET_YSPEED);
    }
    else
    {
        setYSpeed(0);
    }
}