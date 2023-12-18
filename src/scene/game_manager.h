#pragma once

class GameManager {
protected:
    static unsigned int _totalScore;
    static unsigned int _totalHealth;
    static unsigned int _currentHealth;

public:
    GameManager() = delete;

    static unsigned int getScore();
    static void updateScore();
    static void resetScore();

    static unsigned int getCurrentHealth();
    static void updateHealth();
    static void resetHealth();
};