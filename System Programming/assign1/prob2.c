#include <stdio.h>
#include <stdlib.h>
#define M -2,147,483,647

int main()
{
    int N,i, max;
    int * arr;

    printf("Enter total number of elements: ");
    scanf("%d", &N);
    printf("\n");
    arr = (int *)malloc(sizeof(int)*N);
    for(i=0;i<N;++i){
        printf("Enter Number %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    max = M;
    for(i=0;i<N;++i){
        if(arr[i]>max){
            max = arr[i];
        }
    }
    printf("Largest element: %d", max);
    free(arr);
    return 0;
}
