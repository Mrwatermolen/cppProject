#include <stdio.h>
#include <stdlib.h>

int binSearch(int *Array, int start, int end, int key)
{
    int left, right;
    int mid;
    left = start;
    right = end;
    while (left <= right)
    {
        mid = left + (right - left) / 2; //还是溢出问题
        if (key == Array[mid])
            return mid;
        else if (key < Array[mid])
            right = mid - 1;
        else if (key > Array[mid])
            left = mid + 1;
    }
    return -1;
}

int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{
    if (!(nums1Size && nums2Size))
        return NULL;
    if (nums1Size > nums2Size)
    {
        int *temp = nums2;
        nums2 = nums1;
        nums1 = temp;
        int t = nums2Size;
        nums2Size = nums1Size;
        nums1Size = t;
    }
    returnSize = (int *)malloc(sizeof(int) * nums1Size);
    int o = 0;
    for (int i = 0; i < nums1Size; ++i)
    {
        for (int j = 0; j < nums2Size; ++j)
        {
            int k = binSearch(nums2, 0, nums2Size, nums1[i]);
            if (k != -1)
            {
                int temp = nums2[k];
                nums2[k] = nums2[nums2Size];
                nums2[nums2Size] = temp;
                --nums2Size;
                returnSize[o] = temp;
                ++o;
            }
        }
    }
    return returnSize;
}

int main()
{
    int num1[] = {1, 2, 2, 1};
    int num2[] = {2, 2};
    int *p = intersect(num1, 4, num2, 2, p);
    printf("%d %d",p[0],p[1]);
    return 0;
}