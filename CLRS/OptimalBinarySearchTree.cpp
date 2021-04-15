#include <iostream>
using namespace std;

void PrintBST(int **root, int i, int j, int preRoot, int flag)
{ //flag=0:left flag=1:root flag=2:right
    string str[3] = {" left ", " is root ", " right "};
    int r = root[i][j];
    if (j >= i)
    {
        if (flag == 1)
            cout << "k" << r << str[flag] << "k" << endl;
        else
            cout << "k" << r << str[flag] << "k" << preRoot << endl;
        PrintBST(root, i, r - 1, r, 0);
        PrintBST(root, r + 1, j, r, 2);
    }
    else
        cout << "d" << j << str[flag] << "k" << preRoot << endl;
}
double OptimalBST(double *p, double *q, int n)
{
    int **root = new int *[n + 2];    //其实只用到1~n
    double **e = new double *[n + 2]; //n+1
    double **w = new double *[n + 2];
    for (int i = 1; i <= n + 1; ++i)
    {
        root[i] = new int[n + 1];
        e[i] = new double[n + 1];
        w[i] = new double[n + 1];
    }
    for (int i = 1; i <= n + 1; ++i)
    {
        e[i][i - 1] = q[i-1];
        w[i][i - 1] = q[i-1];
    }

    for (int l = 1; l <= n; ++l)
    {
        for (int i = 1; i <= n - l + 1; ++i)
        {
            int j = i + l - 1;
            e[i][j] = INT32_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; ++r)
            {
                double t = e[r + 1][j] + e[i][r - 1] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    PrintBST(root, 1, n, 0, 1);
    return e[1][n];
}

int main()
{
    double p[6] = {0, 0.15, 0.10, 0.05, 0.1, 0.2}, q[6] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};
    cout << OptimalBST(p, q, 5);
}