#include <vector>
#include <string>
#include <iostream>
using namespace std;
/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
class Solution
{
public:
    string temp;
    vector<string> res;
    vector<string> table = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return res;

        dsf(digits, 0);

        return res;
    }

    void dsf(string &t, int num)
    {
        if (num == t.size())
        {
            res.push_back(temp);
            return;
        }
        int p = t[num] - '0';

        for (int i = 0; i < table[p].size(); ++i)
        {
            temp.push_back(table[p][i]);
            dsf(t, num + 1);
            temp.pop_back();
        }
    }
};
