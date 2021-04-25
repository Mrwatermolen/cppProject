/*给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 */
class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); ++i)
        {
            for (int j = 1; j <= amount; ++j)
                if (j >= coins[i])
                    dp[j] = dp[j] + dp[j - coins[i]];
        }
        return dp[amount];
    }
};