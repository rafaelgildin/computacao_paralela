#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1073741824

#define NTHREADS 1

void Vetor(int vet[]);

int main() {

  int Vetor[N];  
  int Soma=0;
  int i;

  srand(time(NULL));
  
  printf("Tamanho do vetor: %d\n",N);
  Vetor(Vetor);

  
  omp_set_num_threads(NTHREADS);
  double start=omp_get_wtime();
  
  #pragma omp parallel for reduction (+:Soma)
  for(i=0;i<N;i++)
    Soma += Vetor[i];
    
  double end=omp_get_wtime();
  printf("Tempo do processamento: %lf\n",end-start);
  printf("Soma = %d\n",Soma);  
  printf("\nCalculo finalizado!\n");

  exit(0);

}

void Vetor(int vet[]) {  
   int i;
   
   omp_set_num_threads(NTHREADS);
   #pragma omp parallel for 
   for(i=0;i<N;i++)
      vet[i] = 1;
}