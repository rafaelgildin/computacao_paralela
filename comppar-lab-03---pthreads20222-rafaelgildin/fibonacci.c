/*
>> gcc fibonacci.c -lpthread -o fibonacci && ./fibonacci
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n = 10;
int *fibseq; //ponteiro para o vetor de fib
pthread_t *threads;
pthread_attr_t attr;

void *fib_th(void *arg)
{
   /* funcao que calcula o fibonacci com threads*/
   int i_ = *((int *) arg);
   // printf("i = %d - thread = %d \n", i_, (int)threads[i_]);
   fibseq[i_] = fibseq[i_ - 1] + fibseq[i_ - 2];
   pthread_exit(0);
}       

int fib(int n)                             
 {                                          
 /* funcao que calcula o fibonacci sem threads*/
    if(n == 0) return 0;
    else if (n == 1) return 1;
    else return (fib(n-1) + fib(n-2));
 }
  
int main(void)
  {
   int i;
   fibseq = (int *)malloc(n * sizeof(int));
   fibseq[0] = 0;
   fibseq[1] = 1;
   threads = (pthread_t *) malloc(n * sizeof(pthread_t));
   pthread_attr_init(&attr);

   // printf("\nCriando as threads\n");
   for (i = 2; i < n; i++)
   {
      pthread_create(&threads[i], &attr, fib_th, (void *) &i);
      // printf("thread criada: %d\n", threads[i]);
   }
   for (i = 2; i < n; i++)
   {
      pthread_join(threads[i], NULL);
   }

   // printing fibseq.
   printf("Sequencia de Fibonacci com threads :\n");
   for (i = 0; i < n; i++)
   {
      printf("%d,", fibseq[i]);
   }
   printf("\n\n");


   // criacao sem threads
   printf("Sequencia de Fibonacci sem threads :\n");
   for (i = 0; i < n; i++)
   {
      printf("%d,", fib(i));
   }
   printf("\n\n");

   return 0;
}
