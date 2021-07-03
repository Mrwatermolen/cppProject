#include <iostream>

typedef struct BSTNode
{
    double key;
    BSTNode *leftChild, *rightChild;
} * BSTree;

int main()
{
    bool CreatBSTNode(BSTree & T, double sq[], int n);
    BSTNode *BSTSearch(BSTree T, double key);
    bool BSTInsert(BSTree &T, double key);
    bool BSTDelete(BSTree &T, double key);

    BSTree T;
    double sq[9] = {8, 3, 10, 1, 6, 4, 7, 14, 13};
    CreatBSTNode(T, sq, 9);
    //BSTDelete(T,13);
    //BSTInsert(T,13);
    //BSTDelete(T,10);
    BSTDelete(T,3);


    return 0;
}

bool CreatBSTNode(BSTree &T, double sq[], int n)
{
    bool BSTInsert(BSTree & T, double key);

    T = nullptr;
    for (int i = 0; i < n; ++i)
    {
        if (!BSTInsert(T, sq[i]))
            return false;
    }
    return true;
}

BSTNode *BSTSearch(BSTree T, double key)
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

bool BSTInsert(BSTree &T, double key)
{
    if (T == nullptr)
    {
        T = new BSTNode;
        T->key = key;
        T->leftChild = T->rightChild = nullptr;
        return true;
    }
    BSTNode *p = T;
    while (p != nullptr)
    {
        if (key == p->key)
            return false;
        if (key < p->key)
        {
            if (p->leftChild == nullptr)
            {
                p->leftChild = new BSTNode; //一定要先申请空间!因为left一定是nullptr 给p赋值后 p就不是T的结点了
                p = p->leftChild;
                break;
            }
            p = p->leftChild;
        }
        else
        {
            if (p->rightChild == nullptr)
            {
                p->rightChild = new BSTNode;
                p = p->rightChild;
                break;
            }
            p = p->rightChild;
        }
    }
    p->key = key;
    p->leftChild = p->rightChild = nullptr;
    return true;
}

//因为没有用ParentsTree 所以比较麻烦 完败
bool BSTDelete(BSTree &T, double key)
{
    BSTNode *BSTSearch(BSTree T, double key);
    void StupidInOrderTreePre(BSTNode * t, const BSTNode *p, BSTNode *&currentNode, BSTNode *&preNode);
    void StupidInOrderTreeNext(BSTNode * t, const BSTNode *p, BSTNode *&currentNode, BSTNode *&nextNode);

    BSTNode *p = BSTSearch(T, key);
    if (p == nullptr)
        return false;
    if (p->leftChild == nullptr && p->rightChild == nullptr)
    {
        delete p; //??前驱会指向野指针吗 结论是会...
        return true;
    }
    if (p->leftChild != nullptr && p->rightChild != nullptr)
    {
        //最小后继代替 找next
        BSTNode *next = nullptr, *temp = nullptr;
        StupidInOrderTreeNext(p, p, temp, next);
        p->key = next->key;
        delete next;
        return true;
    }
    if (p->leftChild != nullptr)
    {
        //p只有左子树 所以p的父节点一定是p的后继
        BSTNode *next = nullptr, *temp = nullptr;
        StupidInOrderTreeNext(T, p, temp, next);
        if (next->leftChild == p)
        {
            next->leftChild = p->leftChild;
        }
        else
        {
            next->rightChild = p->leftChild;
        }
        delete p;
        return true;
    }
    if (p->leftChild != nullptr)
    {
        //p只有右子树 所以p的父节点一定是p的前驱
        BSTNode *pre = nullptr, *temp = nullptr;
        StupidInOrderTreePre(T, p, temp, pre);
        if (pre->leftChild == p)
        {
            pre->leftChild = p->rightChild;
        }
        else
        {
            pre->rightChild = p->rightChild;
        }
        delete p;
        return true;
    }
    return false;
}

void StupidInOrderTreePre(BSTNode *t, const BSTNode *p, BSTNode *&currentNode, BSTNode *&preNode)
{
    if (t != nullptr && preNode == nullptr)
    {
        StupidInOrderTreePre(t->leftChild, p, currentNode, preNode);
        if (t == p)
        {
            preNode = currentNode;
        }
        currentNode = t;
        StupidInOrderTreePre(t->rightChild, p, currentNode, preNode);
    }
}

void StupidInOrderTreeNext(BSTNode *t, const BSTNode *p, BSTNode *&currentNode, BSTNode *&nextNode)
{
    if (t != nullptr && nextNode == nullptr)
    {
        StupidInOrderTreeNext(t->leftChild, p, currentNode, nextNode);
        if (currentNode == p)
        {
            nextNode = t;
        }
        currentNode = t;
        StupidInOrderTreeNext(t->rightChild, p, currentNode, nextNode);
    }
}
