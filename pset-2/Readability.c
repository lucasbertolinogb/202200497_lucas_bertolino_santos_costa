#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int contar_texto(string texto);

int main()
{
//Texto do usuário é insirido
    string texto = get_string("Text: ");
    int readability;

    readability = contar_texto(texto);

    if (readability < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readability > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", readability);
    }

    return 0;
}

int contar_texto(string texto)
{
    int letras = 0;
    int palavras = 1;
    int setencas = 0;

//Vai passar por texto do que o usuário colocou
    for (int i = 0 ; i < strlen(texto); i++)
    {
//Checa para ver se é palavra
        if (isalpha(texto[i]))
        {
            letras++;
        }
//Checa para ver se é espaço
        else if (texto[i] == ' ')
        {
            palavras++;
        }
//Checa para ver se é . ? ou !
        else if (texto[i] == '.' || texto[i] == '?' || texto[i] == '!')
        {
            setencas++;
        }
    }
//conta do pset-readability , porém divida em três partes
    float L = (float) letras / (float) palavras * 100;
    float S = (float) setencas / (float) palavras * 100;
//roud é uma função que arredonda para o inteiro mais próximo
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index ;
}
