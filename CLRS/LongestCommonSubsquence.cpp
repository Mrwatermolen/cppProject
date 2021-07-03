#include <iostream>
#include <string>
using namespace std;

void PrintLCS(string A, int **b, int i, int j)
{
    if (!(i * j))
        return;

    if (b[i][j] == (b[i-1][j-1] + 1))
    {
        PrintLCS(A, b, i - 1, j - 1);
        cout << A[i - 1];
    }
    else if (b[i][j] == (b[i-1][j]))
        PrintLCS(A, b, i - 1, j);
    else
        PrintLCS(A, b, i, j - 1);
}

int LCSLength(string X, string Y)
{
    int **c = new int *[X.length() + 1];
    for (int i = 0; i <= X.length(); ++i)
        c[i] = new int[Y.length() + 1];
    for (int i = 0; i <= X.length(); ++i)
        c[i][0] = 0;
    for (int i = 0; i <= Y.length(); ++i)
        c[0][i] = 0;

    //关键
    for (int i = 1; i <= X.length(); ++i)
        for (int j = 1; j <= Y.length(); ++j)
            if (X[i - 1] == Y[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
    PrintLCS(X, c, X.length(), Y.length());
    return c[X.length()][Y.length()];
}

int main()
{
    string X = "ABCBDAB", Y = "BDCABA";
    cout << LCSLength(X, Y) << endl;
    return 0;
}