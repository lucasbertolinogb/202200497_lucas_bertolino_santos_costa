#include "helpers.h"
#include <math.h>

// Convert image to grayscale
//Função para deixar a foto preto e branco
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //vai passar por todo a imagem
    for (int linha = 0 ;  linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            //aqui é o nome do pixel sendo pixel (para encurtar a minha escrita)
            RGBTRIPLE pixel = image[linha][coluna];
            //vai calcular média entre os pixel Red, Green e Blue
            int mehdia = round((pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen) / 3.0);
            //finalizando com a nova cor preto e branco
            image[linha][coluna].rgbtBlue = image[linha][coluna].rgbtRed = image[linha][coluna].rgbtGreen = mehdia;
        }
    }

    return;
}

// Reflect image horizontally
//Efeito espelho
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //fiz a mesma coisa aqui de pixel sendo pixel
    RGBTRIPLE pixel[height][width];

    //aqui pega os pixel da imagem espelhada
    for (int linha = 0 ;  linha < height; linha++)
    {
        for (int coluna = width - 1, pos_atual = 0; coluna >= 0; coluna--, pos_atual++)
        {
            pixel[linha][pos_atual] = image[linha][coluna];
        }
    }
    //esta parte aqui vai pegar o que eu fiz e retornar o que eu fiz para a image
    //receber sua nova textura
    for (int linha = 0; linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            image[linha][coluna] = pixel[linha][coluna];
        }
    }

    return;
}

//Blur image
//Efeito miopia ou baixa qualidade na imagem
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //aqui vai ser diferente pois o RBGTRIPLE ele é usado duas vezes
    //e como eu tenho dois usos diferente acabei usando dois nomes
    //este aqui é para pegar o pixel de blur
    RGBTRIPLE fam[height][width];

    for (int linha = 0; linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            //aqui começa a brincadeira de passar a pelo bloco e antes de pegar a média
            int contador = 0;
            int linhaContador[3] = {linha - 1, linha, linha + 1};
            int colunaContador[3] = {coluna - 1, coluna, coluna + 1};
            int Vermelho = 0, Azul = 0, Verde = 0;

            //aqui o bloco que eu fiz em cima é usado aqui em baixo
            for (int y = 0; y < 3; y++)
            {
                for (int i = 0; i < 3; i++)
                {
                    int yLinha = linhaContador[y];
                    int yColuna = colunaContador[i];

                    if (yLinha >= 0 && yLinha < height && yColuna >= 0 && yColuna < width)
                    {
                        //outro RGBTRIPLE agora para pegar o pixel
                        RGBTRIPLE pixel = image[yLinha][yColuna];

                        //aqui pegaria os fam´s
                        contador++;
                        Vermelho += pixel.rgbtRed;
                        Verde += pixel.rgbtGreen;
                        Azul += pixel.rgbtBlue;
                    }
                }
            }
            //calculo do blur para embaçar a foto e é aqui que entra a sacada de usar dois RGBTRIPLE
            //pois aqui ele não retornaria normalmente e é preciso ´´força`` a entrada os pixel novos
            fam[linha][coluna].rgbtRed = round(Vermelho / (float)contador);
            fam[linha][coluna].rgbtGreen = round(Verde / (float)contador);
            fam[linha][coluna].rgbtBlue = round(Azul / (float)contador);
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //agora nesta parte eu retorno a nova cor para imagem
            //obs: se tivesse o pixel iria travar o sistema pois ele se começasse dentro da função
            //retornaria a mesma imagem e se for por dentro iria retornar nada
            image[x][y] = fam[x][y];
        }
    }
}

//height: altura (de cima para baixo)
//widht: largura (do lado direito ao esquerdo)
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //contador de rbg da imagem antiga (image) para imagem_velha
    RGBTRIPLE imagem_velha[height][width];
    for (int linha = 0 ;  linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            imagem_velha[linha][coluna] = image[linha][coluna];
        }
    }


    //primeira cor de edges
    int edx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    //segunda cor de edges
    int edy[3][3] =
    {
        {-1, -2, 1},
        {0,   0, 0},
        {1,   2, 1}
    };

    for (int linha = 0 ;  linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            //1º cor de edges edx
            int edxvermelho = 0, edxverde = 0, edxazul = 0;
            //2º cor de edges edy
            int edyvermelho = 0, edyverde = 0, edyazul = 0;

            int mlinha[3]  = {linha - 1, linha, linha + 1};
            int mcoluna[3] = {coluna - 1, coluna, coluna + 1};

            for (int numlinha = 0; numlinha < 3; numlinha++)
            {
                for (int numcoluna = 0; numcoluna < 3; numcoluna++)
                {
                    int nlinha = mlinha[numlinha];
                    int ncoluna = mcoluna[numcoluna];
                    //pegando as cores por pixel
                    RGBTRIPLE pixel = imagem_velha[nlinha][ncoluna];

                    if (numlinha >= 0 && numlinha < height && numcoluna >= 0 && numcoluna < width)
                    {
                        //cor para edx
                        edxvermelho += pixel.rgbtRed * edx[numlinha][numcoluna];
                        edxverde += pixel.rgbtGreen * edx[numlinha][numcoluna];
                        edxazul += pixel.rgbtBlue * edx[numlinha][numcoluna];

                        //cor para edy
                        edyvermelho += pixel.rgbtRed * edy[numlinha][numcoluna];
                        edyverde += pixel.rgbtGreen * edy[numlinha][numcoluna];
                        edyazul += pixel.rgbtBlue * edy[numlinha][numcoluna];
                    }
                }
            }
            //mudando as cores para o edges
            //isso vai pegar o pixel do vermelhe,verde e azul e mudar seu valor
            //para se encaixar no edge, ou seja, dando sua nova textura
            int novoVermelho = round(sqrt(edxvermelho * edxvermelho + edyvermelho * edyvermelho));
            int novoVerde = round(sqrt(edxverde * edxverde + edyverde * edyverde));
            int novoAzul = round(sqrt(edxazul * edxazul + edyazul * edyazul));

            //sequencias de if e else para mudar o valores da image aos obtidas acima

            /*
            image[height][width].rgbtRed = novoVermelho > 255 ? 255 : (novoVermelho < 0 ? 0 : novoVermelho);
            image[height][width].rgbtGreen = novoVerde > 255 ? 255 : (novoVerde < 0 ? 0 : novoVerde);
            image[height][width].rgbtBlue = novoAzul > 255 ? 255 : (novoAzul < 0 ? 0 : novoAzul);
            */


            image[linha][coluna].rgbtRed = novoVermelho > 255 ? 255 : novoVermelho;
            image[linha][coluna].rgbtGreen = novoVerde > 255 ? 255 : novoVerde;
            image[linha][coluna].rgbtBlue = novoAzul > 255 ? 255 : novoAzul;


            /*
            if (novoVermelho > 255)
            {
                image[linha][coluna].rgbtRed = 255;
            }
            else
            {
                image[linha][coluna].rgbtRed = novoVermelho;
            }

            if (novoVerde > 255)
            {
                image[linha][coluna].rgbtGreen = 255;
            }
            else
            {
                image[linha][coluna].rgbtGreen = novoVerde;
            }

            if (novoAzul > 255)
            {
                image[linha][coluna].rgbtBlue = 255;
            }
            else
            {
                image[linha][coluna].rgbtBlue = novoAzul;
            }
            */
        }
    }

    return;
}
