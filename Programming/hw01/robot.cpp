#include "robot.h"
#include <string>
#include <unordered_map>

Robot::Robot(int x, int y, long long n, const Maze& maze)
    : x(x), y(y), n(n), maze(maze) {}

void Robot::execute_moves() {
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int direction = 0;
    std::unordered_map<std::string, long long> visited;

    for (long long i = 0; i < n; ++i) {
        std::string state = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(direction);
        if (visited.count(state)) {
            int cycle_length = i - visited[state];
            i += ((n - i) / cycle_length) * cycle_length;
        } else {
            visited[state] = i;
        }

        while (true) {
            int nx = x + dx[direction];
            int ny = y + dy[direction];

            if (nx >= 0 && nx < maze.get_width() && ny >= 0 && ny < maze.get_height() && maze.get_cell(nx, ny) != '#') {
                x = nx;
                y = ny;
                break;
            } else {
                direction = (direction + 1) % 4;
            }
        }
    }
}

int Robot::get_x() const {
    return x;
}

int Robot::get_y() const {
    return y;
}
