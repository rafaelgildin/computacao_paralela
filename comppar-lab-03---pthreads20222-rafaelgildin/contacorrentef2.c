// p=contacorrentef2 && gcc $p.c -o $p -lpthread && ./$p
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>

pthread_mutex_t the_mutex; //cria o mutex para a thread acessar a regiao critica

float saldo = 1000.00;
int N_THREADS=200;

void *deposito(void *arg){
  pthread_mutex_lock(&the_mutex);
  float *arg1 = (float *) arg;
  float valor = *arg1;
  saldo += valor;
  pthread_mutex_unlock(&the_mutex);
}
void *saque(void *arg){
  pthread_mutex_lock(&the_mutex);
  float *arg1 = (float *) arg;
  float valor = *arg1;
  saldo -= valor;
  pthread_mutex_unlock(&the_mutex);
  }

int main() {
  int i;
  float valor_deposito = 5.0, valor_saque = 2.0;
  pthread_t threads[N_THREADS]; //inicializa as threads
  pthread_mutex_init(&the_mutex, 0);//inicializa o mutex
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

  pthread_mutex_destroy(&the_mutex);//destroi o mutex
  printf("Saldo final: %.2lf\n", saldo);
  return 0;
}
