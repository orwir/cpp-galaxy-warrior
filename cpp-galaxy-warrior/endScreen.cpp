#include "warriorScreens.h"
#include "input.h"
#include "warriorWorld.h"

void EndScreen::render(RenderSystem* rs, World* world)
{
    WarriorWorld* ww = (WarriorWorld*)world;

    char buffer[SCREEN_WIDTH];
    int length = sprintf_s(buffer, "GAME OVER");
    int x = SCREEN_WIDTH / 2 - length / 2;
    rs->drawText(x, SCREEN_HEIGHT / 2 - 2, buffer, ConsoleColor_White, ConsoleColor_Black);

    if (ww->getPlayers() == 1)
    {
        length = sprintf_s(buffer, "Your score: %d", ww->getPlayer1()->getScore());
        x = SCREEN_WIDTH / 2 - length / 2;
        rs->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    }
    else
    {
        length = sprintf_s(buffer, "Player 1 score: %d", ww->getPlayer1()->getScore());
        x = SCREEN_WIDTH / 2 - length / 2;
        rs->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);

        length = sprintf_s(buffer, "Player 2 score: %d", ww->getPlayer2()->getScore());
        x = SCREEN_WIDTH / 2 - length / 2;
        rs->drawText(x, SCREEN_HEIGHT / 2 + 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    }

    length = sprintf_s(buffer, "Press 'Q' to exit...");
    x = SCREEN_WIDTH / 2 - length / 2;
    int y = SCREEN_HEIGHT / 2 + ww->getPlayers() * 3;
    rs->drawText(x, y, buffer, ConsoleColor_Grey, ConsoleColor_Black);
}

void EndScreen::update(float dt, World* world)
{
    if (isKeyDown('Q'))
    {
        world->planDestroy();
    }
}
