#include <bits/stdc++.h>
using namespace std;

int m[100][100], s[100][100];

int matrixChainOrder(vector<int>& p, int n) {
    for (int i = 1; i <= n; i++) m[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n];
}

void printOptimalParens(int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
    cout << "(";
    printOptimalParens(i, s[i][j]);
    printOptimalParens(s[i][j]+1, j);
    cout << ")";
}

int main() {
    vector<int> p = {1, 2, 3, 4};   // A1=1x2, A2=2x3, A3=3x4
    int n = p.size() - 1;

    int minCost = matrixChainOrder(p, n);
    cout << "Minimum scalar multiplications: " << minCost << endl;

    cout << "Optimal Parenthesization: ";
    printOptimalParens(1, n);
    cout << endl;

    return 0;
}