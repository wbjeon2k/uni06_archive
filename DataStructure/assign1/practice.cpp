#include <iostream>
#include "CircularList.h"


using namespace std;

int main(){
    CircularList<int> list1;
    int n;
    scanf("%d", &n);

    for(int i=0;i<n;++i){
        int tmp;
        cin >> tmp;
        list1.add(tmp);
        printf("%d\n", list1.front());
    }

    list1.printlist();

    list1.reverse();

    list1.printlist();
    

    return 0;
}
