#include <vector>
#include <string>
using namespace std;

/*给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。*/
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 1;
        if (s.size() <= 0)
            return 0;
        vector<int> dp(s.size(), 1);
        for (int i = 1; i < s.size(); ++i)
        {
            int j = i - 1;
            for (; j >= i - dp[i - 1]; --j)
            {
                if (s[i] == s[j])
                    break;
            }
            dp[i] = i - j;
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};