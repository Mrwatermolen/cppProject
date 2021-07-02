#include <string>
#include <iostream>
#include <map>
using namespace std;

class Solution
{
public:
    string intToRoman(int num)
    {
        map<string, int> m({{"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100}, {"XC", 90}, {"L", 50}, {"XL", 40}, {"X", 10}, {"IX", 9}, {"V", 5}, {"IV", 4}, {"I", 1}});
        string res;
        for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it)
        {
            while (num >= it->second)
            {
                num -= it->second;
                res += it->first;
            }
            
                

        }
    }
};