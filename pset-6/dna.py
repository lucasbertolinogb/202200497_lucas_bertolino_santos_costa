import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    # checagem de início de entrada do que fazer para usar o
    # programa
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # TODO: Read database file into a variable
    # lendo os arquivos base
    database_dna = open(argv[1])

    # TODO: Read DNA sequence file into a variable
    # lendo a sequência de dna
    arquivo_dna = open(argv[2])

    # TODO: Find longest match of each STR in DNA sequence
    # encontrado a sequencia de dna da database_dna e encontrando este
    # mesmo padrão no csv
    leitor_dna = csv.DictReader(database_dna)
    # aqui ela conta a quantidade de sequencias de str
    sequencia_str = leitor_dna.fieldnames[1:]

    # TODO: Check database for matching profiles
    # vai pegar a sequência para mais para frente do código usa-las
    # para conparar
    dna = arquivo_dna.read()
    arquivo_dna.close()

    # aqui vai pegar as str iqual e armazenar a quantidade de vezes aparecidas
    dna_iqual = {}
    for str in sequencia_str:
        dna_iqual[str] = dna_encontrado(str, dna)

    # vai mostrar de quem é o dna encontrado para cada nome
    for linha in leitor_dna:
        if iqual(sequencia_str, dna_iqual, linha):
            print(linha['name'])
            arquivo_dna.close()
            return

    # caso não tenha ela não aparece nada
    print("No match")
    arquivo_dna.close()


# função para contabilizar os dna encontrados
def dna_encontrado(str, dna):
    y = 0
    while str*(y+1) in dna:
        y += 1
    return y


# vai determinar se a pessoa é iqual ou não
def iqual(sequencia_str, dna_iqual, linha):
    for str in sequencia_str:
        # caso o str seja diferente do encontrado ele retorna false
        if dna_iqual[str] != int(linha[str]):
            return False
    # se passar por tudo e não retornar false , então
    # ele é o que tem o dna correspondente da amostra
    return True


# não usei esta função
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

