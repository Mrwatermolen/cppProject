#include <vector>
#include <numeric>
using namespace std;
/*
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
示例 1：
输入：candidates = [2,3,6,7], target = 7,
所求解集为：
[
  [7],
  [2,2,3]
]
*/

class Solution
{
public:
    vector<vector<int>> res;
    vector<int> path;

    void Back(vector<int> &nums, int start, int target)//超出时间限制
    {
        int flag = 0;
        int sum = accumulate(path.begin(), path.end(), 0);
        if (sum >= target)
        {
            if (sum == target)
            {
                res.push_back(path);
            }
            flag = 1;
        }
        for (int i = start; i < nums.size(); ++i)
        {
            path.push_back(nums[i]);
            Back(nums, i + flag, target);
            path.pop_back();
        }
    }

    void dfs(vector<int> &nums, int start, int target)
    {
        if (target == 0)
        {
            res.push_back(path);
        }
        for (int i = start; i < nums.size(); ++i)
        {
            if (target - nums[i] >= 0)
            {
                path.push_back(nums[i]);
                Back(nums, i, target - nums[i]);
                path.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        dfs(candidates, 0, target);
        return res;
    }
};