#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "World.hpp"

enum class BrushMode {
    Paint,
    Erase
};

class Brush {
public:
    Brush(int initialRadius = 5, int minRadius = 1, int maxRadius = 20);

    void increaseRadius();
    void decreaseRadius();

    void setMode(BrushMode m);
    BrushMode getMode() const;

    int getRadius() const;


    void apply(World& world, int centerGridX, int centerGridY, CellType paintType) const;

  
    void drawPreview(sf::RenderWindow& window,
        int mouseX, int mouseY,
        CellType paintType) const;

private:
    int radius;
    int minRadius;
    int maxRadius;
    BrushMode mode;
};
