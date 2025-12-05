#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

enum CellType {
    EMPTY = 0,
    SAND = 1,
    WATER = 2,
    STONE = 3,
    SNOW = 4
};

class World {
private:
    std::vector<CellType> cells;

  
    int index(int x, int y) const {
        return y * Config::COLUMNS + x;
    }

public:
    World();

    void setCell(int x, int y, CellType type);
    void update();
    void draw(sf::RenderWindow& window);
};
