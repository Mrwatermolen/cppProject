#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *searchRange(int *nums, int numsSize, int target, int *returnSize);
    int a[] = {5,7,7,8,8,10};//{1, 1, 1, 2, 4, 4, 4, 5, 5, 5, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9, 9, 10};
    int t = 6;//22;
    int *r = searchRange(a, t, 8, r);
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    int BinSearch(int *R, int n, int K);
    int *returnNums = (int *)malloc(sizeof(int) * 2);
    returnNums[0] = returnNums[1] = BinSearch(nums, numsSize, target);
    if (returnNums[0] == -1)
        return returnNums;

/*     int first = 0, midl = returnNums[0], midh = returnNums[0], last = numsSize - 1, flagl = 0, flagh = 0;
    //return returnNums;
    if (nums[first] == target)
    {
        returnNums[0] = first;
        flagl = 1;
    }
    if (nums[last] == target)
    {
        returnNums[1] = last;
        flagh = 1;
    }
    while (flagh == 0 || flagl == 0)
    {
        midl--;
        midh++;
        if (nums[midl] != target && flagl == 0)
        {
            returnNums[0] = midl + 1;
            flagl = 1;
        }
        if (nums[midh] != target && flagh == 0)
        {
            returnNums[1] = midh - 1;
            flagh = 1;
        }
        if (nums[first] == target && flagl == 0)
        {
            returnNums[0] = first;
            flagl = 1;
        }
        if (nums[last] == target && flagh == 0)
        {
            returnNums[1] = last;
            flagh = 1;
        }
        first++;
        last--;
    }
    return returnNums; */

    int first = 0, last = returnNums[0];
    while (1)
    {
        last = BinSearch(nums, (last - first), target);
        if (last == -1)
            break;
        if (last == 0 || nums[last - 1] != target)
        {
            returnNums[0] = last;
            break;
        }
    }
    first = returnNums[1], last = numsSize - 1;
    while (1)
    {
        first = BinSearch((nums + first + 1), (last - first), target) + first + 1;
        if (first == -1)
            break;
        if (first == numsSize - 1 || nums[first + 1] != target)
        {
            returnNums[1] = first;
            break;
        }
    }
    return returnNums;
}

int BinSearch(int *R, int n, int K)
{
    //在有序表R[0..n-1]中进行二分查找，成功时返回结点的位置，失败时返回-1
    int low = 0, high = n - 1, mid; //置当前查找区间上、下界的初值
    while (low <= high)
    {
        mid = (high + low) / 2;
        if (R[mid] == K)
            return mid; //查找成功返回
        if (R[mid] < K)
            low = mid + 1; //继续在R[mid+1..high]中查找
        else
            high = mid - 1; //继续在R[low..mid-1]中查找
    }
    if (low > high)
        return -1; //当low>high时表示所查找区间内没有结果，查找失败
}