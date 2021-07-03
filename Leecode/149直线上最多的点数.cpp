#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        int res = 0, n = points.size();
        if (n <= 2)
            return n;

        for (int i = 0; i < n; ++i)
        {
            int temp = 0;
            map<float, int> sum;
            for (int j = 0; j < n; ++j)
            {
                if (j == i)
                    continue;
                float k = (points[i][1] - points[j][1]) / (float(points[i][0] - points[j][0]));

                if (sum[k] == 0)
                {
                    sum[k] = 2;
                }
                else
                {
                    ++sum[k];
                }

                if (temp < (sum[k]))
                {
                    temp = sum[k];
                }
            }
            res = max(res, temp);
        }
        return res;
    }
};