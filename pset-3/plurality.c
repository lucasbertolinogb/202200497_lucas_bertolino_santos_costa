#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Contagem dos votos
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Checa para nomes inválidos
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

// Ganhador da eleição é :
    print_winner();
}

// Aumenta o voto para cada candidato
bool vote(string name)
{
// Loop para cada nome que entra na função
    for (int y = 0; y < candidate_count; y++)
    {
//Se o nome for iqual vai retornar true e acrescentar mais 1 em vote
        if (strcmp(name, candidates[y].name) == 0)
        {
            candidates[y].votes++;
            return true;
        }
    }
//Caso não seja iqual ela retorna nada
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
//maior_caditado vai servir como testador de maior voto
//por cadidato e -1 para garantir que vai pegar ao menos 1
    int maior_candidato = -1;
    for (int i = 0; i < candidate_count ; i++)
    {
        if (candidates[i].votes > maior_candidato)
        {
            maior_candidato = candidates[i].votes;
        }
    }
//outro loop agora para checar os nomes são iqual o maior_cadidato
//caso seja iqual retorne o nome
    for (int i = 0; i < candidate_count ; i++)
    {
        if (candidates[i].votes == maior_candidato)
        {
            printf("%s\n", candidates[i].name);
        }
    }

}
