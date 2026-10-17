#include <bits/stdc++.h>
using namespace std;

// Memoization (Top-Down)
int memo[50];
int fibMemo(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibMemo(n-1) + fibMemo(n-2);
}

// Tabulation (Bottom-Up)
int fibTab(int n) {
    if (n <= 1) return n;
    vector<int> dp(n+1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}

int main() {
    memset(memo, -1, sizeof(memo));
    cout << "Memoized fib(10) = " << fibMemo(10) << "\n";
    cout << "Tabulated fib(10) = " << fibTab(10) << "\n";
}