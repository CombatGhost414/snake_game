#include "Game.h"
#include <iostream>

int main() {
    try {
        // 30×20 board, 100ms per frame, fill-board win condition
        Game game(30, 20, 100, -1);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
