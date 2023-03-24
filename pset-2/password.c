// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
//pega a senha do usuário
    if (valid(password))
//usando a valid para ver se a senha é verdadeira nos sequintes parâmentros:
// possui letra minuscula ,mascula ,número e tecla especial
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
//princiapais parâmetros são colocados como false para mudar dentro do for
    bool tem_maisculo = false;
    bool tem_minusculo = false;
    bool tem_digito = false;
    bool tem_simbolo = false;
//uso strlen para pegar uma única string por vez e sigo em diante com i++
    for (int i = 0, len = strlen(password); i < len; i++)
    {
//função booleana que retorna 1 se for letra maiscula
        if (isupper(password[i]))
        {
            tem_maisculo = true;
        }
//função booleana que retorna 1 se for letra minuscula
        else if (islower(password[i]))
        {
            tem_minusculo = true;
        }
//função booleana que retorna 1 se for números
        else if (isdigit(password[i]))
        {
            tem_digito = true;
        }
//função booleana que retorna 1 se for tecla especial
        else if (ispunct(password[i]))
        {
            tem_simbolo = true;
        }
    }
//agora pega todas as funções de cima e se tudo for true ela vai retorna sua resposta como verdaderia
    return tem_maisculo && tem_minusculo && tem_digito && tem_simbolo;
}
