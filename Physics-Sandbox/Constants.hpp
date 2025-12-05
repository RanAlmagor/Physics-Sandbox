#pragma once

namespace Config {

    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    constexpr int CELL_SIZE = 4;

    constexpr int COLUMNS = WINDOW_WIDTH / CELL_SIZE; 
    constexpr int ROWS = WINDOW_HEIGHT / CELL_SIZE; 
}
