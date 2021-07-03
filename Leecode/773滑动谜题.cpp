#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <queue>

using namespace std;
class Solution
{
public:
    int slidingPuzzle(vector<vector<int>> &board)
    {
        vector<vector<int>> mapRotate = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {3, 1, 5}, {2, 4}};
        string s;
        for (vector<vector<int>>::iterator it = board.begin(); it != board.end(); ++it)
        {
            for(vector<int>::iterator iitt = (*it).begin(); iitt != (*it).end(); ++iitt)
                s += *iitt + '0';
        }
        int step = 0;
        if (s == "123450")
            return step;
        queue<string> q;
        set<string> visited;
        q.push(s);
        visited.emplace(s);
        while (!q.empty())
        {
            ++step;
            int l = q.size();
            while (l > 0)
            {
                s = q.front();
                int zero = s.find('0');
                q.pop();
                for (vector<int>::iterator it = mapRotate[zero].begin(); it != mapRotate[zero].end(); ++it)
                {
                    swap(s[zero], s[*it]);
                    if (s == "123450")
                        return step;

                    if (!visited.count(s))
                    {
                        visited.emplace(s);
                        q.push(s);
                    }

                    swap(s[zero], s[*it]);
                }
                --l;
            }
        }
        return -1;
    }
};