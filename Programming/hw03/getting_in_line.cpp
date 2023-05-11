#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <iterator>

using namespace std;

struct Point
{
    int x, y;
};

double dist(Point a, Point b)
{
    return hypot(a.x - b.x, a.y - b.y) + 16.0;
}

int main()
{
    int n, x, y, tc = 1;
    while (cin >> n && n)
    {
        vector<Point> points(n);
        vector<int> order(n), best_order(n);
        iota(order.begin(), order.end(), 0);

        for (int i = 0; i < n; ++i)
        {
            cin >> x >> y;
            points[i] = {x, y};
        }

        double min_distance = 1e9;

        do
        {
            double current_distance = 0.0;
            for (int i = 1; i < n; ++i)
            {
                current_distance += dist(points[order[i - 1]], points[order[i]]);
            }
            if (current_distance < min_distance)
            {
                min_distance = current_distance;
                copy(order.begin(), order.end(), best_order.begin());
            }
        } while (next_permutation(order.begin(), order.end()));

        cout << "**********************************************************\n";
        cout << "Network #" << tc++ << '\n';
        for (int i = 1; i < n; ++i)
        {
            cout << "Cable requirement to connect (" << points[best_order[i - 1]].x << ","
                 << points[best_order[i - 1]].y << ") to (" << points[best_order[i]].x << ","
                 << points[best_order[i]].y << ") is "
                 << fixed << setprecision(2) << dist(points[best_order[i - 1]], points[best_order[i]]) << " feet.\n";
        }
        cout << "Number of feet of cable required is " << fixed << setprecision(2) << min_distance << ".\n";
    }
    return 0;
}
