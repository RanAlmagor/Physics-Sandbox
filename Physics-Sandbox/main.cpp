#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <vector>

#include "Constants.hpp"
#include "World.hpp"
#include "Brush.hpp"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }),
        "Physics Sandbox - Twilight"
    );
    window.setFramerateLimit(60);

    World world;
    Brush brush(5, 1, 20);
    CellType currentMaterial = CellType::SAND;

  

    sf::CircleShape moon(50.f);
    moon.setFillColor(sf::Color(200, 200, 255));
    moon.setPosition({ 1050.f, 60.f });

    std::vector<sf::CircleShape> stars;
    stars.reserve(100);
    for (int i = 0; i < 100; ++i) {
        sf::CircleShape star(1.f);
        star.setFillColor(sf::Color::White);
        star.setPosition({
            static_cast<float>(std::rand() % Config::WINDOW_WIDTH),
            static_cast<float>(std::rand() % Config::WINDOW_HEIGHT)
            });
        stars.push_back(star);
    }

    sf::ConvexShape mountain3;
    mountain3.setPointCount(3);
    mountain3.setPoint(0, sf::Vector2f(600.f, (float)Config::WINDOW_HEIGHT));
    mountain3.setPoint(1, sf::Vector2f(800.f, (float)Config::WINDOW_HEIGHT - 350.f));
    mountain3.setPoint(2, sf::Vector2f(1050.f, (float)Config::WINDOW_HEIGHT));
    mountain3.setFillColor(sf::Color(30, 30, 60));

    sf::ConvexShape mountain1;
    mountain1.setPointCount(3);
    mountain1.setPoint(0, sf::Vector2f(0.f, (float)Config::WINDOW_HEIGHT));
    mountain1.setPoint(1, sf::Vector2f(400.f, (float)Config::WINDOW_HEIGHT - 200.f));
    mountain1.setPoint(2, sf::Vector2f(650.f, (float)Config::WINDOW_HEIGHT));
    mountain1.setFillColor(sf::Color(45, 45, 80));

    sf::ConvexShape mountain2;
    mountain2.setPointCount(3);
    mountain2.setPoint(0, sf::Vector2f(500.f, (float)Config::WINDOW_HEIGHT));
    mountain2.setPoint(1, sf::Vector2f(900.f, (float)Config::WINDOW_HEIGHT - 150.f));
    mountain2.setPoint(2, sf::Vector2f((float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT));
    mountain2.setFillColor(sf::Color(60, 60, 100));


    while (window.isOpen()) {

        while (const std::optional<sf::Event> event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                using Key = sf::Keyboard::Key;

                switch (keyEvent->code) {
                   
                case Key::Num1: currentMaterial = CellType::SAND;  break;
                case Key::Num2: currentMaterial = CellType::WATER; break;
                case Key::Num3: currentMaterial = CellType::STONE; break;
                case Key::Num4: currentMaterial = CellType::SNOW;  break;

                    
                case Key::Add:
                case Key::Equal:
                    brush.increaseRadius();
                    break;

                case Key::Subtract:
                case Key::Hyphen:
                    brush.decreaseRadius();
                    break;

                 
                case Key::R:
                    world.clear();
                    break;

                default:
                    break;
                }
            }
        }

    
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int gridX = mousePos.x / Config::CELL_SIZE;
        int gridY = mousePos.y / Config::CELL_SIZE;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            brush.setMode(BrushMode::Paint);
            brush.apply(world, gridX, gridY, currentMaterial);
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            brush.setMode(BrushMode::Erase);
            brush.apply(world, gridX, gridY, currentMaterial);
        }

        world.update();

   
        window.clear(sf::Color(25, 10, 40));

        for (const auto& star : stars) window.draw(star);
        window.draw(moon);
        window.draw(mountain3);
        window.draw(mountain1);
        window.draw(mountain2);

        world.draw(window);
        brush.drawPreview(window, mousePos.x, mousePos.y, currentMaterial);

        window.display();
    }

    return 0;
}
