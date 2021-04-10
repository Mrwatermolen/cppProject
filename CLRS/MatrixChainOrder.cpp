#include <iostream>

using namespace std;

void BottomUpMCO(int *p, int **m, int n)
{
    for (int i = 1; i <= n; ++i)
        m[i][i] = 0;
    for (int l = 2; l <= n; ++l)
    {
        for (int i = 1; i <= n - l + 1; ++i)
        {
            int j = l + i - 1;
            int q = INT32_MAX;
            for (int k = i; k < j; ++k)
                q = min(q, m[i][k] + m[k + 1][i] + p[i - 1] * p[k] * p[j]);
            m[i][j] = q;
        }
    }
}

void ExtendedBottomUpMCO(int *p, int **m, int **s, int n)
{
    //p.leght=n+1 
    for (int i = 1; i <= n; ++i)
        m[i][i] = 0;
    for (int l = 2; l <= n; ++l)
    {
        for (int i = 1; i <= n - l + 1; ++i)
        {
            int j = l + i - 1;
            m[i][j] = INT32_MAX;
            for (int k = i; k < j; ++k)
            {
                int q = m[i][k] + m[k + 1][i] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void PrintOptionParens(int **s, int i, int j)
{
    if (i == j)
        cout << i;
    else
    {
        cout<<"(";
        PrintOptionParens(s,i,s[i][j]);
        PrintOptionParens(s,s[i][j]+1,j);
        cout<<")";
    }
}

int main()
{
    int p[7]={30,35,15,5,10,20,25}, n = 6;
    int **s = new int*[n+1], **m = new int*[n+1];
    for(int i = 0; i <= n; ++i)
    {
        s[i] = new int[n+1];
        m[i] = new int[n+1];
    }
    ExtendedBottomUpMCO(p,m,s,n);
    PrintOptionParens(s,1,n);
    cout<<'\n'<<m[1][n];
}