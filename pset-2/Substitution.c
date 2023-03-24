#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
//Vai gerrar a mensagem na tela
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];
//Vai checar se a chave que você colocou é valida
    for (int i = 0 ; i < strlen(key); i++)
    {
//Caso for diferente a função é fechada
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
//Vai ver se a chave é diferente de 26 caracteres
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
//Vai checar se a palavra é iqual ou não a próxima palavra
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
//Agora ele vai pegar sua frase normal
    string texto_muda = get_string("plaintext: ");

//Vai colocar a sua chave sempre maiúscula
    for (int i = 0; i < strlen(key); i++)
    {
        if (islower(key[i]))
        {
            key[i] = key[i] - 32;
        }
    }

    printf("ciphertext: ");
//função onde vai trocar as palavras pela sua chave
    for (int i = 0; i < strlen(texto_muda); i++)
    {
//muda caractere maiúcula
        if (isupper(texto_muda[i]))
        {
            int letra = texto_muda[i] - 65;
            printf("%c", key[letra]);
        }
//muda caractere minuscula
        else if (islower(texto_muda[i]))
        {
            int letra = texto_muda[i] - 97;
            printf("%c", key[letra] + 32);
        }
//o que for diferente de uma letra ela é usado sem alteração
        else
        {
            printf("%c", texto_muda[i]);
        }
    }
    printf("\n");

}
