// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //uint8_t garante que serão valores inteiros positivos, sendo de 8 bits
    uint8_t header[HEADER_SIZE];
    //fread como o nome diz ele vai ler do HEADER_SIZE
    //apartir do imput e no final armazenando em header
    fread(header, HEADER_SIZE, 1, input);
    //fwrite como o nome diz ele vai escrever , usando o header para ser
    //usado de tamanho HEADER_SIZE no arquivo output
    fwrite(header, HEADER_SIZE, 1, output);

    //parecido com int8_t ,porém de 16 bits
    int16_t buffer;

    // TODO: Read samples from input file and write updated data to output file
    //loop de ler dados e muda o input para outro valor de saida(output)
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
