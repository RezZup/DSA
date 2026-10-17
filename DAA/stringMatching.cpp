#include <iostream>
#include <string>
using namespace std;

void naiveStringMatch(const string& T, const string& P) {
    int n = T.length();
    int m = P.length();

    for (int s = 0; s <= n - m; s++) {
        int j = 0;
        while (j < m && T[s + j] == P[j]) {
            j++;
        }
        if (j == m) {
            cout << "Pattern found at shift " << s << endl;
        }
    }
}

int main() {
    string T = "ABABABCA";
    string P = "ABC";

    naiveStringMatch(T, P);

    return 0;
}