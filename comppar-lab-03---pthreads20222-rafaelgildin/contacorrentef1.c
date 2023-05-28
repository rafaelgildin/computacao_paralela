// p=contacorrentef1 && gcc $p.c -o $p -lpthread && ./$p
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>

float saldo = 1000.00;
int N_THREADS=200;

void *deposito(void *arg){
  float *arg1 = (float *) arg;
  float valor = *arg1;
  saldo += valor;
}
void *saque(void *arg){
  float *arg1 = (float *) arg;
  float valor = *arg1;
  saldo -= valor;}

int main() {
  int i;
  float valor_deposito = 5.0, valor_saque = 2.0;
  pthread_t threads[N_THREADS]; //inicializa as threads
  printf("Saldo inical: %.2lf\n", saldo);

  // cria as threads
  for(i = 0; i < N_THREADS; i++){
    if(i < N_THREADS/2){
      pthread_create(&threads[i], 0, deposito, &valor_deposito);
    }
    else{
      pthread_create(&threads[i], 0, saque, &valor_saque);
    }
  }

  //executa as threads
  for(i = 0; i < N_THREADS; i++){
    pthread_join(threads[i], 0);
  }

  printf("Saldo final: %.2lf\n", saldo);
  return 0;
}
