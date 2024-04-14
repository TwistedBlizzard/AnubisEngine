#ifndef GAME_H
#define GAME_H

#include "Core.hpp"
#include "Engine.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Setup();

    void Update();
    void Draw();

    bool ShouldQuit();

private:
    bool m_quit;

    bool m_paused;
    bool m_pauseKey;
    bool m_lastPauseKey;
    double m_pauseCounter;

    Player* m_player;
    Enemy* m_enemy;
};

#endif // GAME_H