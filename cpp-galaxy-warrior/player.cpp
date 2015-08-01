#include "warriorObjects.h"
#include "input.h"

enum Action
{
    UP,
    LEFT,
    DOWN,
    RIGHT,
    FIRE
};

int getActionButton(int player, Action action)
{
    switch (action)
    {
    case UP:    return player == 1 ? VK_UP : 'W';
    case LEFT:  return player == 1 ? VK_LEFT : 'A';
    case DOWN:  return player == 1 ? VK_DOWN : 'S';
    case RIGHT: return player == 1 ? VK_RIGHT : 'D';
    case FIRE:  return player == 1 ? VK_NUMPAD0 : VK_SPACE;
    }
}

void Player::update(float dt, World* world)
{
    Ship::update(dt, world);

    if (isKeyDown(getActionButton(m_index, UP)))
    {
        setYSpeed(-PLAYER_SPEED);
    }
    else if (isKeyDown(getActionButton(m_index, DOWN)))
    {
        setYSpeed(PLAYER_SPEED);
    }
    else {
        setYSpeed(0);
    }

    if (isKeyDown(getActionButton(m_index, LEFT)))
    {
        setXSpeed(-PLAYER_SPEED);
    }
    else if (isKeyDown(getActionButton(m_index, RIGHT)))
    {
        setXSpeed(PLAYER_SPEED);
    }
    else
    {
        setXSpeed(0);
    }

    if (isKeyDown(getActionButton(m_index, FIRE)) && canFire())
    {
        createBullet(world, this, BULLET_XSPEED);
        fire();
    }
}
