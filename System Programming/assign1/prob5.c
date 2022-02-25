#include <stdio.h>
#include <stdlib.h>

struct metric{
    int centimeter;
    float meter;
};

typedef struct metric M;

int main()
{
    M m1, m2;
    int scenti;
    float smeter;

    printf("Enter information for 1st distance\n");
    printf("Enter cm: ");
    scanf("%d", &m1.centimeter);
    printf("Enter meter: ");
    scanf("%f", &m1.meter);

    printf("Enter information for 2st distance\n");
    printf("Enter cm: ");
    scanf("%d", &m2.centimeter);
    printf("Enter meter: ");
    scanf("%f", &m2.meter);

    scenti = m1.centimeter + m2.centimeter;
    smeter = m2.meter + m1.meter;

    printf("Sum of distances = %d-%5.2f\n",scenti,smeter);


    return 0;

}
