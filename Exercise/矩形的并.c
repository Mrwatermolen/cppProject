#include <stdio.h>
#include <stdlib.h>
/* Description
在 X-Y 坐标平面上，给定多个矩形，它们的边分别与坐标轴平行。请计算它们的并的面积。 

输入格式
输入第一行为一个整数 n，1<=n<=100，表示矩形的数量。
接下来有 n 行，每行包括四个数：x1,y1,x2,y2 (0<=x1<x2<=100000;0<=y1<y2<=100000)，
用空格分开，不一定为整数。
(x1,y1)表示一个长方形的左下顶点坐标，(x2,y2)表示右上顶点坐标。 

输出格式
n个矩形的并的面积，保留两位小数。  */
int main()
{
    double SumMaxtirArea();

    printf("%.2lf", SumMaxtirArea());
    return 0;
}

double SumMaxtirArea()
{
    void QuickSort(double arr[], int low, int high);

    int n;
    double sumArea = 0;
    scanf("%d", &n);
    double *x = (double *)malloc(sizeof(double) * 2 * n);
    double *y = (double *)malloc(sizeof(double) * 2 * n);
    double *sortX = (double *)malloc(sizeof(double) * 2 * n);
    double *sortY = (double *)malloc(sizeof(double) * 2 * n);

    for (int i = 0; i < 2 * n; ++i)
    {
        scanf("%lf %lf", (x + i), (y + i));
        sortX[i] = x[i], sortY[i] = y[i];
    }

    //QuickSort(sortX, 0, 2 * n);
    //QuickSort(sortY, 0, 2 * n);
    void sort(double *a, int n);
    sort(sortX, 2 * n);
    sort(sortY, 2 * n);
    for (int i = 0; i < 2 * n; ++i)
    {
        for (int j = 0; j < 2 * n; ++j)
        {
            for (int o = 0; o < 2 * n; o += 2)
            {
                if (sortX[i] >= x[o] && sortX[i + 1] <= x[o + 1])
                {
                    if (sortY[j] >= y[o] && sortY[j + 1] <= y[o + 1])
                    {
                        sumArea += (sortX[i + 1] - sortX[i]) * (sortY[j + 1] - sortY[j]);
                        break;
                    }
                }
            }
        }
    }
    return sumArea;
}

void sort(double *a, int n)
{
    int i;
    int j;
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (a[j] >= a[j + 1])
            {
                double t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}
void QuickSort(double arr[], int low, int high)
{
    int first = low;
    int last = high;
    double key = arr[first];
    if (low >= high)
        return;
    while (first < last)
    {
        while (first < last && arr[last] > key)
        {
            last--;
        }
        arr[first] = arr[last];

        while (first < last && arr[first] < key)
        {
            first++;
        }
        arr[last] = arr[first];
    }
    arr[first] = key;

    QuickSort(arr, low, first - 1);
    QuickSort(arr, first + 1, high);
}