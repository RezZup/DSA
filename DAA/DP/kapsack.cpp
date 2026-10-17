#include <bits/stdc++.h>
using namespace std;

int knapsackOptimized(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<int> K(W+1, 0);
    
    for (int i = 0; i < n; i++) {
        // IMPORTANT: iterate w from HIGH to LOW to avoid using updated values prematurely
        for (int w = W; w >= wt[i]; w--) {
            K[w] = max(K[w], val[i] + K[w - wt[i]]);
        }
    }
    return K[W];
}

int knapsack(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> K(n+1, vector<int>(W+1, 0));
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i-1] <= w)
                K[i][w] = max(K[i-1][w], val[i-1] + K[i-1][w - wt[i-1]]);
            else
                K[i][w] = K[i-1][w];
        }
    }
    
    // Trace back chosen items
    cout << "Chosen items: ";
    int w = W;
    for (int i = n; i > 0 && K[i][w] > 0; i--) {
        if (K[i][w] != K[i-1][w]) {
            cout << "Item" << i << " (wt=" << wt[i-1] << ",val=" << val[i-1] << ") ";
            w -= wt[i-1];
        }
    }
    cout << "\n";
    
    return K[n][W];
}

int main() {
    vector<int> wt = {1, 3, 4, 5};
    vector<int> val = {1, 4, 5, 7};
    int W = 7;
    int n = wt.size();

    
    cout << "Maximum value = " << knapsack(wt, val, n, W) << "\n";
    cout << "Maximum value (optimized) = " << knapsackOptimized(wt, val, n, W) << "\n";
    
}