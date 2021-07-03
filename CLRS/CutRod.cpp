#include <iostream>

using namespace std;

int CutRod(int *p, int n)
{
    //递归求解
    if (n == 0)
        return 0;
    int q = INT32_MIN;
    for (int i = 1; i <= n; ++i)
    {
        q = max(q, p[i] + CutRod(p, n - i));
    }
    return q;
}

int MemoizedCutRod(int *p, int n)
{
    int MemoizedCutRodAux(int *p, int *r, int *s, int n);
    int *r = new int[n + 1];
    int *s = new int[n + 1];
    s[0] = 0;
    for (int i = 0; i <= n; ++i)
    {
        r[i] = INT32_MIN;
    }
    int res = MemoizedCutRodAux(p, r, s, n);
    cout << "i:     ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << i << '\t';
    }
    cout << '\n'
         << "r[i]:  ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << r[i] << '\t';
    }
    cout << '\n'
         << "s[i]:  ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << s[i] << '\t';
    }
    cout << '\n';
    return res;
}

int MemoizedCutRodAux(int *p, int *r, int *s, int n)
{
    if (r[n] >= 0)
        return r[n]; //考虑到收益总是非负值,r[n]ge0说明r[n]已经被记录了直接返回
    int q = 0;
    if (n > 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            int temp = MemoizedCutRodAux(p, r, s, n - i);
            if (q < p[i] + temp)
            {
                q = p[i] + temp;
                s[n] = i;
            }
        }
    }
    r[n] = q;
    return q;
}

int BottomUpCutRod(int *p, int n)
{
    if (n <= 0)
        return 0;
    int *r = new int[n + 1];
    r[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int q = INT32_MIN;
        for (int j = 1; j <= i; ++j)
            q = max(q, p[j] + r[i - j]);
        r[i] = q;
    }
    return r[n];
}

int ExtendedBottomUpCutRod(int *p, int n)
{
    if (n <= 0)
        return 0;
    int *r = new int[n + 1];
    int *s = new int[n + 1];
    r[0] = 0, s[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int q = INT32_MIN;
        for (int j = 1; j <= i; ++j)
        {
            if (q < p[j] + r[i - j])
            {
                q = p[j] + r[i - j];
                s[i] = j;
            }
        }
        r[i] = q;
    }
    cout << "i:     ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << i << '\t';
    }
    cout << '\n'
         << "r[i]:  ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << r[i] << '\t';
    }
    cout << '\n'
         << "s[i]:  ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << s[i] << '\t';
    }
    cout << '\n';
    return r[n];
}

int main()
{
    int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30}, n = 10;
    cout << "Length: ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << i << '\t';
    }
    cout << '\n'
         << "Price:  ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << p[i] << '\t';
    }
    cout << '\n';
    cout << CutRod(p, 10) << '\n';
    cout << MemoizedCutRod(p, 10) << '\n';
    cout << BottomUpCutRod(p, n) << '\n';
    cout << ExtendedBottomUpCutRod(p, n) << '\n';
    return 0;
}