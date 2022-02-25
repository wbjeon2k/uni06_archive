#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main(){
    
    int n;
    char c;
    int cnt=0;
    while(true){
        scanf("%s",&c);
        if(c==''){
            cout << "end" << endl;
            cout << cnt << endl;
            cnt ++;
            break;
        }
    }

    return 0;
}
