#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> C; // global table

int binomialMF(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    if (C[n][k] != -1)          // check cache first
        return C[n][k];
    
    // compute on-demand (top-down recursion)
    int value = binomialMF(n-1, k-1) + binomialMF(n-1, k);
    C[n][k] = value;             // store for future reuse
    return value;
}

int main() {
    int n = 4, k = 2;
    C.assign(n+1, vector<int>(k+1, -1));  // initialize table with sentinel -1
    
    cout << "C(" << n << "," << k << ") = " << binomialMF(n, k) << "\n";
    
    // Show which cells got computed (not -1)
    cout << "\nComputed table cells:\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (C[i][j] != -1)
                cout << "C[" << i << "][" << j << "] = " << C[i][j] << "\n";
        }
    }
}