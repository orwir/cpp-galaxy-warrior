#include "warriorScreens.h"
#include "warriorWorld.h"
#include "graphics.h"
#include "warriorObjects.h"
#include "input.h"

using namespace consolity;

const float spawnCooldown = 5;
const int enemiesTypeCount = 3;
const GameObjectType enemies[enemiesTypeCount] = {GameObjectType_Intercepter, GameObjectType_Hunter, GameObjectType_Mammoth};

void GameScreen::render(RenderSystem* rs, World* world)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            int rx = int(x + m_bgPos);
            if (rx < 0)
            {
                rx = SCREEN_WIDTH + rx;
            }
            rs->drawChar(rx, y, levelBackground[y][x], ConsoleColor_White, ConsoleColor_Black);
        }
    }
    for (int i = 0; i < world->getObjects().size(); i++)
    {
        world->getObjects()[i]->render(rs);
    }

    WarriorWorld* ww = (WarriorWorld*)world;
    char buffer[SCREEN_WIDTH];
    int length = 0;
    int startX = 0;

    if (ww->getPlayers() > 1)
    {
        length = sprintf_s(buffer, "P1: ");
        rs->drawText(startX, 0, buffer, ConsoleColor_Magenta, ConsoleColor_Black);
        startX += length;
    }

    for (int i = 0; i < ww->getPlayer1()->getStrength(); i++)
    {
        rs->drawChar(startX, 0, 3, ConsoleColor_DarkRed, ConsoleColor_Black);
        startX += 2;
    }
    length = sprintf_s(buffer, "Score: %d", ww->getPlayer1()->getScore());
    rs->drawText(++startX, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    startX += length;

    if (ww->getPlayers() > 1)
    {
        startX++;
        length = sprintf_s(buffer, "P2: ");
        rs->drawText(startX, 0, buffer, ConsoleColor_Yellow, ConsoleColor_Black);
        startX += length;

        for (int i = 0; i < ww->getPlayer2()->getStrength(); i++)
        {
            rs->drawChar(startX, 0, 3, ConsoleColor_DarkRed, ConsoleColor_Black);
            startX += 2;
        }
        sprintf_s(buffer, "Score: %d", ww->getPlayer2()->getScore());
        rs->drawText(++startX, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    }
}

void GameScreen::update(float dt, World* world)
{
    m_bgPos -= dt * 12;
    if (m_bgPos < -SCREEN_WIDTH)
    {
        m_bgPos = 0;
    }
    for (int i = 0; i < world->getObjects().size(); i++)
    {
        world->getObjects()[i]->update(dt, world);
    }
    WarriorWorld* ww = (WarriorWorld*)world;
    if (m_spawnCooldown > 0)
    {
        m_spawnCooldown -= dt;
    }
    else
    {
        GameObjectType type = enemies[rand() % enemiesTypeCount];
        createEnemy(world, type, SCREEN_WIDTH - 1, rand() % SCREEN_HEIGHT);
        m_spawnCooldown = spawnCooldown / ww->getPlayers();
    }
    if (ww->getPlayers() == 1 && ww->getPlayer1()->getStrength() <= 0)
    {
        m_nextScreen = ScreenType_End;
    }
    else if (ww->getPlayers() > 1 && ww->getPlayer1()->getStrength() <= 0 && ww->getPlayer2()->getStrength() <= 0)
    {
        m_nextScreen = ScreenType_End;
    }
}

ScreenType GameScreen::openNext()
{
    return m_nextScreen;
}

void GameScreen::onFirstOpen(RenderSystem* rs, World* world)
{
    WarriorWorld* ww = (WarriorWorld*)world;

    Player* player1 = createPlayer(1, world);
    ww->setPlayer1(player1);
    if (ww->getPlayers() == 2)
    {
        Player* player2 = createPlayer(2, world);
        ww->setPlayer2(player2);
        player2->setY(player2->getY() + 1);
        player1->setY(player1->getY() - 1);
    }
    m_spawnCooldown = spawnCooldown;
    
}
