#include "Brush.hpp"
#include <algorithm> // std::clamp

Brush::Brush(int initialRadius, int minR, int maxR)
    : radius(initialRadius),
    minRadius(minR),
    maxRadius(maxR),
    mode(BrushMode::Paint)
{
    radius = std::clamp(radius, minRadius, maxRadius);
}

void Brush::increaseRadius() {
    if (radius < maxRadius)
        ++radius;
}

void Brush::decreaseRadius() {
    if (radius > minRadius)
        --radius;
}

void Brush::setMode(BrushMode m) {
    mode = m;
}

BrushMode Brush::getMode() const {
    return mode;
}

int Brush::getRadius() const {
    return radius;
}

void Brush::apply(World& world, int centerGridX, int centerGridY, CellType paintType) const {
    int r = radius;
    int r2 = r * r;

    for (int dy = -r; dy <= r; ++dy) {
        for (int dx = -r; dx <= r; ++dx) {

            if (dx * dx + dy * dy > r2)
                continue;   // מחוץ לעיגול

            int gx = centerGridX + dx;
            int gy = centerGridY + dy;

            if (mode == BrushMode::Paint)
                world.setCell(gx, gy, paintType);
            else
                world.setCell(gx, gy, CellType::EMPTY);
        }
    }
}

void Brush::drawPreview(sf::RenderWindow& window,
    int mouseX, int mouseY,
    CellType paintType) const
{
    float pixelRadius = static_cast<float>(radius * Config::CELL_SIZE);

    sf::CircleShape preview(pixelRadius);


    preview.setOrigin({ pixelRadius, pixelRadius });
    preview.setPosition({ static_cast<float>(mouseX),
                          static_cast<float>(mouseY) });

    sf::Color color;

    switch (paintType) {
    case CellType::SAND:  color = sf::Color(255, 230, 150); break;
    case CellType::WATER: color = sf::Color(100, 150, 255); break;
    case CellType::STONE: color = sf::Color(150, 150, 150); break;
    case CellType::SNOW:  color = sf::Color(240, 240, 255); break;
    default:              color = sf::Color::White;         break;
    }

    if (mode == BrushMode::Erase) {
        color = sf::Color(255, 80, 80);
    }

    color.a = 60;
    preview.setFillColor(color);
    preview.setOutlineColor(sf::Color(255, 255, 255, 120));
    preview.setOutlineThickness(1.f);

    window.draw(preview);
}
