#include <stdio.h>
#include <limits.h>


int main(){

    int x= 0;
    int y = INT_MAX;
    
    unsigned ux  = (unsigned) x;
    unsigned uy = (unsigned) y;

    printf("%d %d\n", x, y);

    //printf("%d\n", ~x + ~y +1);
    //printf("%d\n", ~(x+y));

    printf("%u\n",ux-uy);
    printf("%u\n",-(unsigned)(y-x));
    return 0;
}
