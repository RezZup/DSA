#include <bits/stdc++.h>
using namespace std;

int binomialCoeff(int n, int k) {
    vector<vector<int>> C(n+1, vector<int>(k+1, 0));
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    return C[n][k];
}

int binomialCoeffOptimized(int n, int k) {
    vector<int> C(k+1, 0);
    C[0] = 1;  // C(i,0) is always 1
    
    for (int i = 1; i <= n; i++) {
        // traverse right to left to avoid overwriting needed values
        for (int j = min(i, k); j > 0; j--) {
            C[j] = C[j] + C[j-1];
        }
    }
    return C[k];
}

int main() {
    cout << "C(4,2) = " << binomialCoeff(4, 2) << "\n"; // Output: 6
    cout << "C(5,2) = " << binomialCoeff(5, 2) << "\n"; // Output: 10
    cout << "C(4,2) = " << binomialCoeffOptimized(4, 2) << "\n"; // Output: 6
    cout << "C(5,2) = " << binomialCoeffOptimized(5, 2) << "\n"; // Output: 10
}