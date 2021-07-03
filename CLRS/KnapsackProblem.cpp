#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Object
{
public:
    double weight;
    double value;
    double density;
    Object(double w, double v)
    {
        weight = w;
        value = v;
        density = v / w;
    }
    /* bool operator<(const Object &rt)
    {
        return this->density > rt.density;
    } 这个重载<虽然能达到降序效果，但我感觉太不妥了*/
};

bool cmp(const Object &x, const Object &y)
{
    return x.density > y.density;
}

double FractionalKnapsack(double C, vector<Object> &o)
{

    sort(o.begin(), o.end(), cmp);
    double cur = 0, res = 0;
    for (vector<Object>::iterator it = o.begin(); it != o.end(); ++it)
    {
        if (cur + it->weight <= C)
        {
            cur += it->weight;
            res += it->value;
        }
        else
        {
            res += it->density * (C - cur);
            break;
        }
    }

    return res;
}

int ZeroOneKnapsack(int C, vector<Object> &o)
{
    if (C <= 0)
        return 0;
    int **p = new int *[C + 1];
    for (int i = 0; i <= C; ++i)
    {
        p[i] = new int[o.size() + 1];
        for (int j = 0; j <= o.size(); ++j)
            p[i][j] = 0;
    }
    for (int i = 1; i <= C; ++i)
    {
        for (int j = 1; j <= o.size(); ++j)
        {
            if (i >= o[j].weight)
                p[i][j] = max(p[i - (int)o[j].weight][j - 1] + (int)o[j].value, p[i][j - 1]);
            else
                p[i][j] = p[i][j - 1];
        }
    }
    return p[C][o.size()];
}

int main()
{
    vector<Object> o;
    o.push_back(Object(1, 5));
    o.push_back(Object(3, 6));
    o.push_back(Object(6, 6));
    o.push_back(Object(2, 9));
    o.push_back(Object(4, 12));
    cout << FractionalKnapsack(10, o) << endl;
    cout << ZeroOneKnapsack(10, o) << endl;
}