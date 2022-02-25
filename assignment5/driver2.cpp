#include<iostream>
#include"ExtendableArray.h"

using namespace std;

int main(){
    ExtendableArray a1;
    cout << a1 << endl;
    cout<< a1[10000]<<endl;
    a1[10]=10;
    cout << a1[10]<<endl;
    cout << a1 << endl;

    return 0;
}
