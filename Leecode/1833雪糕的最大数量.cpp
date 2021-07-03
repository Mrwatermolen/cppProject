#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maxIceCream(vector<int> &costs, int coins)
    {
        sort(costs.begin(), costs.end());
        int count = 0;
        for (int i = 1; i < costs.size(); ++i)
        {
            if (costs[i] > coins)
                break;
            ++count;
            coins -= costs[i];
        }
        return count;
    }
};