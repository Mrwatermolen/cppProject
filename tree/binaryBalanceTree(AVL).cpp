#include <iostream>

typedef struct BBTNode
{
    double key;
    BBTNode *leftChild, *rightChild, *father;
} * BBTree;

bool BBTInsert(BBTree &T, double key)
{
    BBTNode *BBTSearch(BBTree T, double key);
    void Rebalance(BBTNode * t, BBTree & T);

    if (T == nullptr)
    {
        T = new BBTNode;
        T->key = key;
        T->leftChild = T->rightChild = T->father = nullptr;
        //T->height = 1;
        return true;
    }
    else
    {
        BBTNode *p = T;
        while (p != nullptr)
        {
            if (key == p->key)
                return false;
            if (key < p->key)
            {
                if (p->leftChild == nullptr)
                {
                    //p->height += 1;
                    p->leftChild = new BBTNode; //一定要先申请空间!因为left一定是nullptr 给p赋值后 p就不是T的结点了
                    p->leftChild->father = p;
                    p = p->leftChild;
                    break;
                }
                p = p->leftChild;
            }
            else
            {
                if (p->rightChild == nullptr)
                {
                    //p->height += 1;
                    p->rightChild = new BBTNode;
                    p->rightChild->father = p;
                    p = p->rightChild;
                    break;
                }
                p = p->rightChild;
            }
        }
        p->key = key;
        p->leftChild = p->rightChild = nullptr;
    }
    Rebalance(T, T);
}

BBTNode *BBTSearch(BBTree T, double key)
{
    while (T != nullptr)
    {
        if (key == T->key)
        {
            return T;
        }
        else if (key < T->key)
        {
            T = T->leftChild;
        }
        else
        {
            T = T->rightChild;
        }
    }
    return nullptr;
}

int GetHeight(BBTNode *t)
{
    if (t == nullptr)
        return 0;
    int l = GetHeight(t->leftChild);
    int r = GetHeight(t->rightChild);
    return (l > r) ? (l + 1) : (r + 1);
}

void Rebalance(BBTNode *t, BBTree &T)
{
    int GetHeight(BBTNode * t);
    void LeftRotate(BBTNode * t, BBTree & T);
    void RightRotate(BBTNode * t, BBTree & T);

    while (t != nullptr)
    {
        int balance = GetHeight(t->leftChild) - GetHeight(t->rightChild);
        if (balance > 1)
        {
            if (t->rightChild == nullptr)
            {
                if (t->leftChild->leftChild == nullptr)
                {
                    LeftRotate(t->leftChild, T);
                }
            }
            else if (t->leftChild->leftChild->leftChild == nullptr)
            {
                LeftRotate(t->leftChild, T);
            }
            RightRotate(t, T);
        }
        else if (balance < -1)
        {
            if (t->leftChild == nullptr)
            {
                if (t->rightChild->rightChild == nullptr)
                {
                    RightRotate(t->rightChild, T);
                }
            }
            else if (t->rightChild->rightChild->rightChild == nullptr)
            {
                RightRotate(t->rightChild, T);
            }
            LeftRotate(t, T);
        }
        else
        {
            t = t->father;
        }
    }
}

void LeftRotate(BBTNode *t, BBTree &T)
{
    int GetHeight(BBTNode * t);

    //左旋 考虑根结点
    BBTNode *p = t->rightChild;
    t->rightChild = p->leftChild;
    p->leftChild->father = t;
    p->leftChild = t;
    if (t == T)
    {
        T = p;
    }
    else if (t->father->leftChild == t)
    {
        t->father->leftChild = p;
    }
    else
    {
        t->father->rightChild = p;
    }
    p->father = t->father;
    t->father = p;

    //重新计算结点高度
    /* t->height = GetHeight(t);
    p->rightChild->height = GetHeight(t->rightChild);
    p->height = GetHeight(p); */
}

void RightRotate(BBTNode *t, BBTree &T)
{
    int GetHeight(BBTNode * t);

    //右旋 考虑根结点
    BBTNode *p = t->leftChild;
    t->leftChild = p->rightChild;
    p->rightChild->father = t;
    p->rightChild = t;
    if (t == T)
    {
        T = p;
    }
    else if (t->father->leftChild == t)
    {
        t->father->leftChild = p;
    }
    else
    {
        t->father->rightChild = p;
    }
    p->father = t->father;
    t->father = p;

    //重新计算结点的深度
    /* t->height = GetHeight(t);
    p->leftChild->height = GetHeight(p->leftChild);
    p->height = GetHeight(p); */
}