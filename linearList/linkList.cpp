#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//==========================================================单链表=======================================================
//只写了带头指针的单链表
typedef struct LNode{
	struct LNode *next;
	int data;
}LNode,*LinkList;

void InitLinkList(LinkList &L){//有必要传入引用吗
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	L->data = 0;
}

void DestroyLinkList(LinkList &L){
	LNode *p = L;
	if(NULL==p) return;
	while(p!=NULL){
		p = L->next;
		free(L);
		L = p;
	}	
}

void HeadInsertLinkList(LinkList &L){
	printf("\nHEAD INSERT!\n");
	bool InsertNextNode(LNode *p,int i);//??这样声明也可以？？
	int data;
	while(scanf("%d",&data)) if(9999==data || !(InsertNextNode(L,data))) break;
}

void TailInsertLinkList(LinkList &L){
	printf("\nTAIL INSERT\n");
	bool InsertNextNode(LNode *p,int i);
	LNode *s,*r;
	int data;
	r = L;
	while(scanf("%d",&data)){
		if(9999==data) break;
		s = r;
		if(!InsertNextNode(s,data)) break;
		r = s->next;
	}
}

int ListLength(LinkList &L){
	int i;
	LNode *p = L;
	for(i=0;p->next!=NULL;i++) p = p->next;
	return i;
}

LNode* GetLNode(LinkList &L,int i){
	LNode *p = NULL;
	if(i<0) return p;
	p = L;
	while(i>=1 && p != NULL){
		p = p->next;
		i--;
	}
	return p;
}

bool InsertNextNode(LNode *p,int data){//后插
	if(NULL==p) return false;
	LNode *insert = (LNode *)malloc(sizeof(LNode));
	if(NULL==insert) return false;
	insert->next = p->next;
	p->next = insert;
	insert->data = data;
	return true;
}

bool InsertBackNode(LNode *p,int data){
	if(NULL==p || NULL==p->next) return false;
	LNode *insert = (LNode *)malloc(sizeof(LNode));
	if(NULL==insert) return false;
	insert->data = p->data;
	insert->next = p->next;
	p->next = insert;
	p->data = data;
	return true;
}

bool DeleteNode(LNode *p,int &e){//无法删除最后一个否则会有野指针
	if(NULL==p || NULL==p->next) return false;
	LNode *s = p->next;
	e = p->data;
	p->data = s->data;
	p->next = s->next;
	free(s);
	return true;
}

bool ListInsert(LinkList &L,int i,int data){
	LNode *p = GetLNode(L,i-1);	
	return InsertNextNode(p,data);
}

bool ListDelete(LinkList &L,int i,int &e){
	LNode *p = GetLNode(L,i);
	return DeleteNode(p,e);
}

void PrintLinkList(LinkList &L){
	LNode *p = L->next;
	printf("\n");
	while(p != NULL){
		printf("%d->",p->data);
		p = p->next;
	}
	printf("\r\n");
}

//==========================================================END SingleLinkList=======================================================


//==========================================================双链表=======================================================

typedef struct DLNode{
	int data;
	DLNode *next;
	DLNode *prior;
}DLNode,*DLinkList;

void InitDLL(DLinkList &L){
	L = (DLinkList)malloc(sizeof(DLNode));
	L->next = L->prior = NULL;
	L->data = 0;
	return;
}

void DestroyDLL(DLinkList &L){
	DLNode *p = L;
	if(NULL==p) return;
	while(p!=NULL){
		p = L->next;
		free(L);
		L = p;
	}
}

int DLLLength(DLinkList L){
	int i = 0;
	while(L->next!=NULL){
		i++;
		L = L->next;
	}
	return i;
}

bool InsertNextDLL(DLNode *p,int data){
	if(NULL==p){printf("P is NULL");  return false;}
	DLNode *insert = (DLNode *)malloc(sizeof(DLNode));
	insert->next = p->next;
	insert->prior = p;
	insert->data = data;
	if(p->next!=NULL) p->next->prior = insert;
	p->next = insert;
	return true;
}

bool InsertBackDLL(DLNode *p,int data){
	if(NULL==p || NULL==p->prior) return false;
	DLNode *insert = (DLNode *)malloc(sizeof(DLNode));
	p->prior->next = insert;
	insert->prior = p->prior;
	insert->data = data;
	insert->next = p;
	p->prior = insert;
	return true;
}

bool DeleteDLNode(DLNode *p,int &e){
	if(NULL==p || NULL==p->prior) return false;
	p->prior->next = p->next;
	e = p->data;
	if(p->next!=NULL) p->next->prior = p->prior;
	free(p);
	return true;
}

DLNode* GetDLNode(DLinkList &L,int i){
	DLNode *p = NULL;
	if(i<0) return p;
	p = L;
	while(p!=NULL && i>=1){
		p = p->next;
		i--;
	}
	return p;
}

void HeadInsertDLL(DLinkList &L){
	printf("\nHEAD INSERT\n");
	int data = 0;
	DLNode *p = L;
	while(scanf("%d",&data)) if(9999==data || !InsertNextDLL(p,data)) break;
}

void TailInsertDLL(DLinkList &L){
	printf("\nTAIL INSERT\n");
	int data = 0;
	DLNode *p = L;
	while(scanf("%d",&data)){
		if(9999==data || !InsertNextDLL(p,data)) break;
		p = p->next;
	}
}

bool DLLInsert(DLinkList &L,int i,int data){
	DLNode *p = GetDLNode(L,i-1);
	return InsertNextDLL(p,data);
}

bool DLLDelete(DLinkList &L,int i,int &e){
	DLNode *p = GetDLNode(L,i);
	return DeleteDLNode(p,e);
}

void PrintDLL(DLinkList &L){
	DLNode *p = L->next;
	int i = 1;
	printf("\n");
	while(p!=NULL){
		printf("%d:%d->",i,p->data);
		if(NULL==p->next) break;
		p = p->next;
		i++;
	}
	printf("\n");
	while(p!=NULL){
		printf("%d:%d<-",i,p->data);
		if(p->prior==L) break;
		p = p->prior;
		i--;
	}
	printf("\n");
}
//==========================================================END DoubleLinkList=======================================================

void TestSLL(){
	LinkList L;
	InitLinkList(L);
	HeadInsertLinkList(L);
	PrintLinkList(L);
}

void TestDLL(){
	DLinkList L;
	InitDLL(L);
	HeadInsertDLL(L);
	PrintDLL(L);
	DestroyDLL(L);
	InitDLL(L);
	TailInsertDLL(L);
	PrintDLL(L);
	printf("\nList Length=%d\n",DLLLength(L));
	int signal = 0;
	while(signal!=9999){
		printf("\n0:P 1:I 2:D\n");
		scanf("%d",&signal);
		int i,data,e;
		switch(signal){
			case 0:PrintDLL(L);break;
			case 1:{printf("\nposition=?	data=?\n");
					scanf("%d %d",&i,&data);
					if(DLLInsert(L,i,data)) printf("\nSUCCEED\n");
					break;}
			case 2:{printf("\nposition=?\n");
					scanf("%d",&i);
				   	if(DLLDelete(L,i,e)) printf("\nDELETE %d\n",e);
					break;}
			default:break;
		}
	}
}

void ClearSameElemIn(LinkList &L){
	if(NULL==L) return;
	LNode *p = L->next;
	
}

int main(){
	TestSLL();
	return 0;
}

