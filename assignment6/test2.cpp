#include <iostream>
#include "GenericSet.h"

using namespace std;

int main(){
    Set<double> s1;
    Set<string> s2;
    Set<int> s3;

    s1.Insert(2.234234);
    s2.Insert("Insert");
    s3.Insert(10);

    cout << s1 << s2 << s3 << endl;

    s2.Delete("Insert");
    try{
        s2.Delete("INSERT");
    }
    catch(const char* ex){
        cout << ex <<endl;
    }
    return 0;
}
