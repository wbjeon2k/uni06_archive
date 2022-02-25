#include <iostream>
#include "Node.h"

using namespace std;

void print(Node * input){
    cout << input->getWord()<<endl;
    cout << input->getPrev()->getWord()<<endl;
    cout << input->getNext()->getWord()<<endl;
}

int main(){

    Node * test1 = new Node();
    test1->setWord("test1");
    print(test1);
    Node * test2 = new Node("test2");
    print(test2);
    Node * test3 = new Node("test3", test1);
    print(test3);

    test1->setPrev(test2);
    test1->setNext(test3);
    print(test1);

    return 0;
}
