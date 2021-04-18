#include <iostream>
#include <vector>
using namespace std;

void PrintActivitySelector(int **trace, int i, int j)
{
    if (trace[i][j] == 0)
        return;
    else
    {
        cout << "a" << trace[i][j] << "\t";
        PrintActivitySelector(trace, i, trace[i][j]);//找i，k的兼容
        PrintActivitySelector(trace, trace[i][j], j);//找k，j的兼容
    }
}

int ButtomUp(int *s, int *f, int n)
{
    int **c = new int *[n + 2];
    int **trace = new int *[n + 2];

    for (int i = 0; i <= n + 1; ++i)
    {
        c[i] = new int[n + 2];
        trace[i] = new int[n + 2];
        for (int j = 0; j <= n + 1; ++j)
        {
            c[i][j] = 0;
            trace[i][j] = 0;
        }
    }
    for (int l = 3; l <= n + 2; ++l)
    {
        for (int i = 0; i <= n + 2 - l; ++i)
        {
            int j = i + l - 1;
            c[i][j] = 0;
            for (int k = i + 1; k < j; ++k)
            {
                //判断活动ak是否与ai，aj兼容
                if (s[k] < f[i] || f[k] > s[j])
                    continue;

                if (c[i][j] < c[i][k] + c[k][j] + 1)
                {
                    c[i][j] = c[i][k] + c[k][j] + 1;
                    trace[i][j] = k;
                }
            }
        }
    }
    PrintActivitySelector(trace, 0, n + 1);
    return c[0][n + 1];
}

int GreedyActivitySelector(int *s, int *f, int n, vector<int> &A)
{
    if (n <= 0)
        return 0;
    int res = 1, k = 1; // 总是先选第一个因为已经排列过了
    A.push_back(k);
    for (int i = 2; i <= n; ++i)
    {
        if (s[i] >= f[k])
        {
            ++res;
            k = i;
            A.push_back(i);
        }
    }
    return res;
}

int main()
{
    int s[13] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, INT32_MAX}, f[13] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, INT32_MAX};
    //贪心是不需要a0,an+1这个边界的，加边界是为了方便动态规划
    cout << ButtomUp(s, f, 11) << endl;
    vector<int> A(0, 0);
    cout << GreedyActivitySelector(s, f, 11, A) << endl;
    for (vector<int>::iterator it = A.begin(); it != A.end(); ++it)
        cout << *it << "\t";
}