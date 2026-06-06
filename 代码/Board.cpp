#include "Board.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Board::Board(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_grid(height, std::vector<char>(width, EMPTY_CHAR))
{
}

void Board::clear() {
    for (auto& row : m_grid) {
        std::fill(row.begin(), row.end(), EMPTY_CHAR);
    }
}

void Board::drawBorder() {
    // Top and bottom rows
    for (int x = 0; x < m_width; ++x) {
        m_grid[0][x]           = BORDER_CHAR;
        m_grid[m_height - 1][x] = BORDER_CHAR;
    }
    // Left and right columns
    for (int y = 0; y < m_height; ++y) {
        m_grid[y][0]            = BORDER_CHAR;
        m_grid[y][m_width - 1]  = BORDER_CHAR;
    }
}

bool Board::isInside(const Point& p) const {
    return p.x > 0 && p.x < m_width - 1 &&
           p.y > 0 && p.y < m_height - 1;
}

void Board::render() const {
    std::ostringstream buffer;
    for (const auto& row : m_grid) {
        for (const auto& cell : row) {
            buffer << cell;
        }
        buffer << '\n';
    }
    std::cout << buffer.str() << std::flush;
}
