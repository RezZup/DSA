#include <iostream>
using namespace std;

#include <string>
#include <vector>
using namespace std;

vector<int> computeLPS(string pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) len = lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
    return lps;
}

void KMPsearch(string text, string pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
            if (j == m) {
                cout << "Pattern found at index " << i - j << "\n";
                j = lps[j - 1];
            }
        } else {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    KMPsearch(text, pattern);
}