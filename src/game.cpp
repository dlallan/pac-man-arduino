#include "game.h"

Game::Game(int16_t lives /*= 3*/) {
    lives = lives;
}

bool Game::checkGameOver() {
    return lives < 1;
}

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