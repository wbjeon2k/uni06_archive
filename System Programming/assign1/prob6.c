#include <stdio.h>
#include <stdlib.h>
#define Mlen 10000

struct personnel{
    char* name;
    int score;
};

typedef struct personnel P;

int main()
{
    int n,i;

    P* Parr;
    printf("Enter number of records: ");
    scanf("%d", &n);
    Parr = (P*)malloc(sizeof(P)*n);

    for(i=0;i<n;++i){
        (Parr[i]).name = (char*)malloc(Mlen);
    }

    for(i=0;i<n;++i){
        scanf("%s", Parr[i].name);
        scanf("%d", &(Parr[i]).score);
    }

    printf("Displaying information:\n");

    for(i=0;i<n;++i){
        printf("%s", (Parr[i].name));
        printf("     ");
        printf("%d\n", (Parr[i].score));
    }

    return 0;
}
