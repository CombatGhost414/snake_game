#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include <vector>

class Board {
public:
    static constexpr char BORDER_CHAR = '#';
    static constexpr char EMPTY_CHAR  = ' ';
    static constexpr int  DEFAULT_WIDTH  = 25;
    static constexpr int  DEFAULT_HEIGHT = 20;

private:
    int m_width;
    int m_height;
    std::vector<std::vector<char>> m_grid;  // [y][x]

public:
    explicit Board(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

    // Grid operations
    void clear();
    void drawBorder();
    bool isInside(const Point& p) const;

    // Attributes
    int  getWidth()  const { return m_width; }
    int  getHeight() const { return m_height; }

    // Access (const and non-const overloads)
    std::vector<std::vector<char>>&       getGrid()       { return m_grid; }
    const std::vector<std::vector<char>>& getGrid() const { return m_grid; }

    // Output
    void render() const;
};

#endif
