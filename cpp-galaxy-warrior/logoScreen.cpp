#include "warriorScreens.h"
#include "graphics.h"

void LogoScreen::render(RenderSystem* rs, World* world)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            ConsoleColor color = getRenderColor(logoGraphics[y][x]);
            rs->drawChar(x, y, ' ', color, color);
        }
    }

    float loaded = m_showTime - m_currentTime;
    float percent = loaded / m_showTime;
    int fill = int(float(SCREEN_WIDTH) * percent);
    for (int i = 0; i <= fill; i++)
    {
        rs->drawChar(i, SCREEN_HEIGHT - 1, ' ', ConsoleColor_DarkBlue, ConsoleColor_DarkBlue);
    }
}

void LogoScreen::update(float dt, World* world)
{
    if (m_currentTime > 0)
    {
        m_currentTime -= dt;
    }
}

ScreenType LogoScreen::openNext()
{
    return m_currentTime > 0 ? ScreenType_None : ScreenType_Menu;
}
