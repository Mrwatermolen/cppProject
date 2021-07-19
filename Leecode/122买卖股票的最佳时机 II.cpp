#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int min = prices[0], profit = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if (min > prices[i])
            {
                min = prices[i];
            }
            if (0 < prices[i] - min)
            {
                profit += prices[i] - min;
                min = prices[i];
            }
        }
        return profit;
    }
};