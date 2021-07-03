#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef struct {
	int data;
	MinStack *top;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
	MinStack *p = (MinStack *)malloc(sizeof(MinStack));
	p->data = NULL;
	p->top = NULL;
	return p;
}

MinStack* findEndNode(MinStack* obj) {
	MinStack *p = obj;
	while(p->top) p = p->top;	
	return p;
}

void minStackPush(MinStack* obj, int x) {
	if(!x) return;
	MinStack *p = findEndNode(obj);
	p->top = minStackCreate();
	p->top->data = x;
}

void minStackPop(MinStack* obj) {
	MinStack *p = findEndNode(obj);
	
}

int minStackTop(MinStack* obj) {

}

int minStackGetMin(MinStack* obj) {

}

void minStackFree(MinStack* obj) {

}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
