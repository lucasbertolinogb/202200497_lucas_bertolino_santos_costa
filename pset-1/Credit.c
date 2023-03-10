#include <cs50.h>
#include <stdio.h>
#include <math.h>
bool validar_credito(long long numero_credito);
//vai checar se o cartão eh verdadeiro se ele esta em 13,15 ou 15 casas e checar em checksum
bool checksum(long long divi);
//vai checar se a soma esta correta de ex:4012 - 4*2+1*2= 10+0+2= 12/10== 0
int enc_tam(long long y);
//vai identificar o tamanho de casas do cartao
void print_bandeira(long long divi);

//american express : 15 digitos,
int main(void)
{
    long long numero_credito;
    do
    {
        numero_credito = get_long_long("Número do cartão: ");
//vai pegar o nuhmero do cartão
    }
    while (numero_credito < 0);
    if (validar_credito(numero_credito) == true)
    {
        print_bandeira(numero_credito);
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
//vai verificar o cartão e se não passar retorna INVALID
}

bool validar_credito(long long numero_credito)
{
    int tam = enc_tam(numero_credito);
    return (tam == 13 || tam == 15 || tam == 16) && checksum(numero_credito);
//checa o tamanho do cartão usando o enc_tam e verificar se a conta é correspode ao já falado no pset-1
}

int enc_tam(long long y)
{
    int tam;
    for (tam = 0; y != 0; y /= 10, tam++);
    return tam;
//conta a quantidade de casa em credito_cartão e retorna a quantidade
}

bool checksum(long long divi)
{
    int soma = 0, i, digito;
    for (i = 0; divi != 0; i++, divi /= 10)
//vai fazer um laço para contar cada casa em numero_credito
    {
        if (i % 2 == 0)
        {
            soma += divi % 10;
        }
//se for uma casa par ela soma no montante normalmente
        else
        {
            digito = 2 * (divi % 10);
            soma += (digito / 10) + (digito % 10);
//aqui ela pega os impares e multiplica por 2 e soma no montante
        }
    }
    return (soma % 10) == 0;
//nesta parte como eu fiz ela podendo retornar ou true ou false
}

void print_bandeira(long long divi)
{
    if ((divi >= 34e13 && divi < 35e13) || (divi >= 37e13 && divi < 38e13))
    {
        printf("AMEX\n");
    }
    else if (divi >= 51e14 && divi < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((divi >= 4e12 && divi < 5e12) || (divi >= 4e15 && divi < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

//o 34e13 ou 51e14 é uma notacao cientifica de 34x10(elecado a)13
//print_bandeira retorna para qual cartão é cada endereco do cartão e tambem checa se ele é válido
}
