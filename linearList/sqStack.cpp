#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int top;
}SqStack;

typedef struct{
	int data[MaxSize];
	int top1;
	int top2;
}PubSqStack;

/*=========================================================================================================================Sequence Stack=============================================================================================================*/
void InitSqStack(SqStack &S){
	S.top = -1;
	for(int i = 0; i < MaxSize; i++){
		S.data[i] = 0; 
	}
}

void DestroySqStack(SqStack &S){
	InitSqStack(S);
}

bool SqStackEmpty(const SqStack &S){
	return S.top == -1;
}

bool isSqStackFull(SqStack S){
	return S.top == MaxSize - 1;
}

bool Push(SqStack &S, int x){
	if(isSqStackFull(S)){
		printf("SqStack is Full!");
		return false;
	}
	S.data[++S.top] = x;
	return true;
}

bool Pop(SqStack &S, int &e){
	if(SqStackEmpty){
		printf("SqStack is Empty!");
		return false;
	}
	e = S.data[S.top--];
	return true;
}

bool GetTop(SqStack S, int &x){
	if(SqStackEmpty) return false;
	x = S.data[S.top];
	return true;
}
/*=========================================================================================================================Sequence Stack=============================================================================================================*/
void TestSqStack(){
	SqStack S;
	InitSqStack(S);
}

int main(){
	
	return 0;
}
