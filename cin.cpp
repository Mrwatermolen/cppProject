#include <iostream>
#include <string>
using namespace std;
int main(){
    /*string name,dessert;
    cout << "Your Name" << endl;
    cin >> name;
    cout << "Hello\t" << name << endl;
    getline(cin,dessert);
    cout << "Dessert\t" << dessert << endl;
    if(dessert == ""){
        getline(cin,dessert);
        cout << "Dessert\t" << dessert << endl;
    }*/
    //Cin Test
    int a;//Try to input abc123 or 123abc
    cin >> a;
    cout << a << endl;
    while(!cin){
        //There are "abc" in buffInput.
        cout << "cin.clear() start!\n";
        cin.clear();//cin.clear can't clear buffInput. It resets cin status.
        cout << "cin.clear() finish!\n";
        //while(cin.get() != '\n')
        //    continue;
        cin >> a;
        cout << a << endl;
        
    }
    return 0;
}