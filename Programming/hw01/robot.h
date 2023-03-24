#ifndef ROBOT_H
#define ROBOT_H

#include "maze.h"
#include <unordered_map>

class Robot {
public:
    Robot(int x, int y, long long n, const Maze& maze);

    void execute_moves();

    int get_x() const;

    int get_y() const;

private:
    int x, y;
    long long n;
    const Maze& maze;
};

#endif // ROBOT_H
