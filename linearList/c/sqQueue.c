#include <stdio.h>
#include <stdlib.h>
#define MaixSize 10

typedef struct{
	int data[MaixSize];
	int font,rear;
}SqQueue;

void InitSqQueue(SqQueue &Q){
	//font指向当前元素，rear指向下一个
	Q.font = 0;
	Q.rear = 0;
}

void DestroySqQueue(SqQueue &Q){
	
}

bool SqQueueEmpty(SqQueue Q){
	if(Q.rear == Q.font) return true;
	return false;
}

bool SqQueueFull(SqQueue Q){
	if((Q.rear + 1)%MaixSize == Q.font) return true;//Loss one space by this way
	return false;
}

bool EnSqQueue(SqQueue &Q, int x){
	if(SqQueueFull) return false;
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1)%MaixSize;
	return true;
}

bool DeSqQueue(SqQueue &Q, int &e){
	if(SqQueueEmpty) return false;
	e = Q.data[Q.font];
	Q.font = (Q.font + 1)%MaixSize;
	return true;
}

bool GetHead(SqQueue &Q, int &x){
	if(SqQueueEmpty) return false;
	x = Q.data[Q.font];
	return true;
}

int main(){
	return 0;
}
