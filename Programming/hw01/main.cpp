#include <iostream>
#include "maze.h"
#include "robot.h"

int main() {
    int w, h;
    long long n;
    std::cin >> w >> h >> n;

    std::vector<std::string> map(h);
    int x, y;
    for (int i = 0; i < h; ++i) {
        std::cin >> map[i];
        size_t pos = map[i].find('O');
        if (pos != std::string::npos) {
            x = pos;
            y = i;
        }
    }

    Maze maze(w, h, map);
    Robot robot(x, y, n, maze);

    robot.execute_moves();

    std::cout << robot.get_x() << " " << robot.get_y() << std::endl;

    return 0;
}
