// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1009;

// Hash table
node *table[N];

unsigned contador_mundial;
unsigned tamanho;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //usando o hash para (palavra)checar se (int)checar esta correto
    int checar = hash(word);

    //percorrendo a lista se a word esta correta
    for (node *node_checa = table[checar]; node_checa != NULL; node_checa = node_checa -> next)
    {
        //strcasecmp é uma função de comparação
        //nesta parte eu tento checar se word esta nos paramâmetros
        //do pset e caso seja verdadeiro ele retorna 0 (true) ou
        //1 (false)
        if (strcasecmp(node_checa -> word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    //dispersão simples usando apenas 1 palavra 
    for (int y = 0, letra = strlen(word); y < letra; y++)
    {
        hash = (hash * 47) + tolower(word[y]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //abrindo o dicionário
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    //fazendo o dicionário começando com null
    for (int y = 0 ; y < N; y++)
    {
        table[y] = NULL;
    }

    //estabelecendo quem vai receber as palavras
    char word[LENGTH + 1];

    //lendo o arquivo do dicionário linha por linha
    while (fscanf(file, "%s", word) != EOF)
    {
        //criando um novo nó e armazena a palavra nele
        node *novo_node = malloc(sizeof(node));
        //caso não encontre nenhuma palavra a função automaticamente é fechado e
        //retorna NULL
        if (novo_node == NULL)
        {
            fclose(file);
            return false;
        }

        //o 1º word é usado para passar a palavra lida
        //o 2º word é o nome da variável dentro da estrutura de node
        strcpy(novo_node -> word, word);
        //usando hash para determinar a tamanho da palavra lida
        tamanho = hash(word);
        //juntando as palavras por sua palavra
        //tipo b: boneca, baralho e c:carro, créditos e etc.
        novo_node -> next = table[tamanho];
        table[tamanho] = novo_node;
        contador_mundial++;
    }

    fclose(file);
    return true;
}

//função para checar dentro de unload
bool is_loaded(const char *dictionary)
{
    return load(dictionary);
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //retorno do tamanho das palavras
    if (contador_mundial > 0)
    {
        return contador_mundial;
    }
    return 0;

    //inicioalizo o contador para passar na função abaixo
    //e estou forçando ela a sempre retorna um valor positivo e
    //não um valor positivo
    int contador = 0;
    //percorre todas as palavras
    for (int y = 0; y < N; y++)
    {
        //percorre a lista correspondente ao apontar se a palavra esta certa ou não
        node *apontar = table[y];
        //caso ela ela esteja em table ela passa na função
        while (apontar != NULL)
        {
            contador++;
            apontar = apontar -> next;
        }

    }
    //retorna o tamanho da palavra
    return contador;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //vai percorrer a tabela e liberar memória
    for (int y = 0; y < N; y++)
    {
        //usadno apontar para liberar a memória dentro de table
        node *apontar = table[y];
        //vai ficar no loop até acabar de passar por todos os nós na memória
        while (apontar != NULL)
        {
            //nesta parte eu pego agora a parte de memória com limpar
            node *limpar = apontar;
            //e passo o apontar para a proxima apontar
            apontar = apontar -> next;
            //pego o 1ºapontar e libero dele na memória
            free(limpar);
        }

    }
    return true;
}
