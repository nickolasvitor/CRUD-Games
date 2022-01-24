#include <stdio.h>
#include "struct.h"
#include "funcoes.h"
#include <ctype.h>
#include <stdlib.h>

#define TAM_MAX_LINHA 1024
#define DELIMITADOR ";"
#define TAM 100


int main(void) 
{
  int numeros[TAM];
  games game[50];

  int i;
  int id;
  int repete=1;
  i=leraquivo(game,TAM,numeros);

  gerarAleatorioNum(numeros,50,1000,i);  
  
  while(repete)
  {
    int resposta = 0; 
    
    resposta = opcoes(resposta);
    
    switch(resposta)
    {
      case 0:
        repete=0;
        break;
      case 1:
        cadastro(&game[i],i,numeros);
        i=i+1;
        break;
      case 2:
        alterar(game,i);
        break;
      case 3:
        deletar(game,i);
        break;
      case 4:
        consultar(game,i);
        break;
      default:
        printf("Por favor inserir uma opção válida");
        break;
    }
  }
  printf("Deseja salvar suas alterações? S/N? (Inclui a ordenação)  \n");
  char res;
  scanf(" %c",&res);
  
  res=toupper(res);
  
  if(res=='S'){
                salvararquivo(game,i);
               }
  EsperaClickLimpaTela(0);
  imprimirtabela(game,i);
  printf("Muito obrigado por utilizar nosso software");
  return 0;
}