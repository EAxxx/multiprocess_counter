/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Função que identifica se o número é primo, retornando o número se ele for 
   primo e -1 se ele não for primo*/
int checarSePrimo(int numero)
{

  // Caso base
  if (numero == 1)
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

  // Extraímos os números da string
  p = strtok(entrada, " \n");
  for (tam = 0; p != NULL; tam++)
  {
    printf ("\n%s\n",p);

    *numeros = (int *) realloc(*numeros, (sizeof(int) * (tam + 1) ) ); // Alocamos mais espaço para o vetor

    (*numeros)[tam] = atoi(p); // Salvamos no vetor o número convertido para int

    p = strtok (NULL, " \n");

  }
  
  return tam;

}

int main()
{
  int *numeros = NULL; // Vetor que armazena os números a serem avaliados
  int totNums = 0; // Total de números a serem avaliados

  totNums = separarEmNumeros(&numeros);
  return 0;
}
