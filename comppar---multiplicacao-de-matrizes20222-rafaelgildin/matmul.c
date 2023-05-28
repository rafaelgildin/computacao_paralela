/*
Objetivos:
- compilar com O0 e com O3:
    Sem bloco: invertendo indices
    Sem bloco: indices certo
    Com bloco: indice correto

Compilar padrão:
    >> gcc matmul.c -o matmul && ./matmul
Compilar com O0:
    >> gcc -O0 matmul.c -o matmul && ./matmul
Compilar com O3:
    >> gcc -O3 matmul.c -o matmul && ./matmul
*/

#include <stdio.h>
#include <sys/time.h> 
#include <stdlib.h>

struct timeval tv;
double start_t, end_t, tempo_gasto;

void MultMatCerto(int n, int m, int ** a, int **  b, int ** c)
{
    int i, j, k ,par=0;
    printf("\n\n===========  Iniciando multiplicacao Certa ============\n");            
    gettimeofday(&tv, NULL);
    start_t = (double) tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    
    for (i=0;i<n; i++){
        for (j = 0; j<n; j++){
            for (k=0;k<n; k++){
                a[i][j] += (b[i][k]) * (c[k][j]);
                if ( a[i][j] % 2 == 0)
                    par += 1;
                }
        }
    }

    gettimeofday(&tv,NULL);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    tempo_gasto = end_t - start_t;
    printf(" %d pares, tempo %f usecs\n", par,tempo_gasto);
}


void MultMatInvertido(int n, int m, int ** a, int **  b, int ** c)
{
    int i, j, k ,par=0;
    printf("\n\n===========  Iniciando multiplicacao Invertida ============\n");            
    gettimeofday(&tv, NULL);
    start_t = (double) tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    
    for (i=0;i<n; i++){
        for (j = 0; j<n; j++){
            for (k=0;k<n; k++){
                a[i][j] += (b[k][i]) * (c[k][j]);
                if ( a[i][j] % 2 == 0)
                    par += 1;
                }
        }
    }

    gettimeofday(&tv,NULL);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    tempo_gasto = end_t - start_t;
    printf(" %d pares, tempo %f usecs\n", par,tempo_gasto);
}

void MultMatCertoBloco(int n, int m, int ** a, int **  b, int ** c, int blockSize)
{
    int i, j, k, iInner, jInner, kInner, par=0;

    printf("\n\n===========  Iniciando multiplicacao Certa Bloco ============\n");            
    gettimeofday(&tv, NULL);
    start_t = (double) tv.tv_sec + (double)tv.tv_usec / 1000000.0;

    for (i = 0; i < n; i+=blockSize)
        for (k = 0 ; k < n; k+=blockSize)
            for (j=0; j<n ; j+= blockSize)
                for (iInner = i; iInner<i+blockSize; iInner++)
                for (kInner = k ; kInner<k+blockSize ; kInner++)
                    for (jInner = j ; jInner<j+blockSize; jInner++){
                        a[iInner][jInner] += b[iInner][kInner] * c[kInner][jInner] ;
                        if ( a[i][j] % 2 == 0)
                            par += 1;
                    }                            
    gettimeofday(&tv,NULL);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    tempo_gasto = end_t - start_t;
    printf(" %d pares, tempo %f usecs\n", par,tempo_gasto);
}

int main(){

    /* exemplos de tamanhos das matrizes a serem geradas */ 
    int tamanhos[] = {3, 1000, 400, 32, 64, 128, 256, 512, 640, 768, 896, 1024, 1536};
    int tamanhos_bloco[] = {1, 10, 50};
    int indice = 1;

    int MAX = tamanhos[indice], tamanho_bloco=tamanhos_bloco[indice];
    int n, i, j, k, par;
    
    /* aloca espaco para a matriz */
    /* MAX eh inicializado com um dos tamanhos do vetor acima */
    
    int **a =   calloc(MAX, sizeof(int* ));
    int **b =   calloc(MAX, sizeof(int* ));
    int **c =   calloc(MAX, sizeof(int* ));

    for(i=0; i< MAX; i++){
        a[i] = calloc(MAX, sizeof(int *));
        b[i] = calloc(MAX, sizeof(int *));
        c[i] = calloc(MAX, sizeof(int *));
    }
    
    printf("\nMAX = %d, bloco = %d\n", MAX, tamanho_bloco);
    /* inicializa as matrizes */
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            a[i][j] = 2;
            b[i][j] = 2;
            c[i][j] = 0;
        }
    }

    // /* multiplica as matrizes */
    MultMatCerto(MAX,MAX,c,a,b);
    MultMatInvertido(MAX,MAX,c,a,b);
    MultMatCertoBloco(MAX,MAX,c,a,b,tamanho_bloco);
   
    // // printa matriz
    // printf("\nprintando a matriz:\n\n");
    // for(i=0; i<MAX; i++){
    //     for(j=0; j<MAX; j++){
    //         printf("%d ",c[i][j]);
    //     }
    //     printf("\n");
    // }
   
}
