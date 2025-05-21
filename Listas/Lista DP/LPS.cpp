#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<vector<int>> buildLPSMatrix(string &s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        dp[i][i] = 1;

    for (int cl = 2; cl <= n; cl++)
    {
        for (int i = 0; i < n - cl + 1; i++)
        {
            int j = i + cl - 1;
            if (s[i] == s[j] && cl == 2)
                dp[i][j] = 2;
            else if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
        }
    }

    return dp;
}

int main()
{
    string s = "aibioibia";
    auto dp = buildLPSMatrix(s);
    cout << "Tamanho da maior subsequencia palindromica: ";
    cout << dp[0][s.size() - 1] << endl;

    return 0;
}