#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Mlen 256
//https://stackoverflow.com/questions/5375604/reading-in-a-string-of-unknown-length-from-the-console
//https://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
//http://www.cplusplus.com/reference/cstring/strtok/

void rmvstr(char* str1, char*str2, char* str4){
    int cnt=0;
    char *tmpstr;
    if(strlen(str2)>strlen(str1)){
        strcpy(str4,str1);
        return;// str4;
    }
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    int i=0;

    tmpstr = strtok(str1," ");

    while(tmpstr != NULL){
        //printf("%s\n", tmpstr);
        //printstatus(tmpstr);
        if(strcmp(str2,tmpstr)){
           // printf("pass\n");
            if(cnt==0){
                strcpy(str4,tmpstr);
                
            }
            else{
                strcat(str4,tmpstr);
             
            }
            strcat(str4," ");
            cnt++;
        }
        
        tmpstr = strtok(NULL, " ");

    }
    return; //str4;
}

char* Strrev(char *str)
{
      int i=0,j=0;
      char* start = str;
      char* end = str + strlen(str)-1;

      if (str== NULL || *str == NULL )
            return str;
      while(start<end){
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
      }
      return str;
}

void printstatus(char*str){
    int i;
    printf("str length %d\n", strlen(str));
    for(i=0;i<=strlen(str);++i){
        printf("%d %c\n", str[i], str[i]);
    }
}

int main()
{
    int i,n;
    char str1[Mlen];
    char str2[Mlen];

    char str3[Mlen];
    char str4[Mlen];
    char* str5;

    printf("Enter a sentence: ");

    gets(str1);

    printf("Enter string: ");

    gets(str2);

    strcat(str1,str2);
    printf("After: %s\n", str1);

    printf("Enter string: ");

    gets(str3);

    rmvstr(str1,str3,str4);
    printf("After: %s\n", str4);

    //printstatus(str4);
    //strcpy(str5,str4);
    Strrev(str4);
    printf("After: %s\n", str4);
    return 0;


}
