#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        if (!n)
            return 0;

        vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (s[i] != '0')
                dp[i] += 1;

            if (i > 1 && ((s[i - 2] - '0') * 10 + s[i - 1] - '0' <= 26))
                dp[i] += dp[i - 1];
        }
        return dp[n];
    }
};