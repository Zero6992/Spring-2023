#include "maze.h"

Maze::Maze(int w, int h, const std::vector<std::string>& map)
    : width(w), height(h), grid(map)
{}

char Maze::get_cell(int x, int y) const {
    return grid[y][x];
}

int Maze::get_width() const {
    return width;
}

int Maze::get_height() const {
    return height;
}
