#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Point {
    long long x, y;
} Point;

long long compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->x - p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}

bool ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

long double area(Point *points, int n) {
    long double result = 0.0;
    for (int i = 0; i < n - 1; i++) {
        result += (long double)(points[i].x * points[i + 1].y) - (long double)(points[i + 1].x * points[i].y);
    }
    result += (long double)(points[n - 1].x * points[0].y) - (long double)(points[0].x * points[n - 1].y);
    return fabsl(result) / 2.0;
}

int main() {
    int n;
    scanf("%d", &n);

    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), compare);

    Point hull[2 * n];
    int k = 0;

    for (int i = 0; i < n; i++) {
        while (k >= 2 && !ccw(hull[k - 2], hull[k - 1], points[i])) {
            k--;
        }
        hull[k++] = points[i];
    }

    for (int i = n - 1, t = k + 1; i > 0; i--) {
        while (k >= t && !ccw(hull[k - 2], hull[k - 1], points[i - 1])) {
            k--;
        }
        hull[k++] = points[i - 1];
    }

    long double calculated_area = area(hull, k - 1);
    if (calculated_area - (long long)calculated_area > 0) {
        printf("%.1Lf\n", calculated_area);
    } else {
        printf("%lld\n", (long long)calculated_area);
    }

    return 0;
}
