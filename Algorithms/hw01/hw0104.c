#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    long long x, y;
} Point;

double area_of_polygon(Point* points, int n) {
    double area = 0.0;
    for (int i = 0; i < n - 1; i++) {
        area += (points[i].x * points[i + 1].y) - (points[i + 1].x * points[i].y);
    }
    area += (points[n - 1].x * points[0].y) - (points[0].x * points[n - 1].y);
    return 0.5 * abs(area);
}

int main() {
    int n;
    scanf("%d", &n);

    Point* points = (Point*)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }

    double result = area_of_polygon(points, n);
    printf("%.1lf\n", result);

    free(points);
    return 0;
}
