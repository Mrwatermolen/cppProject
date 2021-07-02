#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> res;

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() <= 2)
            return res;
        sort(nums.begin(), nums.end());

        for (int k = 0; k < nums.size() - 1; ++k)
        {
            if (nums[k] > 0)
                break;
            if (k > 0 && nums[k] == nums[k - 1])
                continue;
            int i = k + 1, j = nums.size() - 1;
            while (i < j)
            {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == 0)
                {

                    res.push_back(vector<int>({nums[i], nums[k], nums[j]}));
                    ++i, --j;
                    while (i < j && nums[j] == nums[j + 1])
                    {
                        --j;
                    }
                    while (i < j && nums[i] == nums[i - 1])
                    {
                        ++i;
                    }
                }
                else if (sum < 0)
                {
                    ++i;
                    while (i < j && nums[i] == nums[i - 1])
                    {
                        ++i;
                    }
                }
                else
                {
                    --j;
                    while (i < j && nums[j] == nums[j + 1])
                    {
                        --j;
                    }
                }
            }
        }
        return res;
    }
    int threeSumClosest(vector<int> &nums, int target)
    {
        int n = nums.size(), res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        for (int k = 0; k < n - 2; ++k)
        {
            if (k > 0 && nums[k] == nums[k - 1])
                continue;
            int i = k + 1, j = n - 1;
            while (i < j)
            {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == target)
                    return sum;
                if (abs(sum - target) < abs(res - target))
                    res = sum;
                if (sum > target)
                {
                    --j;
                    while (i < j && nums[j] == nums[j + 1])
                        --j;
                }
                else
                {
                    ++i;
                    while (i < j && nums[i] == nums[i - 1])
                        ++i;
                }
            }
        }
        return res;
    }
};

int main()
{
    vector<int> nums({-1, 0, 1, 2, -1, 4});
    Solution s;
    s.threeSum(nums);
}