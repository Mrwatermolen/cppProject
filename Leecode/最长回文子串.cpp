//给你一个字符串 s，找到 s 中最长的回文子串。
class Solution
{
public:
    string LongestPalindrome(string s)
    {
        string t = "#";
        int n = s.size(), max = 0, pos = 0;
        for (int i = 0; i < n; ++i)
        {
            t += s[i];
            t += "#";
        }
        s = t;
        n = s.size();
        vector<int> len(n, 0); //len = pos - max
        for (int i = 0; i < n; ++i)
        {
            if (i < max)
            {
                if (max - i > len[2 * pos - i])
                    len[i] = len[2 * pos - i];
                else
                    len[i] = max - i;
            }
            else
                len[i] = 0;
            int left = i - len[i], right = i + len[i];
            while (left >= 0 && right < n && s[left] == s[right])
                --left, ++right;
            len[i] = (right - left - 2) >> 1;
            if (len[i] > len[pos])
                pos = i, max = len[i] + i;
        }
        t = "";
        for (int i = pos - len[pos]; i <= max; ++i)
        {
            if (s[i] != '#')
                t += s[i];
        }
        return t;
    }
    string DPLongestPalindrome(string s)
    {
        vector<int> res(2, 0);

        vector<vector<int>> dp(s.size(), vector(s.size(), 0));

        for (int l = 1; l <= s.size(); ++l)
        {
            for (int i = 0; i <= s.size() - l; ++i)
            {
                int j = i + l - 1;
                if (l <= 2)
                {
                    dp[i][j] = (s[i] == s[j]) ? (l) : (0);
                    dp[j][i] = dp[i][j];
                    if (dp[i][j] > res[1])
                        res[0] = i, res[1] = dp[i][j];
                    continue;
                }
                if (s[i] == s[j] && dp[i + 1][j - 1] == j - i - 1)
                {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                    if (dp[i][j] > res[1])
                        res[0] = i, res[1] = dp[i][j];
                }
                else
                    dp[i][j] = dp[i + 1][j - 1];
            }
        }
        return s.substr(res[0], res[1]);
        //eturn nullptr;
    }
};