
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

#define TAM_MAX_LINHA 1024
#define DELIMITADOR ";"
#define TAM 100





/*imprimirtabela
  EsperaClickLimpaTela
  opcoes
  cadastro
  trocar
  ordenar
  listar 
  consultar
  alterar
  deletar
  leraquivo
  salvararquivo
  existeNum
  gerarAleatorioNum
  */



void imprimirtabela(games *game,int i)
{
printf("----------Jogos cadastrados----------\n\n");
  printf("N°|Nome   |ID   |Gênero  |Ano  \n");
  printf("____________________________________\n");
  for(int j=0;j<i;j++)
  {
    if(game[j].existe)
      printf("%d | %s | %d | %s | %d\n", j+1, game[j].nome,game[j].id,game[j].genero,game[j].anolancamento);
      printf("____________________________________\n");
  }
}

void EsperaClickLimpaTela(int x)
{
  char esperaTecla;

  if(x)
  {
    printf("\nPressione 'Enter' para voltar");
    scanf("%c", &esperaTecla);
    esperaTecla = getchar();
  }
  system("@cls||clear");
}

int opcoes(int resposta)
{
  
  printf("----------CADASTRO DE JOGOS----------\n\n");
  printf("1 - CADASTRAR novo jogo\n");
  printf("2 - ALTERAR um jogo cadastrado\n");
  printf("3 - DELETAR um jogo cadastrado\n");
  printf("4 - CONSULTAR um jogo cadastrado\n\n");
  printf("0 - SALVAR e SAIR do sistema\n\n");
  printf("Sua escolha: ");
  scanf("%d",&resposta);

  EsperaClickLimpaTela(0);

  return resposta;
}

void cadastro(games *game,int i,int *num)
{
  game->id=num[i];

  game->existe=1;
  char res;
  
  printf("---------CADASTRAR NOVO JOGO---------\n\n");
  printf("OBS.: Tente não dar 'espaço')\n");
  printf("Nome do Game: ");
  scanf("%s",game->nome);
  printf("Gênero de %s: ",game->nome);
  scanf(" %s",game->genero);
  printf("Ano de lançamento %s: ",game->nome);
  scanf("%d",&game->anolancamento);
  printf("%s é multiplayer?(S/N) ",game->nome);
  scanf(" %c",&res);
  
  res=toupper(res);
  
  if(res=='S')
    game->multiplayer=1;
  else
    game->multiplayer=0;

  EsperaClickLimpaTela(1);
}

void trocar(games *game,int i)
{
  games aux[TAM];
  aux[i]=game[i];
  game[i]=game[i+1];
  game[i+1]=aux[i];
}

void ordenar(games *game,int i)
{
int continua=1;
int j;

while(continua==1)
  {
    for(j=0;j<i;j++)
    {
    
      if(game[j].id > game[j+1].id)
      {
        
        if(game[j+1].id!=0)
        {
        
        trocar(game,j);
        j=0;
        break;
        }
      }
      
    }
        
        if(i==j)
        {
         
         continua=0;
        }
  } 
}

void listar(games *game,int i)
{
  printf("----------Jogos cadastrados----------\n\n");
  printf("N°  Nome \n");
  printf("____________________________________\n");
  for(int j=0;j<i;j++)
  {
    if(game[j].existe)
      printf("%d | %s\n", j+1, game[j].nome);
      printf("____________________________________\n");
  }

  printf("Deseja visualizar os dados em ordem de id? S/N? \n");
  char res;
  scanf(" %c",&res);
  
  res=toupper(res);
  
  
  if(res=='S'){
                ordenar(game,i);
                imprimirtabela(game,i);
              }
  
}

void consultar(games *game, int i)
{
  int aux;
  listar(game,i);
  printf("\nQual game deseja consultar? ");
  scanf("%d",&aux);

  printf("\nNome: %s",game[aux-1].nome);
  printf("\nID: %d",game[aux-1].id);
  printf("\nGênero: %s",game[aux-1].genero);
  printf("\nO game foi lançado em: %d",game[aux-1].anolancamento);
  
  if(game[aux-1].multiplayer==1)
    printf("\nO game é multiplayer\n");
  else
    printf("\nO game é singleplayer\n");

  EsperaClickLimpaTela(1);
}

