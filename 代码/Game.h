#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include <string>

class Game {
private:
    Board m_board;
    Snake m_snake;
    Food  m_food;
    int   m_score;
    bool  m_gameOver;
    bool  m_won;
    int   m_frameDelayMs;
    int   m_targetLength;  // -1 = fill entire board

public:
    Game(int width = 25, int height = 20,
         int speed = 120, int targetLength = -1);

    void run();

private:
    void processInput();
    void update();
    void render();
    void checkCollisions();
    void displayStartScreen();
    void displayEndScreen();
};

#endif
