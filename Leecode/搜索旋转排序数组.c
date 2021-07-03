#include <stdio.h>

int search(int *nums, int numsSize, int target)
{
    int l = 0, r = numsSize - 1, p, m, mid;
    if (numsSize <= 2)
    {
        p = 0;
    }
    while (l <= r && numsSize > 2)
    {
        p = l + ((r - l) >> 1);
        if (nums[p] < nums[p - 1] && nums[p] < nums[p + 1])
        {
            break;
        }
        else if (nums[p] > nums[numsSize - 1])
        {
            l = p + 1;
        }
        else
        {
            r = p - 1;
        }
    }
    printf("%d", p);
    p = numsSize - 1 - p;
    l = 0, r = numsSize - 1;
    while (l <= r)
    {
        m = l + ((r - 1) >> 1);
        mid = m;
        if (m > p)
        {
            m = m - p;
        }
        else
        {
            m = m + p;
        }
        if (nums[m] == target)
        {
            return m;
        }
        else if (nums[m] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return -1;
}

int main()
{
    int nums[] = {4,5,6,7,8,0,1,2};
    int target = 3;
    printf("\n %d \n",search(nums,8,target));
    return 0;

}