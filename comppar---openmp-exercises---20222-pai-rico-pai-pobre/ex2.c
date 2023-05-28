#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1073741824



void Vetor(int vet[]);
int Soma=0;

int main() {

  int Vetor[N];    
  int i;

  srand(time(NULL));
  
  printf("Tamanho do vetor: %d\n",N);
  Vetor(Vetor);

  
  
  double start=omp_get_wtime(); 
  

 

    int SomaLocal=0; 
    #pragma omp for
    for (int i=0; i<N; ++i) SomaLocal += Vetor[i];

    #pragma omp critical
    Soma += SomaLocal; 

  
    
  double end=omp_get_wtime();
  printf("Tempo do processamento: %lf\n",end-start);
  printf("Soma = %d\n",Soma);  
  printf("\nCalculo finalizado!\n");

  exit(0);

}

void Vetor(int vet[]) {  
   int i;
   
  
   for(i=0;i<N;i++)
      vet[i] = 1;
}