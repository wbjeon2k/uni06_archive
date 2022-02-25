#include <iostream>
//#include "Iterator.h"
#include "Buffer.h"

using namespace std;

void print(Iterator iter){
    cout << iter.getCurr()->getWord()<<endl;
}

int main(){
    Buffer b1;
    Iterator iter;

    b1.produceAtHead("t1");
    b1.produceAtHead("t2");
    b1.produceAtHead("t3");
    b1.produceAtHead("t4");
    b1.produceAtHead("t5");

    iter = b1.getHeadItr();
    print(iter);
    print(++iter);
    print(--iter);
    cout << endl;
    iter++;
    print(iter);
    iter--;
    print(iter);
    cout <<endl;
    iter+=4;
    print(iter);
    iter-=4;
    print(iter);
    cout <<endl;
    
    for(int i=0;i<5;i++){
        print(iter+i);
    }
    cout << endl;
    for(int i=0;i<5;i++){
        print(iter-i);
    }
    (iter == iter+1 ? cout << "T\n" : cout << "F\n");
    (iter != iter+1 ? cout << "T\n" : cout << "F\n");

    return 0;

}
