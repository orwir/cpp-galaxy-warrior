#include "warriorScreens.h"
#include "warriorWorld.h"
#include "input.h"
#include <cstdio>

void MenuScreen::render(RenderSystem* rs, World* world)
{
    char buffer[SCREEN_WIDTH];
    int length = sprintf_s(buffer, "GALAXY WARRIOR");
    int x = SCREEN_WIDTH / 2 - length / 2;
    rs->drawText(x, 1, buffer, ConsoleColor_Blue, ConsoleColor_Black);

    int y = SCREEN_HEIGHT / 2 - m_menuItems;
    for (int i = 0; i < m_menuItems; i++)
    {
        ConsoleColor background = i == m_selected ? ConsoleColor_DarkGrey : ConsoleColor_Black;
        length = sprintf_s(buffer, getMenuItemName(i));
        x = SCREEN_WIDTH / 2 - length / 2;
        rs->drawText(x, y + i * 2, buffer, ConsoleColor_White, background);
    }
}

void MenuScreen::update(float dt, World* world)
{
    if (isKeyDown(VK_DOWN) && m_KeyPressCooldown <= 0)
    {
        if (m_selected < m_menuItems - 1)
        {
            m_selected++;
        }
        else
        {
            m_selected = 0;
        }
        m_KeyPressCooldown = KEY_PRESS_COOLDOWN;
    }
    if (isKeyDown(VK_UP) && m_KeyPressCooldown <= 0)
    {
        if (m_selected > 0)
        {
            m_selected--;
        }
        else
        {
            m_selected = m_menuItems - 1;
        }
        m_KeyPressCooldown = KEY_PRESS_COOLDOWN;
    }
    if (isKeyDown(VK_RETURN) && m_KeyPressCooldown <= 0)
    {
        if(m_selected < 2)
        {
            m_nextScreen = ScreenType_Game;
            WarriorWorld* ww = (WarriorWorld*)world;
            ww->setPlayers(m_selected + 1);
        }
        m_KeyPressCooldown = KEY_PRESS_COOLDOWN;
    }

    if (m_KeyPressCooldown > 0)
    {
        m_KeyPressCooldown -= dt;
    }
}

ScreenType MenuScreen::openNext()
{
    return m_nextScreen;
}