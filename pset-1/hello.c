#include <cs50.h>
#include <stdio.h>

int main()
{
  //vai estar na tela ´´Hello, word,indeed!``
  printf("Hello, world,indeed!\n");
  //vai pegar uma string name , usando a pergunta ´´What´s your name?``
  string name = get_string("What's your name? ");
  //finalizando o código usando o que pegou na pergunta em cima
  //e retornando ´´hello, <nome inserido anteriormente>``
  printf("hello, %s\n", name);
}
