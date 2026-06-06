#include "Snake.h"

Snake::Snake(const Point& startPos, int initialLength)
    : GameEntity(startPos)
    , m_direction(Direction::Right)
    , m_nextDirection(Direction::Right)
    , m_growing(false)
{
    // Build initial body: head at startPos, body trailing to the left
    for (int i = 0; i < initialLength; ++i) {
        m_body.emplace_back(startPos.x - i, startPos.y);
    }
}

void Snake::update() {
    // Commit the buffered direction
    m_direction = m_nextDirection;

    // Compute new head position
    Point newHead = m_body.front();
    switch (m_direction) {
        case Direction::Up:    newHead.y--; break;
        case Direction::Down:  newHead.y++; break;
        case Direction::Left:  newHead.x--; break;
        case Direction::Right: newHead.x++; break;
    }

    // Insert new head at the front
    m_body.insert(m_body.begin(), newHead);

    // Remove tail unless the snake is growing this frame
    if (m_growing) {
        m_growing = false;
    } else {
        m_body.pop_back();
    }

    // Keep base position in sync with head
    m_position = m_body.front();
}

void Snake::draw(std::vector<std::vector<char>>& grid) const {
    for (std::size_t i = 0; i < m_body.size(); ++i) {
        const auto& seg = m_body[i];
        if (seg.y >= 0 && seg.y < static_cast<int>(grid.size()) &&
            seg.x >= 0 && seg.x < static_cast<int>(grid[0].size())) {
            grid[seg.y][seg.x] = (i == 0) ? 'O' : 'o';
        }
    }
}

void Snake::setDirection(Direction dir) {
    // Reject 180-degree reversal
    if ((m_direction == Direction::Up    && dir == Direction::Down)  ||
        (m_direction == Direction::Down  && dir == Direction::Up)    ||
        (m_direction == Direction::Left  && dir == Direction::Right) ||
        (m_direction == Direction::Right && dir == Direction::Left)) {
        return;
    }
    m_nextDirection = dir;
}

void Snake::grow() {
    m_growing = true;
}

const Point& Snake::getHeadPosition() const {
    return m_body.front();
}

const std::vector<Point>& Snake::getBody() const {
    return m_body;
}

int Snake::getLength() const {
    return static_cast<int>(m_body.size());
}

Snake::Direction Snake::getDirection() const {
    return m_direction;
}

bool Snake::checkSelfCollision() const {
    const auto& head = m_body.front();
    // Use range-based for starting from the second segment
    for (auto it = m_body.begin() + 1; it != m_body.end(); ++it) {
        if (*it == head) {
            return true;
        }
    }
    return false;
}
