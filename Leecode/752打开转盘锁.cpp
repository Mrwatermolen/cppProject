#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <set>
using namespace std;

class Solution
{
public:
    int openLock(vector<string> &deadends, string target)
    {
        set<string> visited;
        visited.insert(deadends.begin(), deadends.end());
        if (visited.count("0000"))
            return -1;

        queue<string> q;
        q.push("0000");
        int step = 0;
        while (!q.empty())
        {
            int l = q.size();
            while (l > 0)
            {
                --l;
                string cur = q.front();
                if (cur == target)
                    return step;
                q.pop();
                for (int i = 0; i < 4; ++i)
                {
                    for (int j = -1; j < 2; j += 2)
                    {
                        char c = (cur[i] - '0' + j + 10) % 10 + '0';
                        string temp = cur;
                        temp[i] = c;
                        if (!visited.count(temp))
                        {
                            visited.emplace(temp);
                            q.push(temp);
                        }
                    }
                }
            }

            ++step;
        }
        return -1;
    }
};
int main()
{
    Solution s;
    vector<string> d({"8888"});
    cout << s.openLock(d, "1111");
}