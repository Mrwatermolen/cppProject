#include <iostream>
#include <cstring>

int rigth(char s){
	if(s=='(') return ')';
	if(s=='[') return ']';
	if(s=='{') return '}';
	return 0;
}

bool isValid(char *s){
	int len = strlen(s);
	if(len%2==1) return false;
	int top = 0,i = 0;
	char *stack = new char [len];
	while(len){
		char tmp = rigth(s[i]);
		if(tmp){
			stack[top] = tmp;
			top++;
		}else if(top>0 && s[i] == stack[top-1]){
			top--;
		}else{
			return false;
		}
		i++;
		len--;
	}
	return (top==0);
}

int main(){
	char *s = new char [100];
	std::cin.getline(s,100);
	std::cout << isValid(s);
}
