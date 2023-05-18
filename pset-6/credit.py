# TODO
# vai fazer conta do credit em phython
def checksum(divi):
    i = 0
    soma = 0
    # o loop vai continuar até que divi não seja iqual a zero
    while divi != 0:
        if i % 2 == 0:
            # vai fazer a primeria parte da soma
            soma += divi % 10
        else:
            # vai fazer a segunda parte da soma
            digito = 2 * (divi % 10)
            soma += (digito // 10) + (digito % 10)
        # vai passar por todos as casas
        i += 1
        divi //= 10
    return soma % 10 == 0


# ja vai medir o tamanho e validar o tamanho da quantidade
# de casas do cartão
def validar_credito(numero_credito):
    tam = len(str(numero_credito))
    return (tam == 13 or tam == 15 or tam == 16) and checksum(numero_credito)


# vai determinar qual a bandeira do cartão
def print_bandeira(divi):
    # bandeira AMEX
    if (divi >= 34e13 and divi < 35e13) or (divi >= 37e13 and divi < 38e13):
        print("AMEX\n")
    # bandeira MASTERCARD
    elif (divi >= 51e14 and divi < 56e14):
        print("MASTERCARD\n")
    # bandeira VISA
    elif (divi >= 4e12 and divi < 5e12) or (divi >= 4e15 and divi < 5e15):
        print("VISA\n")
    # caso não seja nenhuma delas irá sair como inválida
    else:
        print("INVALID\n")


# tratamento de excessão
try:
    numero_credito = None
    while True:
        # pega o número do cartão
        numero_credito = int(input("Número do cartão: "))
        # caso seja maior que zero ela sai do while
        if numero_credito >= 0:
            break
    # aqui vai validar e caso tenha uma banderia correspondente
    # ira mostrar o nome dela
    if validar_credito(numero_credito):
        print_bandeira(numero_credito)
    # caso não tenha correspondente irá retornar inválida
    else:
        printf("INVALID\n")
# caso o código não
except Exception as e:
    print("INVALID")
