#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#endif

// ═══════════════════════════════════════════════════════
//  Constructor
// ═══════════════════════════════════════════════════════
Game::Game(int width, int height, int speed, int targetLength)
    : m_board(width, height)
    , m_snake(Point(width / 2, height / 2), 3)
    , m_food()
    , m_score(0)
    , m_gameOver(false)
    , m_won(false)
    , m_frameDelayMs(speed)
    , m_targetLength(targetLength)
{
}

// ═══════════════════════════════════════════════════════
//  Main game loop
// ═══════════════════════════════════════════════════════
void Game::run() {
    displayStartScreen();

    // Hide console cursor for smooth rendering
    std::cout << "\033[?25l";

    // Place first food (avoiding snake body)
    m_food.respawn(m_snake.getBody(), m_board.getWidth(), m_board.getHeight());

    // Clear screen once before entering the loop
    std::cout << "\033[2J\033[H";

    // ── Main loop ──
    while (!m_gameOver && !m_won) {
        auto frameStart = std::chrono::steady_clock::now();

        processInput();
        update();
        checkCollisions();
        render();

        // Frame rate control using modern <chrono>
        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed  = std::chrono::duration_cast<std::chrono::milliseconds>(
                            frameEnd - frameStart);
        auto remaining = std::chrono::milliseconds(m_frameDelayMs) - elapsed;
        if (remaining.count() > 0) {
            std::this_thread::sleep_for(remaining);
        }
    }

    // Restore cursor
    std::cout << "\033[?25h";

    displayEndScreen();
}

// ═══════════════════════════════════════════════════════
//  Non-blocking keyboard input (Windows)
// ═══════════════════════════════════════════════════════
void Game::processInput() {
#ifdef _WIN32
    while (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'w': case 'W':
                m_snake.setDirection(Snake::Direction::Up);
                break;
            case 's': case 'S':
                m_snake.setDirection(Snake::Direction::Down);
                break;
            case 'a': case 'A':
                m_snake.setDirection(Snake::Direction::Left);
                break;
            case 'd': case 'D':
                m_snake.setDirection(Snake::Direction::Right);
                break;
            case 27:  // ESC
                m_gameOver = true;
                break;
        }
    }
#endif
}

// ═══════════════════════════════════════════════════════
//  Update all entities (polymorphic calls)
// ═══════════════════════════════════════════════════════
void Game::update() {
    m_snake.update();   // Snake: moves forward, handles growth
    m_food.update();    // Food:  no-op — demonstrates polymorphism
                        //        (same interface, different behavior)
}

// ═══════════════════════════════════════════════════════
//  Render: build frame buffer → output
// ═══════════════════════════════════════════════════════
void Game::render() {
    // 1. Reset grid
    m_board.clear();
    m_board.drawBorder();

    // 2. Draw entities polymorphically
    m_snake.draw(m_board.getGrid());
    m_food.draw(m_board.getGrid());

    // 3. Move cursor to top-left (avoids flicker; no system("cls"))
    std::cout << "\033[H";

    // 4. Output grid
    m_board.render();

    // 5. Status bar
    std::cout << "Score: " << m_score
              << "  |  Length: " << m_snake.getLength()
              << "  |  Target: "
              << (m_targetLength > 0 ? std::to_string(m_targetLength)
                                     : std::string("Fill board"))
              << std::endl;
    std::cout << "W/A/S/D to move  |  ESC to quit" << std::endl;
}

// ═══════════════════════════════════════════════════════
//  Collision detection & game state update
// ═══════════════════════════════════════════════════════
void Game::checkCollisions() {
    const Point& head = m_snake.getHeadPosition();

    // ── Wall collision ──
    if (!m_board.isInside(head)) {
        m_gameOver = true;
        return;
    }

    // ── Self collision ──
    if (m_snake.checkSelfCollision()) {
        m_gameOver = true;
        return;
    }

    // ── Food collision ──
    if (m_food.isEatenBy(m_snake)) {
        m_snake.grow();
        m_score += 10;
        m_food.respawn(m_snake.getBody(),
                       m_board.getWidth(), m_board.getHeight());

        // ── Win condition check ──
        if (m_targetLength > 0) {
            if (m_snake.getLength() >= m_targetLength) {
                m_won = true;
            }
        } else {
            // Fill-board win: snake occupies all playable cells
            int playableArea = (m_board.getWidth() - 2)
                             * (m_board.getHeight() - 2);
            if (m_snake.getLength() >= playableArea) {
                m_won = true;
            }
        }
    }
}

// ═══════════════════════════════════════════════════════
//  Start screen
// ═══════════════════════════════════════════════════════
void Game::displayStartScreen() {
    std::cout << "========================================\n";
    std::cout << "          Welcome to SNAKE!\n";
    std::cout << "========================================\n\n";
    std::cout << "Controls:  W = Up    S = Down\n";
    std::cout << "           A = Left  D = Right\n";
    std::cout << "           ESC = Quit\n\n";
    std::cout << "Eat food ( * ) to grow and score points.\n";
    std::cout << "Avoid hitting walls ( # ) or yourself!\n\n";

    if (m_targetLength > 0) {
        std::cout << ">>> Reach length " << m_targetLength
                  << " to win! <<<\n\n";
    } else {
        std::cout << ">>> Fill the entire board to win! <<<\n\n";
    }

    std::cout << "Press any key to start...";
#ifdef _WIN32
    _getch();
#endif
}

// ═══════════════════════════════════════════════════════
//  End screen
// ═══════════════════════════════════════════════════════
void Game::displayEndScreen() {
    std::cout << "\033[2J\033[H";   // Clear screen
    std::cout << "========================================\n";
    if (m_won) {
        std::cout << "             YOU WIN!\n";
    } else {
        std::cout << "            GAME OVER\n";
    }
    std::cout << "========================================\n\n";
    std::cout << "Final Score:  " << m_score << "\n";
    std::cout << "Final Length: " << m_snake.getLength() << "\n\n";
    std::cout << "Press any key to exit...";
#ifdef _WIN32
    _getch();
#endif
}
