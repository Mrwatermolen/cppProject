#include <vector>
using namespace std;

/*给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。*/
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int ans = nums[0], pre = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            pre = max(pre + nums[i], nums[i]);
            ans = max(ans, pre);
        }
        return ans;
    }
};