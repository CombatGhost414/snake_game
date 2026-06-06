#include "Food.h"
#include "Snake.h"

Food::Food(int seed)
    : GameEntity()
{
    if (seed == 0) {
        std::random_device rd;
        m_rng.seed(rd());
    } else {
        m_rng.seed(static_cast<unsigned int>(seed));
    }
}

void Food::update() {
    // Food is static — nothing to update per frame.
    // This override exists for polymorphism:
    // Game loop calls update() on every GameEntity without knowing
    // whether it's a Snake (which moves) or Food (which stays still).
}

void Food::draw(std::vector<std::vector<char>>& grid) const {
    if (m_position.y >= 0 && m_position.y < static_cast<int>(grid.size()) &&
        m_position.x >= 0 && m_position.x < static_cast<int>(grid[0].size())) {
        grid[m_position.y][m_position.x] = '*';
    }
}

void Food::respawn(const std::vector<Point>& occupied,
                   int boardWidth, int boardHeight) {
    // Collect all cells inside the walls that are not occupied
    std::vector<Point> candidates;
    for (int y = 1; y < boardHeight - 1; ++y) {
        for (int x = 1; x < boardWidth - 1; ++x) {
            Point p(x, y);
            bool isOccupied = false;
            for (const auto& occ : occupied) {
                if (occ == p) {
                    isOccupied = true;
                    break;
                }
            }
            if (!isOccupied) {
                candidates.push_back(p);
            }
        }
    }

    // Pick a random cell from candidates
    if (!candidates.empty()) {
        std::uniform_int_distribution<size_t> dist(0, candidates.size() - 1);
        m_position = candidates[dist(m_rng)];
    }
}

bool Food::isEatenBy(const Snake& snake) const {
    return m_position == snake.getHeadPosition();
}
