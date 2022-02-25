#include <stdio.h>
#include <stdlib.h>

void swapint(int *a, int *b, int *c){

    int arr[3] = {*a,*b,*c};
    int i,j,temp;
    for(i=1;i<3;i++){
        j=i;
        while((j>0) && (arr[j]<arr[j-1])){
            temp = arr[j-1];
            arr[j-1] = arr[j];
            arr[j] = temp;
            j -= 1;
        }
    }
    *a = arr[0];
    *b = arr[1];
    *c = arr[2];

    return;
}


int main()
{
    int a,b,c, i;

    printf("Enter a, b and c respectively: ");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    swapint(&a, &b, &c);

    printf("Value after swapping:\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);

    return 0;
}
