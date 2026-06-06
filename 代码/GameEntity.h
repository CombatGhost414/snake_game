#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Point.h"
#include <vector>

class GameEntity {
protected:
    Point m_position;

public:
    explicit GameEntity(const Point& pos = Point()) : m_position(pos) {}
    virtual ~GameEntity() = default;

    // Pure virtual functions — derived classes must override
    virtual void update() = 0;
    virtual void draw(std::vector<std::vector<char>>& grid) const = 0;

    // Non-virtual accessors (not meant to be overridden)
    Point getPosition() const { return m_position; }
    void  setPosition(const Point& pos) { m_position = pos; }
};

#endif
