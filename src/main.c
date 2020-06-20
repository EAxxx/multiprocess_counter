/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <unistd.h>


/* Função que identifica se o número é primo, retornando o número se ele for 
   primo e -1 se ele não for primo*/
int checarSePrimo(int numero)
{

  // Casos base
  if ( (numero == 1) || (numero == 0) )
  {
    return -1;
  }

  for (int i = 2; i <= numero / 2; ++i)
  {

    // Se o número não é primo
    if (numero % i == 0)
    {
      numero = -1;
      break;
    }

  }

  return numero;

}

/* Função que recebe a string de entrada com os números a serem análisados e extrai desta 
   cada número e os salva em um vetor */
int separarEmNumeros(int **numeros)
{

  char entrada[300]; // Armazena a entrada do programa como uma string
  char *p;
  int tam = 0; // Tamanho do vetor que armazena os números

  fgets(entrada, sizeof(entrada), stdin); // Recebemos a string de entrada

  p = strtok(entrada, " \n"); // Selecionamos o primeiro número da entrada
  for (tam = 0; p != NULL; tam++) // Extraímos os números da string
  {
    *numeros = (int *) realloc(*numeros, (sizeof(int) * (tam + 1) ) ); // Alocamos mais espaço para o vetor

    (*numeros)[tam] = atoi(p); // Salvamos no vetor o número convertido para int

    p = strtok (NULL, " \n"); // Selecionamos o próximo número

  }
  
  return tam;

}

int main(int argc, char *argv[])
{
  int *numeros = NULL; // Vetor que armazena os números a serem avaliados
  int totNums = 0; // Total de números a serem avaliados
  int numAval = 0; // Número que estamos avaliando se é primo ou não

  pid_t pidFilho; // PID do processo filho
  int totProcess = 0; // Total de processos executando no momento

  totNums = separarEmNumeros(&numeros); // Recebemos as entradas do programa

  for (int i = 0; i < totNums; i++)
  {
    totProcess++; // Incrementamos o contador de processos

    while (totProcess >= 4) // Se estamos no número máximo de processos simultâneos (4)
    {
      int status; // Indica se um dos processos filho está executando ou não

      waitpid(-1, &status, WNOHANG); // Esperamos um dos processos terminar
      // Se um dos filhos foi encerrado, decrementamos o contador de processos
      if (WIFEXITED(status))
      {
        totProcess--;
      }

    }
    
    pidFilho = fork(); // Criamos um novo processo


    if (pidFilho == 0) // Se estamos no processo filho
    {
      numAval = checarSePrimo(numeros[i]); // Determinamos se o número é primo

      if (numAval != -1) // Se o número for primo
      {
        printf("\n%d\n", numAval);
      }

      exit(0); // Encerramos o processo
    }
    
    
  }
  
  return 0;
}
