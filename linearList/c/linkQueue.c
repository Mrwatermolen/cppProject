#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode{
	int data;
	LinkNode *next;
}LinkNode;

typedef struct{
	LinkNode *font,*rear;
}*LinkQueue;

void InitLinkQueue(LinkQueue &Q){
	Q->font = NULL;
	Q->rear = NULL;
}

void DestroyLinkQueue(){}

bool LinkQueueEmpty(LinkQueue Q){
	return Q->font == NULL;
}

bool EnLinkQueue(LinkQueue Q, int x){
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	if(!p) return  false;
	p->next = NULL;
	if(LinkQueueEmpty){	
		Q->font = p;
		Q->rear = p;
	}else{
		Q->rear->next = p;
		Q->rear = p;
	}
	return true;
}

bool DeLinkQueue(LinkQueue Q, int &e){
	if(LinkQueueEmpty) return false;
	LinkNode *p = Q->font;
	Q->font = p->next;
	e = p->data;
	if(Q->rear == p){
		Q->font = NULL;
		Q->rear = NULL;
	}
	free(p);
	return true;
}

bool GetHead(LinkQueue Q, int &x){
	if(LinkQueueEmpty) return false;
	x = Q->rear->data;
	return true;
}

void PrintfLinkQueue(LinkQueue Q){
	LinkNode *p = Q->font;
	while(p){
		printf("%d>",p->data);
		p = p->next;
	}
}

void TestLinkQueue(){
	LinkQueue Q;
	InitLinkQueue(Q);
	int x;
	scanf("%d",&x);
	while(scanf("%d",&x) && x!=9999){
		if(x==999){
			PrintfLinkQueue(Q);
			continue;
		}
		if(EnLinkQueue(Q,x)){
			continue;
		}
	}
}

int main(){
	TestLinkQueue();
	return 0;
}
