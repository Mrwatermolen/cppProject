#include <vector>
#include <iostream>
using namespace std;

// Definition for a Node.给定一个 N 叉树，返回其节点值的层序遍历。 (即从左到右，逐层遍历)。
/**
 * Definition for a Node.
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

struct Node {
    int val;
    int numChildren;
    struct Node** children;
};

struct LinkNode
{
	Node *t;
	LinkNode *next;
};

struct LinkQueue
{
	LinkNode *font, *rear;
};

void InitLinkQueue(LinkQueue *Q)
{
	Q->font = nullptr;
	Q->rear = nullptr;
}

void EnLinkQueue(LinkQueue *Q, Node *t)
{
	LinkNode *p = new LinkNode;
	if (p == nullptr || t == nullptr)
		return;
	p->next = nullptr;
	p->t = t;
	if (Q->font == nullptr)
	{
		Q->font = p;
		Q->rear = p;
	}
	else
	{
		Q->rear->next = p;
		Q->rear = p;
	}
	return;
}

void DeLinkQueue(LinkQueue *Q, Node *&e)
{
	if (Q->font == nullptr)
		return;
	LinkNode *p = Q->font;
	Q->font = p->next;
	e = p->t;
	if (Q->rear == p)
	{
		Q->font = nullptr;
		Q->rear = nullptr;
	}
	delete p;
	return;
}

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
    LinkQueue *Q = new LinkQueue;
	InitLinkQueue(Q);
	EnLinkQueue(Q, root);
	while (!(Q->font == nullptr))
	{
		Node *e;
		DeLinkQueue(Q, e);
		cout << e->val;
        for(int i = 0; i < e->numChildren; ++i)
        {
            EnLinkQueue(Q, (*(e->children)+i));
        }
		
	}
    }
};