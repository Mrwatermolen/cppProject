#include <vector>
#include <map>
#include <algorithm>

using namespace std;
//超时
class Solution
{
public:
    vector<vector<int>> res;
    map<vector<int>, int> mapN;

    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        int size = 4, sum = 0;
        vector<int> temp;
        sort(nums.begin(), nums.end());
        d(nums, temp, 0, size, target, sum);
        return res;
    }

    void d(vector<int> &nums, vector<int> &temp, int index, int &size, int &target, int sum)
    {
        if (temp.size() == size)
        {

            if (sum == target)
            {
                if (mapN.end() == mapN.find(temp))
                {
                    mapN.insert(pair<vector<int>, int>(temp, mapN.size()));
                    res.push_back(temp);
                }
            }

            return;
        }
        for (int i = index; i < nums.size(); ++i)
        {
            if (nums.size() - i < int(4 - temp.size()))
                return;
            temp.push_back(nums[i]);

            d(nums, temp, i + 1, size, target, sum + nums[i]);
            temp.pop_back();
        }
    }
};