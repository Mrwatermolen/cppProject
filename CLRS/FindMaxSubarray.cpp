#include <iostream>
using namespace std;

int FindMaxCrossSubarray(int *a, int &low, const int &mid, int &high)
{
    int leftSum = INT32_MIN, rightSum = INT32_MIN, sum = 0, leftMax = 0, rightMax = 0;
    for (int i = mid; i >= low; --i)
    {
        sum += a[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            leftMax = i;
        }
    }
    sum = 0, low = leftMax; //找到i
    for (int i = mid + 1; i <= high; ++i)
    {
        sum += a[i];
        if (sum > rightSum)
        {
            rightSum = sum;
            rightMax = i;
        }
    }
    high = rightMax;
    return (rightSum + leftSum);
}

int FindMaxSubarray(int *a, int &low, int &high)
{
    if (low == high)
        return a[low];
    else
    {
        int mid = low + ((high - low) >> 1);
        int leftLow = low, leftHigh = mid, rightLow = mid + 1, rightHigh = high, crossLow = low, crossHigh = high, leftSum, rightSum, crossSum;
        leftSum = FindMaxSubarray(a, leftLow, leftHigh);
        rightSum = FindMaxSubarray(a, rightLow, rightHigh);
        crossSum = FindMaxCrossSubarray(a, crossLow, mid, crossHigh);
        if (leftSum >= rightSum && leftSum >= crossSum)
        {
            low = leftLow, high = leftHigh;
            return leftSum;
        }
        else if (rightSum >= leftSum && rightSum >= crossSum)
        {
            low = rightLow, high = rightHigh;
            return rightSum;
        }
        else
        {
            low = crossLow, high = crossHigh;
            return crossSum;
        }
    }
}

int BottomUp(int *a, int n)
{
    int *dp = new int[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; ++i)
        dp[i] = max(dp[i - 1] + a[i], a[i]);
    int res = INT32_MIN;
    for (int i = 1; i <= n; ++i)
        res = max(dp[i], res);
    return res;
}
int ExtendedBottomUp(int *a, int &low, int &high)
{
    int cur = 0, pre = 0, l = low, h = high, res = INT32_MIN, temp;//temp用来记录每一次求和的数组发生变化时的第一个数组索引
    for (int i = l; i <= h; ++i)
    {
        if (pre > 0)
        {
            cur = pre + a[i];
        }
        else
        {
            cur = a[i];
            temp = i;
        }
        pre = cur;
        if (res < cur)
        {   //只有res被更新时才更新low和high
            high = i;
            low = temp;
            res = cur;
        }
    }
    return res;
}
int main()
{
    int A[17] = {0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}, low = 1, high = 16;
    for (int i = low; i <= high; ++i)
        cout << A[i] << "\t";
    cout << endl;
    int maxSum = ExtendedBottomUp(A, low, high);
    cout << maxSum << "\t" << low << "\t" << high;
}