#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<double> p = {0, 0.5, 0.1, 0.4}; // 1-indexed, p[0] unused
    int n = 3;
    vector<vector<double>> cost(n+2, vector<double>(n+2, 0));
    vector<vector<int>> root(n+2, vector<int>(n+2, 0));

    for (int i = 1; i <= n+1; i++) cost[i][i-1] = 0;

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n-len+1; i++) {
            int j = i + len - 1;
            cost[i][j] = DBL_MAX;
            double W = 0;
            for (int x = i; x <= j; x++) W += p[x];

            for (int r = i; r <= j; r++) {
                double left = (r-1 >= i) ? cost[i][r-1] : 0;
                double right = (r+1 <= j) ? cost[r+1][j] : 0;
                double total = left + right + W;
                if (total < cost[i][j]) {
                    cost[i][j] = total;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "Minimum expected search cost: " << cost[1][n] << endl;
    cout << "Root of full tree: key " << root[1][n] << endl;

    return 0;
}