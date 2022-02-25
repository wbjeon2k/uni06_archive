#include <iostream>
#include "Buffer.h"

using namespace std;

int main(){

    Buffer t1;
    Buffer t2;
    string pass = "pass\n";

    Iterator it;
    t1.print();
    
    cout << "Produce\n";
    t1.produceAtHead("t1");
    t1.produceAtHead("t2");
    cout << "pass\n";
    t1.produceAtTail("t3");
    t1.produceAtTail("t4");
    cout << "pass\n";
    it = t1.getHeadItr();
    it = t1.produceAtMiddle(it, "t5");
    cout << "pass\n";
    //it = t1.getHeadItr();

    t2 = t1;
    t2.print();
    Buffer t3(t1);
    t3.print();

    cout <<"Get\n";
    cout << t1.getHeadElement() << endl;
    cout << t1.getTailElement() << endl;
    
    cout << endl;

    for(int i=0;i<5;i++){
        cout << t1[i] << endl;
    }

    cout << endl;

    t1.consumeAtHead();
    t1.consumeAtTail();
    t1.print();
    t1.consume(t1.getTailItr());
    t1.print();
    cout <<pass;
    t2.consume(t2.getHeadItr(), t2.getTailItr());
    t2.print();

    (findNode(t3.getHeadItr(),t3.getTailItr(),"t3") ==true ? cout <<"T\n" : cout<<"F\n");
    ((t3.isEmpty()==true) ?  cout << "T\n" : cout << "F\n");

    return 0;
}
