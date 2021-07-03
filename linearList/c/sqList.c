#include <stdio.h>
#include <stdlib.h>
#define InitSize 10

typedef struct{
	int *data;
	int MaxSize;
	int length;
	int scrape;
}SqList;

void InitSqList(SqList &L){
	L.data = (int *)malloc(sizeof(int)*InitSize);
	L.MaxSize = InitSize;
	L.length = 0;
}

void DestroySqList(SqList &L){
		L.length = 0;
		L.MaxSize = 0;
		free(L.data);
}

void ExpandList(SqList &L){
	int size = L.MaxSize + InitSize;
	int *p = L.data;
	L.data = (int *)malloc(sizeof(int)*size);
	for(int i=0; i<L.MaxSize; i++){
		L.data[i] = p[i];
		L.data[L.MaxSize+i] = 0;
	}
	free(p);
}

bool CheckInput(SqList L,int i){
	if(i<1 || i>L.length){
		printf("\nILICIT INPUT!\n");
		return true;
	}
		return false;
}

bool IsAvail(SqList &L){
    if(L.length>=L.MaxSize)	return false;
	return true;
}

int GetElem(SqList &L,int i){
	if(CheckInput(L,i)) return 0;
	return (L.data[i-1]);
}

int LocateElem(SqList &L,int data){
	int i = 0;
	bool find = false;
	for(;i<L.length;i++){
		if(data==L.data[i]){
			find = true;
			break;
		}
	}
	if(!find) i=-1;
	return (i+1);
}

void AppendElem(SqList &L,int data){
	if(!IsAvail(L)) ExpandList(L);

	L.data[L.length] = data;
	L.length++;
}

void InsertElem(SqList &L,int data,int p){
	if(CheckInput(L,p)) return ;
	if(!IsAvail(L)) ExpandList(L);

	for(int i=L.length; i>=p && p>0; i--){
		L.data[i] = L.data[i-1];
	}	
	L.data[p-1] = data;	
	L.length++;

}

void DeleteElem(SqList &L,int i,int &e){
	if(CheckInput(L,i)) return;
	e = L.data[i-1];
	for(int j=L.length; i<j; i++){
		L.data[i-1] = L.data[i];
	}
	L.length--;
}

void PrintSqList(SqList &L){
	for(int i=0; i<L.length; i++){
		printf("SqList[%d]=%d\n",i,L.data[i]);
	}
}

int main(){
	SqList L;
	InitSqList(L);
	for(int i=0; i<L.MaxSize; i++){
		AppendElem(L,InitSize-i);
	}
	printf("l=%d\n",L.length);
	PrintSqList(L);

	int signal = 0;
	while(signal != 9999){
		printf("\n	0:Print	1:Append 2:Insert 3:Delete 4:GetElem 5:LocateElem\n");
		while(!(scanf("%d",&signal)));
		switch(signal){
				case 0:PrintSqList(L);break;
				case 1:{
					 int data;
					printf("\nTo Append data=? \n");
					scanf("%d",&data);
					AppendElem(L,data);
					break;}
				case 2:{
					int data,p;
					printf("\n data=?  \t position=? \n");
					scanf("%d %d",&data,&p);
					InsertElem(L,data,p);
					break;}
				case 3:{
		      		int dp,e;
					printf("\n position \n");
					scanf("%d",&dp);
					DeleteElem(L,dp,e);
					printf("DELETE %d\n",e);
					break;}
				case 4:{
					int i;
					printf("\nGetElem i=?\n");
					scanf("%d",&i);
					int data = GetElem(L,i);
					printf("\n[%d]=%d\n",i,data);
					break;}
				case 5:{
					int data;
					printf("\nLocate data=?\n");
					scanf("%d",&data);
					int i = LocateElem(L,data);
					printf("\n%d locates in %d\n",data,i);
					   }
				default:break;
		}
	}
	return 0;
}
