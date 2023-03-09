#include <cs50.h>
#include <stdio.h>
int main()
{
    int y, q, w, esp;
    do
    {
        printf("Height: ");
        scanf("%i", &y);
    }
    while (y < 1 || y > 8);
//faz com que não leia números menores de 1 ou maiores de 8
    for (q = 0 ; q < y; q++)
    {
//começa a contagem da #
        for (esp = 1 ; esp < y - q; esp++)
        {
//conta o número lido anteriormente e coloca um espaço ante do #
//usando a equação ´´esp < y - q``,ou seja, número lido - qual a
            printf(" ");
//contagem do looping inicial
        }
        for (w = 0; w <= q; w++)
        {
//agora começa o looping de colocar #
            printf("#");
        }
//termina o 1º # subida
        printf("  ");
//dois ´´espaços``
        for (w = 0; w <= q; w++)
        {
            printf("#");
//usando o mesmo # agora sem espaço
        }
        printf("\n");
//para cada volta tem ele vai para próxima linha
    }
    return 0;
}
