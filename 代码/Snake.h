#ifndef SNAKE_H
#define SNAKE_H

#include "GameEntity.h"
#include <vector>

class Snake : public GameEntity {
public:
    // Modern scoped enum for direction
    enum class Direction { Up, Down, Left, Right };

private:
    std::vector<Point> m_body;          // index 0 = head
    Direction          m_direction;     // Current committed direction
    Direction          m_nextDirection; // Buffered input (prevents 180° reversal)
    bool               m_growing;

public:
    explicit Snake(const Point& startPos, int initialLength = 3);

    // ---- Override virtual functions ----
    void update() override;
    void draw(std::vector<std::vector<char>>& grid) const override;

    // ---- Snake-specific interface ----
    void setDirection(Direction dir);
    void grow();

    // ---- Queries ----
    const Point&               getHeadPosition() const;
    const std::vector<Point>&  getBody() const;
    int                        getLength() const;
    Direction                  getDirection() const;
    bool                       checkSelfCollision() const;
};

#endif
