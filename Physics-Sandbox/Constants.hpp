#pragma once

namespace Config {
    
    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 800;

    
    constexpr int CELL_SIZE = 6;

    constexpr int COLUMNS = WINDOW_WIDTH / CELL_SIZE;
    constexpr int ROWS = WINDOW_HEIGHT / CELL_SIZE;
}