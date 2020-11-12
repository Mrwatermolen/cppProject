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

typedef struct ThreadBinaryTreeNode
{
	ThreadBinaryTreeNode *leftChild, *rightChild;
	double data;
	int leftTag, rightTag; // 0 means childPoint point to node. 1 means childPoint is thread.
} * ThreadBinaryTree;

int main()
{
	void InitThreadTree(ThreadBinaryTree & T);
	void BuildThreadTree(ThreadBinaryTree & T);
	void CreatInOrderThreadTree(ThreadBinaryTree & T);

	ThreadBinaryTree T;
	InitThreadTree(T);
	BuildThreadTree(T);
	CreatInOrderThreadTree(T);
	return 0;
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

#pragma region OdinaryBinaryTree

void TestBinaryTree()
{
	void InitTree(BinaryTree & t);
	void BuildBinaryTree(BinaryTree & t);
	//要传入指针是因为使用了递归
	void PreOrder(BinaryTree t);
	void InOrder(BinaryTree t);
	void PostOrder(BinaryTree t);
	void LevelOrder(const BinaryTree &t);
	void StupidInOrderThreadTree(const BinaryTreeNode *t, const BinaryTree &T);

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

	cout << endl;
	StupidInOrderThreadTree(t, t);
	cout << endl;
	StupidInOrderThreadTree(t->leftChild, t);
	cout << endl;
	StupidInOrderThreadTree(t->rightChild, t);
	cout << endl;
	StupidInOrderThreadTree(t->leftChild->leftChild, t);
	cout << endl;
	StupidInOrderThreadTree(t->leftChild->rightChild, t);
	cout << endl;
	StupidInOrderThreadTree(t->rightChild->leftChild, t);
	cout << endl;
	StupidInOrderThreadTree(t->rightChild->rightChild, t);
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

#pragma region StupidInOrderThreadTree

void StupidInOrderThreadTree(const BinaryTreeNode *t, const BinaryTree &T)
{
	void StupidInOrderTreadTreePre(BinaryTreeNode * t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode);
	void StupidInOrderTreadTreeNext(BinaryTreeNode * t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode);

	if (T == nullptr || t == nullptr)
		return;

	BinaryTreeNode *q = nullptr, *pre = nullptr;
	StupidInOrderTreadTreePre(T, t, q, pre);
	cout << t->data << " Pre is " << ((pre == nullptr) ? -1 : pre->data) << endl;

	q = nullptr, pre = nullptr;
	StupidInOrderTreadTreeNext(T, t, q, pre);
	cout << t->data << " Next is " << ((q == nullptr) ? -1 : q->data) << endl;
}

void StupidInOrderTreadTreePre(BinaryTreeNode *t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode)
{
	if (t != nullptr && preNode == nullptr)
	{
		StupidInOrderTreadTreePre(t->leftChild, p, currentNode, preNode);
		if (t == p)
		{
			preNode = currentNode;
		}
		currentNode = t;
		StupidInOrderTreadTreePre(t->rightChild, p, currentNode, preNode);
	}
}

void StupidInOrderTreadTreeNext(BinaryTreeNode *t, const BinaryTreeNode *&p, BinaryTreeNode *&currentNode, BinaryTreeNode *&preNode)
{
	if (t != nullptr && currentNode == nullptr)
	{
		StupidInOrderTreadTreeNext(t->leftChild, p, currentNode, preNode);
		if (preNode == p)
		{
			currentNode = t;
		}
		preNode = t;
		StupidInOrderTreadTreeNext(t->rightChild, p, currentNode, preNode);
	}
}

#pragma endregion StupidInOrderThreadTree

#pragma endregion OdinaryBinaryTree

#pragma region ThreadBinaryTree

void InitThreadTree(ThreadBinaryTree &T)
{
	T = new ThreadBinaryTreeNode;
	T->leftChild = nullptr;
	T->rightChild = nullptr;
	T->leftTag = 0;
	T->rightTag = 0;
}

void BuildThreadTree(ThreadBinaryTree &T)
{
	//1 2 3 9999 4 9999 9999 5 9999 9999 6 7 9999 9999 9999
	if (T == nullptr)
	{
		InitThreadTree(T);
	}
	double x = 0;
	cout << "Input x" << endl;
	cin >> x;
	if (x == 9999)
	{
		delete T;
		T = nullptr;
		return;
	}
	T->data = x;
	BuildThreadTree(T->leftChild);
	BuildThreadTree(T->rightChild);
}

void CreatIPreOrderThreadTree(ThreadBinaryTree &T)
{
	void PreOrderThread(ThreadBinaryTreeNode * &t, ThreadBinaryTreeNode * &preNode);
	ThreadBinaryTreeNode *pre = nullptr;
	if (T != nullptr)
	{
		PreOrderThread(T, pre);
		pre->rightChild = nullptr;
		pre->rightTag = 1;
	}
}

void PreOrderThread(ThreadBinaryTreeNode *&t, ThreadBinaryTreeNode *&preNode)
{
	if (t != nullptr)
	{
		if (t->leftChild == nullptr)
		{
			t->leftChild = preNode;
			t->leftTag = 1;
		}
		if (preNode != nullptr && preNode->rightChild == nullptr)
		{
			preNode->rightChild = t;
			preNode->rightTag = 1;
		}
		preNode = t;
		if (t->leftTag == 0)
		{
			PreOrderThread(t->leftChild, preNode);
		}
		PreOrderThread(t->rightChild, preNode);
	}
}

void CreatInOrderThreadTree(ThreadBinaryTree &T)
{
	void InOrderThread(ThreadBinaryTreeNode * &t, ThreadBinaryTreeNode * &preNode);
	ThreadBinaryTreeNode *pre = nullptr;
	if (T != nullptr)
	{
		InOrderThread(T, pre);
		pre->rightChild = nullptr;
		pre->rightTag = 1;
	}
}

void InOrderThread(ThreadBinaryTreeNode *&t, ThreadBinaryTreeNode *&preNode)
{
	if (t != nullptr)
	{
		InOrderThread(t->leftChild, preNode);
		if (t->leftChild == nullptr)
		{
			t->leftChild = preNode;
			t->leftTag = 1;
		}
		if (preNode != nullptr && preNode->rightChild == nullptr)
		{
			preNode->rightChild = t;
			preNode->rightTag = 1;
		}
		preNode = t;
		InOrderThread(t->rightChild, preNode);
	}
}

void CreatPostOrderThreadTree(ThreadBinaryTree &T)
{
	void PostOrderThread(ThreadBinaryTreeNode * &t, ThreadBinaryTreeNode * &preNode);
	ThreadBinaryTreeNode *pre = nullptr;
	if (T != nullptr)
	{
		PostOrderThread(T, pre);
		pre->rightChild = nullptr;
		pre->rightTag = 1;
	}
}

void PostOrderThread(ThreadBinaryTreeNode *&t, ThreadBinaryTreeNode *&preNode)
{
	if (t != nullptr)
	{
		PostOrderThread(t->leftChild, preNode);
		PostOrderThread(t->rightChild, preNode);
		if (t->leftChild == nullptr)
		{
			t->leftChild = preNode;
			t->leftTag = 1;
		}
		if (preNode != nullptr && preNode->rightChild == nullptr)
		{
			preNode->rightChild = t;
			preNode->rightTag = 1;
		}
		preNode = t;
	}
}

#pragma endregion ThreadBinaryTree
