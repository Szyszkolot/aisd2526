#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string X, Y;
    getline(cin, X);
    getline(cin, Y);

    int m = (int)X.size(), n = (int)Y.size();

    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));

    // dynamiczne
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;
            else c[i][j] = max(c[i - 1][j], c[i][j - 1]);
        }
    }

    // odzyskiwanie z c[][]
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs.push_back(X[i - 1]);
            --i; --j;
        }
        else if (c[i - 1][j] >= c[i][j - 1]) {
            --i;
        }
        else {
            --j;
        }
    }
    reverse(lcs.begin(), lcs.end());

    cout << c[m][n] << "\n" << lcs << "\n";
    return 0;
}