#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int dp(int i, int j, const string& X, const string& Y, vector<vector<int>>& c) {
    if (i == 0 || j == 0) return 0;
    if (c[i][j] != -1) return c[i][j];

    if (X[i - 1] == Y[j - 1])
        return c[i][j] = dp(i - 1, j - 1, X, Y, c) + 1;

    return c[i][j] = max(dp(i - 1, j, X, Y, c),
        dp(i, j - 1, X, Y, c));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string X, Y;
    getline(cin, X);
    getline(cin, Y);

    int m = (int)X.size(), n = (int)Y.size();

    vector<vector<int>> c(m + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= m; i++) c[i][0] = 0;
    for (int j = 0; j <= n; j++) c[0][j] = 0;

    int len = dp(m, n, X, Y, c);

    // odzyskiwanie z c[][]
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs.push_back(X[i - 1]);
            --i; --j;
        }
        else {
            if (c[i - 1][j] == -1) dp(i - 1, j, X, Y, c);
            if (c[i][j - 1] == -1) dp(i, j - 1, X, Y, c);

            if (c[i - 1][j] >= c[i][j - 1]) --i;
            else --j;
        }
    }
    reverse(lcs.begin(), lcs.end());

    cout << len << "\n" << lcs << "\n";
    return 0;
}