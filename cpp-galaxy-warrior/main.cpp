#include <cstdio>
#include "game.h"
#include "warriorScreens.h"
#include "warriorWorld.h"

using namespace consolity;

void main()
{
    Game* game = new Game();
    game->setup();
    game->setWorld(new WarriorWorld(SCREEN_WIDTH, SCREEN_HEIGHT));

    game->addScreen(new LogoScreen());
    game->addScreen(new MenuScreen());
    game->addScreen(new GameScreen());
    game->addScreen(new EndScreen());

    game->setScreen(ScreenType_Logo);
    game->run();
    game->shutdown();

    delete game;
}