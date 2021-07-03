#include <vector>
using namespace std;
//给定一个 没有重复 数字的序列，返回其所有可能的全排列。
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;

    void Swap(vector<int>  &nums, int start, int end)
    {
        int temp  = nums[start];
        nums[start] = nums[end];
        nums[end] =temp;
    }
    void Back(vector<int> &nums, int start)
    {
        if(start == nums.size())
        {
            res.push_back(nums);
        }
        for (int i = start; i < nums.size(); ++i)
        {
            Swap(nums, start, i);
            Back(nums, start+ 1);
            Swap(nums, i,start);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        Back(nums,0);
        return res;
    }
};