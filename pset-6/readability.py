# TODO
def contar_texto(texto):
    # setando as variáveis
    letras = 0
    palavras = 1
    setencas = 0

    # vai passar por cada letra da frase
    for tam in texto:
        # se for uma palavra do alfabeto ela passa
        if tam.isalpha():
            letras += 1
        # se for um espaço ela passa como uma palavra
        elif tam == ' ':
            palavras += 1
        # caso seja . ? ! ela passa como uma setença
        elif tam == '.' or tam == '?' or tam == '!':
            setencas += 1
    # Calculo  das variáveis L e S
    L = letras / palavras * 100
    S = setencas / palavras * 100

    # Calculo do index da questão
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


# vai inserir seu texto na variável texto
texto = input("Text: ")
# analise do texto
readability = contar_texto(texto)

# pontuação do texto
if readability < 1:
    print("Before Grade 1")
elif readability > 16:
    print("Grade 16+")
else:
    print(f"Grade {readability}")
