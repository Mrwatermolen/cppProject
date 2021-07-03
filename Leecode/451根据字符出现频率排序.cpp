#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    string frequencySort(string s)
    {
        unordered_map<char, int> m;
        if (s == "")
            return s;

        for (int i = 0; i < s.size(); ++i)
            if (m.count(s[i]))
                ++m[s[i]];
            else
                m[s[i]] = 1;

        vector<pair<char, int>> vec;
        for (unordered_map<char, int>::iterator it = m.begin(); it != m.end(); ++it)
            vec.push_back(*it);

        sort(vec.begin(), vec.end(), [](const pair<char, int> &a, const pair<char, int> &b)
             { return a.second > b.second; });
        string res;
        for (vector<pair<char, int>>::iterator it = vec.begin(); it != vec.end(); ++it)
            for (int i = it->second; i > 0; --i)
                res.push_back(it->first);

        return res;
    }
};