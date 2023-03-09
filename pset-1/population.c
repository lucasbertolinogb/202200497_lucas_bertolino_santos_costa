#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n,end,q=0;

    // TODO: Prompt for start size
     do
     {
        printf("Start size: "); scanf("%i",&n);
     }while (n < 9);

    // TODO: Prompt for end size
    do
    {
      printf("End size: "); scanf("%i \n",&end);
    }while(n > end);

    // TODO: Calculate number of years until we reach threshold
    do
    {
        n= n +(n/3) - (n/4);
        q++;
    }
    while(n<end);

    // TODO: Print number of years
    printf("Years: %i \n",q);

    return 0;
}
