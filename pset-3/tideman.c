#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
//conta se os cadidatos são iquais no início do programa
//se sim ele vai se colocado em ranks
    for (int i = 0 ; i < candidate_count ; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
//Vai contar preference[i][] primeira casa
    for (int i = 0 ; i < candidate_count ; i++)
    {
//Vai contar preference[][j] segunda casa
        for (int j = i + 1 ; j < candidate_count ; j++)
        {
            //preferencia de j sobre i
            if (ranks[i] < ranks[j])
            {
                preferences[j][j]++;
            }
            //preferencia de i sobre j
            else if (ranks[i] > ranks[j])
            {
                preferences[i][j]++;
            }
        }
    }

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
// Mesma coisa que record_preferences , porém agora é contar se um par
// é maior do que o outro
    int pair = 0;
    for (int i = 0 ; i <= candidate_count ; i++)
    {
        for (int j = 0 ; j <= candidate_count ; j++)
        {
            //Identificar se o par ij é maior que ji
            if (preferences[i][j] > preferences[j][i])
            {
                //se sim então i é vencedor e j perdedor
                pairs[pair].winner = i;
                pairs[pair].loser = j;
                pair_count++;
                //vai colocar em outro espaço do pairs
                pair++;
            }

        }
    }

}

//faz o que o pset-3 chama de força da vitória sobre o perdedor 
int compara(const void *ordem1, const void *ordem2)
{
    pair v = *((pair *) ordem1);
    pair g = *((pair *) ordem2);
    int pri = preferences[v.winner][v.loser] - preferences[v.loser][v.winner];
    int seg = preferences[g.winner][g.loser] - preferences[g.loser][g.winner];
    return seg - pri;

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //função que ordena de forma decrescente 
    qsort(pairs, pair_count, sizeof(pair), compara);

}

bool tem_ciclo_sim(int index, bool visto[])
{
    //parte para caso ele já tenha sido checado ele sai da função
    if (visto[index])
    {
        return true;
        
    }
    visto[index] = true;
    //Aqui começa a checagem dos ciclos
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[index][i] && tem_ciclo_sim(i, visto))
        {
            return true;
        }

    }
    return false;
}

//usando a função tem_ciclo_sim nesta função
bool tem_ciclo(int pri_index)
{
    bool visto[candidate_count];
    //vai deixar todas as funções ´´zeradas`` para entrar em tem_ciclo_sim
    for (int i = 0 ; i < candidate_count; i++)
    {
        visto[i] = false;
    }
    //vai retornar se tiver um ciclo ou não 
    return tem_ciclo_sim(pri_index, visto);
}

// Lock pairs into the candidate graph in order, without creating cycles
//Essa daqui vai travar os caminhos do ciclo feito em tem_ciclo
//Obs: tem erro nessa função de não setar a preferência no 1º voto
//ou seja, não checa todos as preferências
void lock_pairs(void)
{
    // TODO
    for (int i = 0 ; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        //caso tenha preferência de i para j vai retornar true e fechando um ciclo
        if (tem_ciclo(i))
        {
            //essa parte pode tirar esse fechamento do ciclo 
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

}

//Verifica se tem um ciclo entre os candidatos 
bool tem_rec(int index)
{
    for (int i = 0 ; i < candidate_count; i++)
    {
        //caso ele tenha um ciclo retorna false
        if (locked[i][index])
        {
            return false;
        }
    }
    //se não tiver ele retorna true
    return true;
}

//pegador de candidato vencedor imediato no 1º turno (PCVI1)
int pega_rec()
{
    for (int i = 0 ; i < candidate_count; i++)
    {
        //caso ele vença no nº turno ele retorna como 1 e passa como ganhador
        if (tem_rec(i))
        {
            return i;
        }
    }
    //caso não passe ele fica de fora
    return -1;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    int index = pega_rec();
    //agora os resultados da eleição 
    if (index != -1)
    {
        printf("%s\n", candidates[index]);
    }

}
