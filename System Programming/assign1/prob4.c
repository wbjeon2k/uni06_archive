#include <stdio.h>
#include <stdlib.h>

int main()
{
        char str[10000];
        printf("Enter sentence: ");
            FILE * fp = fopen("hello.txt", "wt");
            gets(str);
            fputs(str, fp); return 0;
}
