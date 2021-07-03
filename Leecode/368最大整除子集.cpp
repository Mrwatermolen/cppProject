/*
给你一个由 无重复 正整数组成的集合 nums ，请你找出并返回其中最大的整除子集 answer ，子集中每一元素对 (answer[i], answer[j]) 都应当满足：
answer[i] % answer[j] == 0 ，或
answer[j] % answer[i] == 0
如果存在多个有效解子集，返回其中任何一个均可。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-divisible-subset
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution
{
public:
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size(), maxCount = 1, maxP;
        vector<int> dp(n, 1);
        vector<int> res;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] % nums[j] == 0)
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                    if (maxCount < dp[i])
                    {
                        maxCount = dp[i];
                        maxP = i;
                    }
                }
            }
        }

        if (maxCount == 1)
        {
            res.push_back(nums[0]);
            return res;
        }
        res.push_back(nums[maxP]);
        for (int i = maxP - 1; maxCount > 1 && i >= 0; --i)
        {
            if (nums[maxP] % nums[i] == 0 && maxCount == dp[i] + 1)
            {
                res.push_back(nums[i]);
                maxP = i;
                --maxCount;
            }
        }

        return res;
    }
};