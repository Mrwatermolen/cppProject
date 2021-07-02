#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size(), m = s2.size(), k = s3.size();
        if (n + m != k)
            return false;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        dp[0][0] = 1;
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= m; ++j)
            {
                //处理边界条件 i,j任意一个为0 但不能同时为0
                if (!(i * j))
                {
                    if (j && dp[i][j - 1])
                    {
                        dp[i][j] = (s2[j - 1] == s3[j - 1]);
                    }
                    if (i && dp[i - 1][j])
                    {
                        dp[i][j] = (s1[i - 1] == s3[i - 1]);
                    }
                    continue;
                }

                if (dp[i - 1][j])
                { //如果[0~(i-1+j -1)]的s3能被s1[0~(i-2)]与s2[0~(j-1)]交错 则
                    //判断s1[i-1] s3[i-1+j]
                    dp[i][j] = (s1[i - 1] == s3[i - 1 + j]);
                }
                else if (dp[i][j - 1])
                { //如果[0~(i+j-1 -1)]的s3能被s1[0~(i-1)]与s2[0~(j-2]交错 则
                    dp[i][j] = (s2[j - 1] == s3[i - 1 + j]);
                }
            }
        }
        return dp[n][m];
    }
};