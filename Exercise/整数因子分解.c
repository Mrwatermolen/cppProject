/*
9718 整数因子分解（优先做）
Description
大于1的正整数 n 都可以分解为 n = x1 * x2 * ... * xm， 每个xi为大于1的因子，即1<xi<=n 。
例如：当n=12时，共有8种不同的分解式：
12 = 12
12 = 6*2
12 = 4*3
12 = 3*4
12 = 3*2*2
12 = 2*6
12 = 2*3*2
12 = 2*2*3
对于给定正整数n，计算n共有多少种不同的分解式。
输入格式
第一行一个正整数n （1<=n<=1000000）
输出格式
不同的分解式数目
输入样例
12
输出样例
8
}*/
#include <stdio.h>

int main()
{
    void solve(int n, int *total);
    int num = 0, n;
    scanf("%d", &n);
    int *total = &num;
    solve(n, total);
    printf("%d", num);
    return 0;
}

void solve(int n, int *total)
{
    if (n == 1)
        (*total)++;
    for (int i = 2; i <= n; ++i)
    {
        if (n % i == 0)
            solve(n / i, total);
    }
}