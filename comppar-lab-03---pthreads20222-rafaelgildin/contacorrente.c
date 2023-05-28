// p=contacorrente && gcc $p.c -o $p -lpthread && ./$p
#include<stdio.h>
#include<stdlib.h>

float saldo = 1000.00;
int N = 100; // 2147483000;

void deposito(float valor){
  saldo += valor;
}

void saque(float valor){
  saldo -= valor;
}

int main() {
  int i;
  float valor_deposito = 5.0, valor_saque = 2.0;
  printf("Saldo inical: %.2lf\n", saldo);

  for(i = 0; i < N; i++){
    deposito(valor_deposito);
  }
    
  for(i = 0; i < N; i++){
    saque(valor_saque);
  }

  printf("Saldo final: %.2lf\n", saldo);
  return 0;  
}
