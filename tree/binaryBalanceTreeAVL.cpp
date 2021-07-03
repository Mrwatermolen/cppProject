#include <iostream>

using namespace std;

typedef struct BBTNode
{
    double key;
    BBTNode *leftChild, *rightChild, *father;
} * BBTree;

int main()
{
    void BBTInsert(BBTree & T, double key);
    void InOrder(BBTree t);
    void LevelOrder(const BBTree &T);

    BBTree T;
    double sq[15] = {100, 50, 500, 25, 75, 350, 1000, 1, 30, 65, 80, 300, 400, 900, 1500};
    for (int i = 0; i < 15; ++i)
    {
        BBTInsert(T, sq[i]);
    }
    cout << endl;
    InOrder(T);
    cout << endl;
    LevelOrder(T);

    /* //LL p->rightChild = nullptr
    BBTInsert(T, 0.1);
    BBTInsert(T, 0.01); */
    /* //LL
    BBTInsert(T, 60);
    BBTInsert(T, 68);
    BBTInsert(T, 53); */
    /* //LR p->leftChild = nullptr
    BBTInsert(T, 60);
    BBTInsert(T, 63); */
    /* //LR
    BBTInsert(T, 60);
    BBTInsert(T, 68);
    BBTInsert(T, 67); */
    
    /* BBTree TT = nullptr;
    double sqq[5] = {5, 4, 6, 2, 3};
    for (int i = 0; i < 5; ++i)
    {
        BBTInsert(TT, sqq[i]);
    }
    cout << endl;
    InOrder(TT);
    cout << endl;
    LevelOrder(TT);
    //root is unbalance
    BBTInsert(TT, 1);
    cout << endl;
    InOrder(TT);
    cout << endl;
    LevelOrder(TT); */
    return 0;
}

void InOrder(BBTree t)
{
    if (t != nullptr)
    {
        InOrder(t->leftChild);
        cout << t->key << "->";
        InOrder(t->rightChild);
    }
}

#pragma region LinkQueue

struct LinkNode
{
    BBTNode *t;
    LinkNode *next;
};

struct LinkQueue
{
    LinkNode *font, *rear;
};

void InitLinkQueue(LinkQueue *Q)
{
    //Q = new LinkQueue;
    Q->font = nullptr;
    Q->rear = nullptr;
}

bool LinkQueueEmpty(const LinkQueue *Q)
{
    return Q->font == nullptr;
}

bool EnLinkQueue(LinkQueue *Q, BBTNode *t)
{
    LinkNode *p = new LinkNode;
    if (p == nullptr || t == nullptr)
        return false;
    p->next = nullptr;
    p->t = t;
    if (LinkQueueEmpty(Q))
    {
        Q->font = p;
        Q->rear = p;
    }
    else
    {
        Q->rear->next = p;
        Q->rear = p;
    }
    return true;
}

bool DeLinkQueue(LinkQueue *Q, BBTNode *&e)
{
    if (LinkQueueEmpty(Q))
        return false;
    LinkNode *p = Q->font;
    Q->font = p->next;
    e = p->t;
    if (Q->rear == p)
    {
        Q->font = nullptr;
        Q->rear = nullptr;
    }
    delete p;
    return true;
}

#pragma endregion LinkQueue

void LevelOrder(const BBTree &T)
{
    LinkQueue *Q = new LinkQueue;
    InitLinkQueue(Q);
    EnLinkQueue(Q, T);
    while (!LinkQueueEmpty(Q))
    {
        BBTNode *e;
        DeLinkQueue(Q, e);
        cout << e->key << "->";
        EnLinkQueue(Q, e->leftChild);
        EnLinkQueue(Q, e->rightChild);
    }
}

void BBTInsert(BBTree &T, double key)
{
    BBTNode *BBTSearch(BBTree T, double key);
    void Rebalance(BBTNode * t, BBTree & T);

    if (T == nullptr)
    {
        T = new BBTNode;
        T->key = key;
        T->leftChild = T->rightChild = T->father = nullptr;
        //T->height = 1;
        Rebalance(T, T);
        return;
    }
    else
    {
        BBTNode *p = T;
        while (p != nullptr)
        {
            if (key == p->key)
                return;
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
        Rebalance(p, T);
        return;
    }
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
    if (p->leftChild != nullptr)
    {
        p->leftChild->father = t;
    }
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
    if (p->rightChild != nullptr)
    {
        p->rightChild->father = t;
    }
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
