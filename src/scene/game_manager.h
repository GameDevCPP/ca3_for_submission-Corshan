#pragma once

class GameManager {
protected:
    static unsigned int _totalScore;

public:
    GameManager() = delete;

    static unsigned int getScore();
    static void updateScore();
    static void resetScore();
};