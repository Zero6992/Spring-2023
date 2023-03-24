#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
public:
    Maze(int w, int h, const std::vector<std::string>& map);

    char get_cell(int x, int y) const;

    int get_width() const;

    int get_height() const;

private:
    int width, height;
    std::vector<std::string> grid;
};

#endif // MAZE_H
