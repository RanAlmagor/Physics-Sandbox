#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <optional>

#include "Constants.hpp"
#include "World.hpp"

int main() {

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // חלון (שימי לב ל-{} – סינטקס של SFML 3)
    sf::RenderWindow window(
        sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }),
        "Physics Sandbox"
    );
    window.setFramerateLimit(60);

    World world;

    // חומר ברירת מחדל לציור
    CellType currentType = CellType::SAND;

    while (window.isOpen()) {

        // === אירועים (סגירת חלון וכו') – SFML 3 עם std::optional ===
        while (const std::optional<sf::Event> event = window.pollEvent()) {

            // סגירת חלון
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // === בחירת חומר לפי מקשים (קלט בזמן אמת, לא דרך event) ===
        // שים לב: תמיד עם sf::Keyboard::Key::...

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            currentType = CellType::SAND;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            currentType = CellType::WATER;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            currentType = CellType::STONE;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
            currentType = CellType::SNOW;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            int gridX = mousePos.x / Config::CELL_SIZE;
            int gridY = mousePos.y / Config::CELL_SIZE;

            world.setCell(gridX, gridY, currentType);
        }

        // כפתור ימין – מוחק (שם EMPTY)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            int gridX = mousePos.x / Config::CELL_SIZE;
            int gridY = mousePos.y / Config::CELL_SIZE;

            world.setCell(gridX, gridY, CellType::EMPTY);
        }



        world.update();

       
        window.clear(sf::Color(20, 20, 30)); // כהה-כחלחל

        world.draw(window);
        window.display();
    }

    return 0;
}