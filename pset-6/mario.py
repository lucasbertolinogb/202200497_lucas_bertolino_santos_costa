# TODO

# enquanto numero não for um int ele vai retornar
# até ficar True com a função isdigit()
while True:
    entrada = input("Height: ")
    if entrada.isdigit():
        numero = int(entrada)
        if 1 <= numero <= 8:
            break

# contamento da escadaria
for contar in range(1, numero + 1):
    # espaçamento inicial
    for contar_ini in range(numero - contar):
        print(" ", end="")
    # subida
    for contar_tag in range(contar):
        print("#", end="")
    # espaço entre os #
    print("  ", end="")
    # descida
    for contar_tag in range(contar):
        print("#", end="")
    print("")
