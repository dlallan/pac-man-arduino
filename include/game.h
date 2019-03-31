#ifndef game_h
#define game_h
#include <Arduino.h>

class Game {
    public:
        // start game with given number of lives
        Game(int16_t lives = 3);
        ~Game();

        // check for Game Over condition
        // (returns true if game over, false otherwise)
        bool checkGameOver();

        // gets value of lives member
        int16_t getRemainingLives();
        
        // decrement value of lives member
        void loseLife();

        // get value of score member
        int16_t getScore();

        // add val to score. Does nothing if val is not positive.
        void increaseScore(int16_t val);

    private:
        int16_t score = 0; // game score
        int16_t lives;     // player lives
};

#endif