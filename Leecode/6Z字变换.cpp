#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    string convert(string s, int numRow)
    {
        int len = s.size();
        if (len <= 1)
            return s;
        string res;
        int edge = (len - 1) / (2 * (numRow - 1));
        for (int i = 0; i < numRow; ++i)
        {
            for (int j = 0; j <= edge; ++j)
            {
                int index = 2 * (numRow - 1) * j + i;
                if (index < len)
                {
                    res += s[index];
                }
                if (i != 0 && i != numRow - 1)
                {
                    //index = 2 * (numRow - 1) * j + i + numRow - 1 - i + numRow - 1 - i;
                    index = 2 * (numRow - 1) * (j + 1) - i;
                    if (index < len)
                    {
                        res += s[index];
                    }
                }
            }
        }
        return res;
    }
};