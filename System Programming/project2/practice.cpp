#include <iostream>

using namespace std;

int func(int a, int b, unsigned int c){
    int d;
    d = (c-b)/2 + b;
    if(d <= a){
        if(d<a){
            d += func(a, d+1, c);
        }
    }
    else{
        d += func(a,b,c-1);
    }
    return d;
}


int main(){
    unsigned t =0;
    while(1){
        if (t>14) break;

        int chk=0;
        chk = func(t,0,14);
        if(chk==43){
            printf("%u\n", t);
            break;
        }
        t += 1;
    }

}


