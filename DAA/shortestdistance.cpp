#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double bruteForce(vector<Point>& points) {
    double minDist = 1e18;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            minDist = min(minDist, dist(points[i], points[j]));
        }
    }
    return minDist;
}

double closestUtil(vector<Point>& Px, vector<Point>& Py) {
    int n = Px.size();
    if (n <= 3) return bruteForce(Px);

    int mid = n / 2;
    Point midPoint = Px[mid];

    vector<Point> Lx(Px.begin(), Px.begin()+mid), Rx(Px.begin()+mid, Px.end());
    vector<Point> Ly, Ry; // split Py accordingly based on x < midPoint.x

    double dl = closestUtil(Lx, Ly);
    double dr = closestUtil(Rx, Ry);
    double d = min(dl, dr);

    // build strip
    vector<Point> strip;
    for (auto& p : Py)
        if (abs(p.x - midPoint.x) < d) strip.push_back(p);

    // check only next ~7 points
    for (int i = 0; i < strip.size(); i++)
        for (int j = i+1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++)
            d = min(d, dist(strip[i], strip[j]));

    return d;
}

double closestPair(vector<Point>& points) {
    vector<Point> Px = points, Py = points;
    sort(Px.begin(), Px.end(), [](Point a, Point b) { return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](Point a, Point b) { return a.y < b.y; });
    return closestUtil(Px, Py);
}
 int main() {
    vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {1, 0}};
    cout << "The smallest distance is " << closestPair(points) << endl;
    return 0;
 }