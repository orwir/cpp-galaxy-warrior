#pragma once

#include "world.h"
#include "warriorObjects.h"

using namespace consolity;

class WarriorWorld : public World
{
public:
    WarriorWorld(int width, int height) : World(width, height)
    {
        m_players = 1;
        m_player1 = 0;
        m_player2 = 0;
    }

    int getPlayers() { return m_players; }
    void setPlayers(int players) { m_players = players; }
    
    void setPlayer1(Player* player) { m_player1 = player; }
    Player* getPlayer1() { return m_player1; }

    void setPlayer2(Player* player) { m_player2 = player; }
    Player* getPlayer2() { return m_player2; }

private:
    int m_players;
    Player* m_player1;
    Player* m_player2;
};