#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct LinkNode{
	LinkNode *next;
	double data;
}LinkNode, *LinkStack;

void InitStack(LinkStack &S){
	S = NULL;
}

void DestroyLinkStack(LinkStack &S){

}

bool Push(LinkStack &S, double x){
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	if(!p) return false;
	p->data = x;
	p->next = S;
	S = p;
	//printf("Push x=%f\n",S->data);
	return true;
}

bool Pop(LinkStack &S, double &e){
	if(S == NULL) return false;
	LinkNode *p = S->next;
	e = S->data;
	free(S);
	S = p;
	return true;
}

bool GetTop(LinkStack &S, double &x){
	if(S == NULL) return false;
	x = S->data;

	return true;
}

bool PopFlagStack(LinkStack &operate, LinkStack &flag){
	double leftNum = 0, rightNum = 0, popFlag = 0, result = 0;
	if(Pop(operate,rightNum) && Pop(operate,leftNum) && Pop(flag,popFlag)){
		printf("l = %f %c  r = %f",leftNum,(int)popFlag,rightNum);
		switch((int)popFlag){
			case '+':{result = leftNum + rightNum;break;}
			case '-':{result = leftNum - rightNum;break;}
			case '*':{result = leftNum * rightNum;break;}
			case '/':{result = leftNum / rightNum;break;}
		}
		printf("result=%f\n",result);
		Push(operate,result);
		return true;
	}
	
	return false;
}

int GetFlagPriority(int flag){
	if(flag == '(' || flag == ')')	return -1;
	if(flag == '*' || flag == '/')	return 1;
	if(flag == '+' || flag == '-')	return 0;
	return -2;
}

bool CharToDouble(char *str, int len, double &x){
	double *key = (double *)malloc(sizeof(double)*len);
	if(!key) return false;
	x = 0;
	int counter, buff;
	for(counter = 0; counter  < len && str[counter] != '.'; counter++){
		key[counter] = str[counter] - 48;
	}
	for(int i = counter - 1; i >= 0; i--){
		x = x + pow(10.0,i) * key[counter - 1 -i];
	}
	buff = counter + 1;
	for(int i = buff; i < len; i++){
		key[i] = str[i] - 48;
		x = x + pow(0.1,(i - buff + 1)) * key[i];
	}
	return	true;
}

void ReversePolishNotation(char *exp, LinkStack &operate, LinkStack &flag, int &runCounter){
	runCounter = 0;
	int expLength = strlen(exp), start = 0, numLength = 0;
	double num,flagMark,result;

	for(int i = 0; i < expLength; i++){
		runCounter++;
		if(exp[i] == '('){
			Push(flag,(double)exp[i]);
			start = i + 1;
			ReversePolishNotation(&exp[start],operate,flag,runCounter);
			i = i + runCounter;
		}else if(exp[i] == ')'){

			start = i - numLength;
			CharToDouble(&exp[start],numLength,num);
			Push(operate,num);

			while(flag){
				GetTop(flag,flagMark);
				if(GetFlagPriority(exp[i]) == GetFlagPriority(flagMark)){
					Pop(flag,flagMark);
					return;
				}else{
					PopFlagStack(operate,flag);
				}
			}
		}else if(exp[i] == '*' || exp[i] == '/' || exp[i] == '-' || exp[i] == '+'){
			if(numLength){
			start = i - numLength;
			CharToDouble(&exp[start],numLength,num);
			Push(operate,num);
			numLength = 0;
			}

			while(flag){
				GetTop(flag,flagMark);
				if(GetFlagPriority(exp[i]) > GetFlagPriority(flagMark)){
					break;
				}else{
					PopFlagStack(operate,flag);
				}
			}
			Push(flag,(double)exp[i]);
		}else{
			numLength++;
		}

	}
	start = expLength - numLength;
	CharToDouble(&exp[start],numLength,num);
	Push(operate,num);
	PopFlagStack(operate,flag);

	GetTop(operate,result);
	printf("%f",result);
}

int main(){
	int runCounter = 0;
	char *str = "((8.3+2.3)-2*3/2.7+4)";
	LinkStack flag, operate;
	InitStack(flag);
	InitStack(operate);

	ReversePolishNotation(str,operate,flag,runCounter);
}

