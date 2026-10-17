#include <bits/stdc++.h>
using namespace std;

void rabinKarp(const string &text, const string &pattern, int base, int mod) {
    int n = text.size();
    int m = pattern.size();
    if (m > n) return; // edge case: pattern longer than text

    long long h = 1; // h = base^(m-1) % mod
    for (int i = 0; i < m - 1; i++)
        h = (h * base) % mod;

    long long p_hash = 0, t_hash = 0;

    // Step 1: compute initial hashes
    for (int i = 0; i < m; i++) {
        p_hash = (base * p_hash + pattern[i]) % mod;
        t_hash = (base * t_hash + text[i]) % mod;
    }

    // Step 2: slide the window
    for (int s = 0; s <= n - m; s++) {
        if (p_hash == t_hash) {
            // Verify character by character (avoid spurious hit)
            if (text.substr(s, m) == pattern) {
                cout << "Pattern found at index " << s << endl;
            }
        }
        if (s < n - m) {
            t_hash = (base * (t_hash - text[s] * h) + text[s + m]) % mod;
            if (t_hash < 0) t_hash += mod; // handle negative mod
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    int base = 256;
    int mod = 101; // a prime number

    rabinKarp(text, pattern, base, mod);
    return 0;
}