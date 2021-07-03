/*给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

你可以认为每种硬币的数量是无限的。
*/

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount <= 0 || coins.size() == 0)
            return (amount == 0) ? 0 : -1;
        int *dp = new int[amount + 1];
        int coinNum = coins.size();
        int MaxAmount = amount + 1;
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i)
        {
            dp[i] = MaxAmount;
            for (int j = 0; j < coinNum; ++j)
            {
                int t = i - coins[j];
                if (t >= 0)
                    if (dp[i] > dp[t]) //这有个小坑注意一下不能是>=
                        dp[i] = dp[t] + 1;
            }
        }
        return (dp[amount] >= MaxAmount) ? (-1) : (dp[amount]);
    }
};