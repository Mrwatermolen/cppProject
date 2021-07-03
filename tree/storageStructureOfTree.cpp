#include <iostream>
#include <string>
#define MaxSize 100

using namespace std;

struct ParentsTNode
{
    double data;
    int parent;
};

struct ParentsTree
{
    ParentsTNode nodes[MaxSize];
    int n;
};

#pragma region ListChildTree

struct CTNoode
{
    int child;//next所指向的孩子在数组中的位置
    CTNoode *next;//下一个孩子
};

struct CTBox
{
    double data;
    CTNoode *firstChild;
};

struct CTree
{
    CTBox nodes[MaxSize];
    int n,r;//结点数和根的位置
};

#pragma endregion ListChildTree

typedef struct CSNode
{
    double data;
    CSNode *firstChild, *nextsilbling; //第一个孩子,右兄弟指针
} * CSTree;

int main()
{
    return 0;
}
