
#include "World.hpp"
#include <cstdlib>    // std::rand
#include <algorithm>  // std::swap


World::World()
    : cells(Config::COLUMNS* Config::ROWS, CellType::EMPTY)
{
}


void World::setCell(int x, int y, CellType type) {
    if (x < 0 || x >= Config::COLUMNS || y < 0 || y >= Config::ROWS) {
        return;
    }
    cells[index(x, y)] = type;
}

void World::update()
{
    const int width = Config::COLUMNS;
    const int height = Config::ROWS;

    for (int y = height - 2; y >= 0; --y) {

        bool leftToRight = (std::rand() % 2 == 0);
        int xStart = leftToRight ? 0 : width - 1;
        int xEnd = leftToRight ? width : -1;
        int xStep = leftToRight ? 1 : -1;

        for (int x = xStart; x != xEnd; x += xStep) {

            int idx = index(x, y);
            CellType type = cells[idx];

            if (type == CellType::EMPTY || type == CellType::STONE)
                continue;

            int belowY = y + 1;
            int idxBelow = index(x, belowY);

            auto isEmpty = [&](int i) {
                return cells[i] == CellType::EMPTY;
                };

            auto swapCells = [&](int a, int b) {
                std::swap(cells[a], cells[b]);
                };

            // --- חול ושלג ---
            if (type == CellType::SAND || type == CellType::SNOW) {
                if (cells[idxBelow] == CellType::WATER) {
                    cells[idx] = CellType::WATER;
                    cells[idxBelow] = type;
                    continue;
                }
                if (isEmpty(idxBelow)) {
                    swapCells(idx, idxBelow);
                    continue;
                }

                bool preferLeft = (std::rand() % 2 == 0);
                int dx1 = preferLeft ? -1 : 1;
                int dx2 = preferLeft ? 1 : -1;

                int nx1 = x + dx1;
                if (nx1 >= 0 && nx1 < width) {
                    int idxDiag1 = index(nx1, belowY);
                    if (isEmpty(idxDiag1)) {
                        swapCells(idx, idxDiag1);
                        continue;
                    }
                    if (cells[idxDiag1] == CellType::WATER) {
                        cells[idx] = CellType::WATER;
                        cells[idxDiag1] = type;
                        continue;
                    }
                }

                int nx2 = x + dx2;
                if (nx2 >= 0 && nx2 < width) {
                    int idxDiag2 = index(nx2, belowY);
                    if (isEmpty(idxDiag2)) {
                        swapCells(idx, idxDiag2);
                        continue;
                    }
                    if (cells[idxDiag2] == CellType::WATER) {
                        cells[idx] = CellType::WATER;
                        cells[idxDiag2] = type;
                        continue;
                    }
                }
            }
            // --- מים ---
            else if (type == CellType::WATER) {
                if (isEmpty(idxBelow)) {
                    swapCells(idx, idxBelow);
                    continue;
                }

                int firstDir = (std::rand() % 2 == 0) ? -1 : 1;
                int secondDir = -firstDir;

                auto tryDiagonal = [&](int dir) -> bool {
                    int nx = x + dir;
                    if (nx < 0 || nx >= width) return false;
                    int idxDiag = index(nx, belowY);
                    if (isEmpty(idxDiag)) {
                        swapCells(idx, idxDiag);
                        return true;
                    }
                    return false;
                    };

                if (tryDiagonal(firstDir)) continue;
                if (tryDiagonal(secondDir)) continue;

                int horizDir = (std::rand() % 2 == 0) ? 1 : -1;
                for (int step = 1; step <= 3; ++step) {
                    int newX = x + horizDir * step;
                    if (newX < 0 || newX >= width) break;
                    int idxSide = index(newX, y);
                    if (isEmpty(idxSide)) {
                        swapCells(idx, idxSide);
                        break;
                    }
                }
            }
        }
    }
}


void World::draw(sf::RenderWindow& window) {
    sf::RectangleShape cellShape(sf::Vector2f((float)Config::CELL_SIZE, (float)Config::CELL_SIZE));

    for (int y = 0; y < Config::ROWS; y++) {
        for (int x = 0; x < Config::COLUMNS; x++) {
            int idx = index(x, y);
            CellType type = cells[idx];

            if (type == CellType::EMPTY) continue;

            if (type == CellType::SAND) cellShape.setFillColor(sf::Color::Yellow);
            else if (type == CellType::WATER) cellShape.setFillColor(sf::Color::Blue);
            else if (type == CellType::STONE) cellShape.setFillColor(sf::Color(100, 100, 100));
            else if (type == CellType::SNOW) cellShape.setFillColor(sf::Color::White);

            cellShape.setPosition({ (float)(x * Config::CELL_SIZE), (float)(y * Config::CELL_SIZE) });
            window.draw(cellShape);
        }
    }
}