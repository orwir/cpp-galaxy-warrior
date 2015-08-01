#pragma once

#include "screen.h"

using namespace consolity;

static ConsoleColor getRenderColor(unsigned char symbol)
{
    switch (symbol)
    {
    case 'W': return ConsoleColor_DarkGrey;
    case 'R': return ConsoleColor_Red;
    }
    return ConsoleColor_Black;
}

enum WarriorScreenType : ScreenType
{
    ScreenType_Logo,
    ScreenType_Menu,
    ScreenType_Game,
    ScreenType_End
};

class LogoScreen : public Screen
{
public:
    LogoScreen() : Screen(ScreenType_Logo)
    {
        m_showTime = 4;
        m_currentTime = m_showTime;
    }

    void render(RenderSystem* rs, World* world) override;
    void update(float dt, World* world) override;
    ScreenType openNext() override;

private:
    float m_showTime;
    float m_currentTime;
};

class MenuScreen : public Screen
{
public:
    MenuScreen() : Screen(ScreenType_Menu)
    {
        m_nextScreen = ScreenType_None;
        m_selected = 0;
        m_menuItems = 2;
    }

    void render(RenderSystem* rs, World* world) override;
    void update(float dt, World* world) override;
    ScreenType openNext() override;

private:
    const float KEY_PRESS_COOLDOWN = .3;
    int m_selected;
    int m_menuItems;
    float m_KeyPressCooldown;
    ScreenType m_nextScreen;

    const char* getMenuItemName(int item)
    {
        switch (item)
        {
        case 0: return "1 Player";
        case 1: return "2 Players";
        }
        return "";
    }
};

class GameScreen : public Screen
{
public:
    GameScreen() : Screen(ScreenType_Game)
    {
        m_nextScreen = ScreenType_None;
        m_spawnCooldown = 0;
    }
    void onFirstOpen(RenderSystem* rs, World* world) override;
    void render(RenderSystem* rs, World* world) override;
    void update(float dt, World* world) override;
    ScreenType openNext() override;

private:
    ScreenType m_nextScreen;
    float m_bgPos;
    float m_spawnCooldown;
};

class EndScreen : public Screen
{
public:
    EndScreen() : Screen(ScreenType_End) {}

    void render(RenderSystem* rs, World* world) override;
    void update(float dt, World* world) override;

};
