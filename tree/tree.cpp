#include <iostream>
#include <string>
#define MaxSize 100

using namespace std;

typedef struct BinaryTreeNode
{
	BinaryTreeNode *leftChild;
	BinaryTreeNode *rightChild;
	double data;
} * BinaryTree;

int main()
{
	void InitTree(BinaryTree & t);
	void BuildBinaryTree(BinaryTree & t);
	//要传入指针是因为使用了递归
	void PreOrder(BinaryTree t);
	void InOrder(BinaryTree t);
	void PostOrder(BinaryTree t);
	void LevelOrder(const BinaryTree &t);
	void ThreadTree(const BinaryTreeNode *t, const BinaryTree &T);

	BinaryTree t;
	InitTree(t);
	BuildBinaryTree(t);
	cout << endl;

	PreOrder(t);
	cout << endl;
	InOrder(t);
	cout << endl;
	PostOrder(t);
	cout << endl;
	LevelOrder(t);
	cout << endl;

	/* cout << endl;
	ThreadTree(t, t);
	cout << endl;
	ThreadTree(t->leftChild, t);
	cout << endl;
	ThreadTree(t->rightChild, t);
	cout << endl;
	ThreadTree(t->leftChild->leftChild, t);
	cout << endl;
	ThreadTree(t->leftChild->rightChild, t);
	cout << endl;
	ThreadTree(t->rightChild->leftChild, t);
	cout << endl;
	ThreadTree(t->rightChild->rightChild, t); */
	return 0;
}

void InitTree(BinaryTree &t)
{
	t = new BinaryTreeNode;
	t->leftChild = nullptr;
	t->rightChild = nullptr;
	t->data = 0;
}

void BuildBinaryTree(BinaryTree &t)
{
	//1 2 3 9999 9999 4 9999 9999 5 6 9999 9999 7 9999 9999
	if (t == nullptr)
	{
		InitTree(t);
	}
	double x = 0;
	cout << "Input  x" << endl;
	cin >> x;
	if (x == 9999)
	{
		delete t;
		t = nullptr;
		return;
	}
	t->data = x;
	BuildBinaryTree(t->leftChild);
	BuildBinaryTree(t->rightChild);
}

void VisitTreeNode(const BinaryTreeNode *t)
{
	cout << t->data;
}

void PreOrder(BinaryTree t)
{
	if (t != nullptr)
	{
		VisitTreeNode(t);
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}

void InOrder(BinaryTree t)
{
	if (t != nullptr)
	{
		InOrder(t->leftChild);
		VisitTreeNode(t);
		InOrder(t->rightChild);
	}
}

void PostOrder(BinaryTree t)
{
	if (t != nullptr)
	{
		PostOrder(t->leftChild);
		PostOrder(t->rightChild);
		VisitTreeNode(t);
	}
}

#pragma region LinkQueue

struct LinkNode
{
	BinaryTreeNode *t;
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

bool EnLinkQueue(LinkQueue *Q, BinaryTreeNode *t)
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

bool DeLinkQueue(LinkQueue *Q, BinaryTreeNode *&e)
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

void LevelOrder(const BinaryTree &t)
{
	LinkQueue *Q = new LinkQueue;
	InitLinkQueue(Q);
	EnLinkQueue(Q, t);
	while (!LinkQueueEmpty(Q))
	{
		BinaryTreeNode *e;
		DeLinkQueue(Q, e);
		cout << e->data;
		EnLinkQueue(Q, e->leftChild);
		EnLinkQueue(Q, e->rightChild);
	}
}

void ThreadTree(const BinaryTreeNode *t, const BinaryTree &T)
{
	void InOrderTreadTreePre(BinaryTreeNode * t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode);
	void InOrderTreadTreeNext(BinaryTreeNode * t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode);

	if (T == nullptr || t == nullptr)
		return;

	BinaryTreeNode *q = nullptr, *pre = nullptr;
	InOrderTreadTreePre(T, t, q, pre);
	cout << t->data << " Pre is " << ((pre == nullptr) ? -1 : pre->data) << endl;

	q = nullptr, pre = nullptr;
	InOrderTreadTreeNext(T, t, q, pre);
	cout << t->data << " Next is " << ((q == nullptr) ? -1 : q->data) << endl;
}

void InOrderTreadTreePre(BinaryTreeNode *t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode)
{
	if (t != nullptr && preNode == nullptr)
	{
		InOrderTreadTreePre(t->leftChild, p, currentNode, preNode);
		if (t == p)
		{
			preNode = currentNode;
		}
		currentNode = t;
		InOrderTreadTreePre(t->rightChild, p, currentNode, preNode);
	}
}

void InOrderTreadTreeNext(BinaryTreeNode *t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode)
{
	if (t != nullptr && currentNode == nullptr)
	{
		InOrderTreadTreeNext(t->leftChild, p, currentNode, preNode);
		if (preNode == p)
		{
			currentNode = t;
		}
		preNode = t;
		InOrderTreadTreeNext(t->rightChild, p, currentNode, preNode);
	}
}