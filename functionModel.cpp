#include <iostream>
#include <string>
#include <array>
#include <vector>
#define SQUARE(X) X*X

using namespace std;

typedef struct LinkNode{
    LinkNode *next;
    int data; 
}*LinkList;

const LinkList &ReturnConstLeftValue(LinkList &L);

template <typename AnyType>
AnyType AddAny(const AnyType x, const AnyType y);

int main(){
    double x;
    cout << "x=?" << endl;
    cin >> x;
    cout << "x^2 = " << SQUARE(x) << endl;
    LinkList L;
    cout << "L->data = " << ReturnConstLeftValue(L)->data << endl;
    return 0;
}

void ShowArray(const int *dataPtr, const int &dataAlia){
    //const int *data refer to an const value, But you can turn data to another const value;
    cout << *dataPtr << endl;
    //const int earth = 0;
    //data = &earth;

}

void EditArray(int const *data){
    //value in data can't be edited,But you can change *data;
    cout << *data << endl;
    *data++;
    cout << *data << endl;
}

const LinkList &ReturnConstLeftValue(LinkList &L){
    L = new LinkNode;
    L->data = 0;
    L->next = nullptr;
    return L;
}

#pragma region Overload

int ShowIt(int x){
    cout << x << endl;
    return x + 1;
}

float ShowIt(float x){
    cout << x << endl;
    return x + 0.1;
}

double ShowIt(double x){
    cout << x << endl;
    return x + 0.01;
}

#pragma endregion Overload

template <typename AnyType>
AnyType AddAny(const AnyType x, const AnyType y){
    return  x + y;
}

template <typename AnyType>
AnyType AddAny(const AnyType x[], const AnyType y[], int n){

}

template <typename AnyType1, typename AnyType2>
auto AddAny(const AnyType1 x, const AnyType2 y) -> decltype(x + y){
    return x + y;
}