#include <bits/stdc++.h>
using namespace std;

struct Point { int x, y; };

Point p0;

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;      // collinear
    return (val > 0) ? 1 : 2;    // 1=clockwise, 2=counter-clockwise
}

int dist(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) return dist(p0, p2) >= dist(p0, p1);
    return (o == 2); // counter-clockwise comes first
}

vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    int ymin = points[0].y, minIdx = 0;
    for (int i = 1; i < n; i++)
        if (points[i].y < ymin || (points[i].y == ymin && points[i].x < points[minIdx].x))
            ymin = points[i].y, minIdx = i;
    swap(points[0], points[minIdx]);
    p0 = points[0];

    sort(points.begin()+1, points.end(), compare);

    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() > 1 && orientation(hull[hull.size()-2], hull.back(), points[i]) != 2)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    vector<Point> hull = convexHull(points);
    cout << "Points in Convex Hull:\n";
    for (auto p : hull)
        cout << "(" << p.x << ", " << p.y << ")\n";
    return 0;
}