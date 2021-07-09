#include <vector>

using namespace std;
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        if (nums.size() == 0)
            return -1;
        int count = 0, res;
        for (int &num : nums)
        {
            if (count == 0)
                res = num, count = 1;
            else if (res == num)
                ++count;
            else
                --count;
        }
        count = 0;
        for (int &num : nums)
        {
            if (res == num)
                ++count;
        }
        return (2 * count > nums.size()) ? (res) : (-1);
    }
};