#include <stack>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        map<int, int> m;
        stack<int> s;
        vector<int> res;
        for (auto &num : nums2)
        {
            while (!s.empty() && s.top() < num)
            {
                m[s.top()] = num;
                s.pop();
            }
            s.push(num);
        }
        for (auto &num : nums1)
        {
            map<int, int>::iterator  iter = m.find(num);
            if (iter != m.end())
                res.push_back(iter->second);
            else
                res.push_back(-1);
        }
        return res;
    }
};
