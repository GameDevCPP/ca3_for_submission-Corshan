#include "game_manager.h"

unsigned int GameManager::_totalScore;

unsigned int GameManager::getScore() {
    return _totalScore;
}

void GameManager::resetScore() {
    _totalScore = 0;
}

void GameManager::updateScore() {
    _totalScore += 100;
}