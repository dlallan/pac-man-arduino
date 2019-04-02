#include "game.h"

Game::Game(int16_t lives /*= 3*/) {
    this->lives = lives;
}

Game::~Game() {}

int16_t Game::getRemainingLives() {
    return lives;
}

void Game::loseLife() {
    lives--;
}

int16_t Game::getScore() {
    return score;
}

void Game::increaseScore(int16_t val) {
    score += val > 0 ? val : 0;
}

bool Game::isPaused() {
    return paused;
}

void Game::pauseGame() {
    paused = true;
}

void Game::resumeGame() {
    paused = false;
}

bool Game::isGameOver() {
    if (lives < 1 || score == Game::maxScore) return true;
    return false;
}