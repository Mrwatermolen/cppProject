#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode{
	int data;
	struct LinkNode *next;
}*LinkStack;

void InitLinkStack(LinkStack &L){
	L = NULL;
}

void DestroyLinkStack(LinkStack &L){
	p = L;
	while(p){
		p = L->next;
		free(L);
		L = p;
	}
}

bool Push(LinkNode *p, int x){
	LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));
	q->next = p;
	q->data = x;
	p = q;
	return true;
}

bool Pop(LinkNode *p, int &e){
	if(p==NULL) return false;
	LinkNode *q = p->next;
	free(p);
	p = q;
	return true;
}

bool GetTop(LinkNode *p, int &x){
	if(p==NULL) return false;
	x = p->data;
	return true;
}
