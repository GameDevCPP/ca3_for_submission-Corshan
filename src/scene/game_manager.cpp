#include "game_manager.h"

unsigned int GameManager::_totalScore;
unsigned int GameManager::_totalHealth = 100;
unsigned int GameManager::_currentHealth;

unsigned int GameManager::getScore() {
    return _totalScore;
}

void GameManager::resetScore() {
    _totalScore = 0;
}

void GameManager::updateScore() {
    _totalScore += 100;
}

unsigned int GameManager::getCurrentHealth(){
    return _currentHealth;
}

void GameManager::updateHealth() {
    _currentHealth -= 10;
}

void GameManager::resetHealth() {
    _currentHealth = _totalHealth;
}