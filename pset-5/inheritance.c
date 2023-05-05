// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    //usando a estrutura de person criei uma instância nova_pessoa
    //para usar-las na criação das pessoas
    //obs: (person*) pode ser retirado ,tendo a função de me
    //lembrar que esta sendo apontado de person para nova_pessoa
    person *nova_pessoa = (person *) malloc(sizeof(person));
    //person *nova_pessoa = malloc(sizeof(person));


    // If there are still generations left to create
    //aqui vai criar os descendentes com 1 alelo dos pais e um aleatório
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        // TODO: Set parent pointers for current person
        //usando a nova_pessoa que vai criar os pais da geração
        nova_pessoa -> parents[0] = create_family(generations - 1);
        nova_pessoa -> parents[1] = create_family(generations - 1);




        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        //usando a nova_pessoa e randomizando os seus alelos
        nova_pessoa->alleles[0] = nova_pessoa->parents[0]->alleles[rand() % 2];
        nova_pessoa->alleles[1] = nova_pessoa->parents[1]->alleles[rand() % 2];

    }

    // If there are no generations left to create
    //em português, se essa for a 0º geração ela vai ser aleatória
    else
    {
        // TODO: Set parent pointers to NULL
        //Vai deixar como sendo os ancestrais da família
        nova_pessoa -> parents[0] = NULL;
        nova_pessoa -> parents[1] = NULL;

        // TODO: Randomly assign alleles
        //geração aleatória dos dois alelos
        nova_pessoa->alleles[0] = random_allele();
        nova_pessoa->alleles[1] = random_allele();

    }

    // TODO: Return newly created person
    //vai retornar a nova_pessoa criada
    return nova_pessoa;
}

// Free `p` and all ancestors of `p`.
//mudei o p para o ponteiro de nova_pessoa
void free_family(person *nova_pessoa)
{
    // TODO: Handle base case
    //caso a nova_pessoa esteja vazia ela já não entre no resto da função
    //tipo uma barreira para não passar o que já passou
    if (nova_pessoa == NULL)
    {
        return;
    }
    // TODO: Free parents recursively
    //parte onde eu limpo as memórias dos pais de nova_pessoa
    free_family(nova_pessoa->parents[0]);
    free_family(nova_pessoa->parents[1]);
    // TODO: Free child
    //e logicamente faltaria limpar a parte do filho 
    free(nova_pessoa);

}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
