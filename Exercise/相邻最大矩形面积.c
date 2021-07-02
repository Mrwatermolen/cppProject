#include <stdio.h>
#include <stdlib.h>
/* Description
在X轴上水平放置着 N 个条形图，这 N 个条形图就组成了一个柱状图，每个条形图都是一个矩形，每个
矩形都有相同的宽度，均为1单位长度，但是它们的高度并不相同。 
你的任务就是计算柱状图中以X轴为底边的最大矩形的面积。 */
int main()
{
    int FindNearbyMartixMaxArea(int n, int martixH[]);
    int n;
    scanf("%d", &n);
    int *arrayM = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", (arrayM + i));
    }
    int maxArea = FindNearbyMartixMaxArea(n, arrayM);
    printf("%d", maxArea);
    return 0;
}

int FindNearbyMartixMaxArea(int n, int martixH[])
{
    int left, right, maxWidth, maxArea = 0;
    for (int i = 0; i < n; ++i)
    {
        left = right = i;
        maxWidth = 1;
        for (int j = left - 1; j >= 0; --j)
        {
            if (martixH[j] >= martixH[i])
            {
                ++maxWidth;
            }
            else
            {
                break;
            }
        }
        for (int j = right + 1; j < n; ++j)
        {
            if (martixH[j] >= martixH[i])
            {
                ++maxWidth;
            }
            else
            {
                break;
            }
        }
        int temp = maxWidth * martixH[i];
        if (temp > maxArea)
        {
            maxArea = temp;
        }
    }
    return maxArea;
}