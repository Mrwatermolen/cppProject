#include <vector>
using namespace std;

class Solution
{
public:
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {
        map<int, int> m;
        int sum = 0, res = 0;
        for (int &num : nums)
        {
            ++m[sum];
            sum += num;
            res += m[sum - goal];
        }
        return res;
    }
};