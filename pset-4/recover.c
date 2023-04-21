#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define tam_bloco 512


typedef uint8_t BYTE;

//função para checar a entrada do usuário esta correta
void checar(int argc);
//checa se a imagem foi aberta corretamenta ou não
void checaArquivo(FILE *file);
int verdadeJPEG(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //checa a entrada da imagem
    checar(argc);

    FILE *f = fopen(argv[1], "r");
    //FILE *f = fopen(filename, "r");
    //checa se a imagem abriu corretamente
    checaArquivo(f);

    //vou usar o buffer para passar pelo código da imagem
    //poderia ser qualquer nome
    BYTE buffer[tam_bloco];

    char nameArquivo[8];
    FILE *imagem;
    int counter = 0;

    //aqui vai ser lido os bloco de hexa da imagem e enquanto ela não terminar a
    //função vai continuar
    while (fread(buffer, tam_bloco, 1, f) == 1)
    {
        //checa se o cabeçalho é verdadeiro , fechando o arquivo atual se tiver
        if (verdadeJPEG(buffer) == 1)
        {
            if (counter != 0)
            {
                fclose(imagem);
            }
            //cria o novo nome dos arquivos
            sprintf(nameArquivo, "%03i.jpg", counter++);
            imagem = fopen(nameArquivo, "w");
            //caso já tenha um arquivo aberto ele irá gravar o conteúdo
            //do buffer por cima do arquivo
            fwrite(buffer, tam_bloco, 1, imagem);
        }
        else if (counter > 0)
        {
            fwrite(buffer, tam_bloco, 1, imagem);
        }
    }

    return 0;
}

void checar(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        //diferente do return esta aqui termina o código e não ´´contamina´´
        //os outros códigos
        exit(1);
    }
}

void checaArquivo(FILE *file)
{
    //caso ela seja NULL, ou seja, não abre ele acaba com
    //o código
    if (file == NULL)
    {
        printf("File could not be opened.\n");
        exit(1);
    }
}

int verdadeJPEG(BYTE buffer[])
{
    //if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 )
    //simplificada no bites do buffer com a função memcmp
    //que compara os primeros quatros bytes e se ele forem iqual o que estão em \\
    //ele retorna 0 (true) do contrário 1 (false)
    if (memcmp(buffer, "\xff\xd8\xff\xe0", 4) == 0 && (buffer[3] & 0xf0) == 0xe0)
    {
        //diferente do exit anteriormente nesta parte eu quero que o código
        //continue sem parar ele
        return 1;
    }
    return 0;
}
