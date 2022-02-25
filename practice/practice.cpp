#include<iostream>

using namespace std;

class ClassA{

    public:
        ClassA(){
            cout << "call constructor\n";
        }
        ~ClassA(){
            cout << "call destructor\n";
        }
};

class ClassB{
    private:
        int *ptr;
        ClassA varA;
    public:
        ClassB(int value=0){
            ptr = new int;
            *ptr =value;
        }
        void printc(){
            cout << *ptr << endl;
        }
};

int main(){

    ClassB c1(100);
    ClassB c2;
    
    c1.printc();
    c2.printc();
    return 0;
}
