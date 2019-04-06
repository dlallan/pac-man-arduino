/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of game*/
#ifndef game_h
#define game_h
#include <Arduino.h>

// Game state stored in instance of Game
class Game {
    public:
        // start game with given number of lives
        Game(int16_t lives = 3);
        ~Game() {};

        // check if out of lives or at max score
        bool isGameOver();

        // gets value of lives member
        int16_t getRemainingLives();
        
        // decrement value of lives member
        void loseLife();

        // get value of score member
        int16_t getScore();

        // add val to score. Does nothing if val is not positive.
        void increaseScore(int16_t val);

        // check value of paused member
        bool isPaused();

        // set paused member
        void pauseGame();

        // clear paused member
        void resumeGame();

        // raise or lower flag for new score to display
        bool scoreChanged;
        // raise or lower flag for new num lives to display
        bool livesChanged;

        static const int16_t deathDelay = 500; // in milliseconds

        // get this score to win the game
        // (310 dots + 6 power pellets * 5 points per pellet)
        static const int16_t maxScore = 340;
    
    private:
        int16_t score = 0; // game score
        
        
        int16_t lives;     // player lives
        bool paused = false; // if true, then game should stop running

};

#endif