void alterar (games *game,int i)
{   
  int aux;
  listar(game,i);
  printf("\nQual game deseja alterar? ");
  scanf("%d",&aux);

  char res;
  printf("\nVocê selecionou %d\n\n", aux);
  printf("OBS.: Tente não dar 'espaço')\n");
  printf("Novo nome: ");
  scanf("%s",game[aux-1].nome);
  printf("Gênero de %s? ",game[aux-1].nome);
  scanf("%s",game[aux-1].genero);
  printf("Ano de lançamento %s? ",game[aux-1].nome);
  scanf("%d",&game[aux-1].anolancamento);
  printf("%s é multiplayer?(S/N) ",game[aux-1].nome);
  scanf("%c",&res);
  printf("\n");
  res=toupper(res);
  
  if(res=='S')
    game[aux].multiplayer=1;
  else
    game[aux].multiplayer=0;
  
  EsperaClickLimpaTela(1);
}


void deletar (games *game,int i)
{   
  int aux;
  listar(game,i);
  printf("\nQual game deseja deletar? ");
  scanf("%d",&aux);

  game[aux-1].existe=0;

  EsperaClickLimpaTela(1);
}

int leraquivo(games *game,int tamanho, int *num)
{
  int t=0;
  char variavel[50];
  
  FILE* arq = fopen("games.csv", "r");

  if (arq == NULL) 
    printf("Falha ao abrir o arquivo");
  
  char linha[TAM_MAX_LINHA];
  char *campo;
  fgets(linha, TAM_MAX_LINHA, arq);
  campo = strtok(linha, DELIMITADOR);
  campo = strtok(linha, DELIMITADOR);
  campo = strtok(linha, DELIMITADOR);
  while (fgets(linha, TAM_MAX_LINHA, arq) != NULL)
  {
    campo = strtok(linha, DELIMITADOR);
    strcpy (variavel,campo);
    game[t].id=atoi(variavel);
    num[t]=game[t].id;
           
    campo = strtok(NULL, DELIMITADOR);
    strcpy (game[t].nome,campo);
           
    campo = strtok(NULL, DELIMITADOR);
    strcpy (variavel,campo);
    game[t].anolancamento=atoi(variavel);

    campo = strtok(NULL, DELIMITADOR);
    strcpy (variavel,campo);
    game[t].multiplayer=atoi(variavel);
        
    campo = strtok(NULL, "\n");
    strcpy (game[t].genero,campo);
          
    game[t].existe=1;
    t=t+1;  
  }
  if(tamanho<=t)
    printf("limite de memória do vetor alcançada!");
  //testar a quantidade de elementos
  fclose(arq);   
  return t;
}

void salvararquivo(games *game,int i)
{
  int u;

  FILE* arq = fopen("games.csv", "w");

  if (arq == NULL) 
    printf("Falha ao abrir o arquivo");
    fprintf(arq,"ID;NOME;ANOLANÇAMENTO;MULTIPLAYER;GENERO\n");

  for(u=0;u<i;u++)
  {
    if(game[u].existe==1)
        fprintf(arq,"%d;%s;%d;%d;%s\n",game[u].id,game[u].nome,game[u].anolancamento,game[u].multiplayer,game[u].genero);
  }

   fclose(arq);
}

int existeNum(int valores[],int tam,int valor)
{
 for(int l=0;l<tam;l++)
 {
   if(valores[l]==valor){return 1;}
 }
 return 0;
}

void gerarAleatorioNum (int num[], int quantNumeros,int limite,int arquivos)
{
  srand(time(NULL));

  int x,t;
  for(int i=arquivos;i<quantNumeros;i++)
  {
    x = rand() % limite;
    t=existeNum(num,i,x);
    while(t==1)
    {
      x = rand() % limite;
      t=existeNum(num,i,x);
    }
    num[i] = x;
  } 
}
