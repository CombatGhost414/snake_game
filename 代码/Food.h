#ifndef FOOD_H
#define FOOD_H

#include "GameEntity.h"
#include <random>

class Snake;  // Forward declaration

class Food : public GameEntity {
private:
    std::mt19937 m_rng;  // Modern Mersenne Twister engine

public:
    explicit Food(int seed = 0);

    // ---- Override virtual functions ----
    void update() override;
    void draw(std::vector<std::vector<char>>& grid) const override;

    // ---- Food-specific interface ----
    void respawn(const std::vector<Point>& occupied,
                 int boardWidth, int boardHeight);
    bool isEatenBy(const Snake& snake) const;
};

#endif
