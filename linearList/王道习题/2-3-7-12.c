#include <stdio.h>
#include <stdlib.h>
#include '../sLinkList.c'

LNode* SliptLinkList(LinkList &L){
	if(NULL==L) return NULL;
	LinkList A;
	InitLinkList(A);
	LNode *p = L,*d = A,*s = L;
	int i = 1;
	while(p->next!=NULL){
		if(0==i%2){
			d->next = p->next;
			d = d->next;
		}
		else{
			s->next = p->next;
			s = s->next;
		}
		i++;
		p = p->next;
	}
	d->next = NULL;
	s->next = NULL;
	return A;
}
void T_SliptLinkList(){
	LinkList L,A;
	InitLinkList(L);
	TailInsertLinkList(L);
	A = SliptLinkList(L);
	PrintLinkList(A);
	PrintLinkList(L);
	DestroyLinkList(A);
	DestroyLinkList(L);
}

int main(){
	T_SliptLinkList();
	return 0;
}
