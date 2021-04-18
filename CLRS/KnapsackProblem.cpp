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

int main()
{
    vector<Object> o;
    o.push_back(Object(1, 5));
    o.push_back(Object(3, 6));
    o.push_back(Object(6, 6));
    o.push_back(Object(1.5, 6));
    o.push_back(Object(4, 12));
    cout << FractionalKnapsack(10, o) << endl;
}