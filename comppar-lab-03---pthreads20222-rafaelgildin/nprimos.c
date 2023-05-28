// p=nprimos && gcc $p.c -o $p -lpthread && ./$p 3
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t the_mutex; //cria o mutex para a thread acessar a regiao critica

// int N_THREADS=4;
const int J=10, K=40; // J:inicio | K:fim
int* primosT = NULL, Qprimos=0;//quantidade de primos

void * nprimos(void *args){
    pthread_mutex_lock(&the_mutex);
    // pega argumantos
    int *args_ = (int *) args;
    int j = args_[0], k = args_[1];

    int l = k-j+1;
    int primos[l];
    int i0, i1, eh_primo, qprimos=0;

    for(i0=0; i0<l; i0++){ primos[i0] = 0;}// zerar vetor

    // buscar os primos no intervalo (j,k)
    for(i0=j;i0<=k;i0++){
        eh_primo=1;
        for(i1=2; i1<i0; i1++){
            if(i0 % i1 == 0){
                eh_primo=0;//n eh primo
                break;
            }
        }
        //inserir primo na lista
        if(eh_primo){
            // printf("%d\n",i0);
            primos[qprimos] = i0;
            primosT[Qprimos+qprimos] = i0;
            qprimos++;
        }
    }

    // // printando os primos locais
    // for(i0=0; i0<qprimos; i0++){
    //     printf("primos[%d]: %d\n", i0, primos[i0]);
    // }

    Qprimos += qprimos; //incrementa Total primos
    pthread_mutex_unlock(&the_mutex);
}

int main(int argc, char *argv[]){

    // Pega N de Threads por linha de comando
    int N_THREADS = atoi(argv[1]);
    if (N_THREADS <= 0){
        printf("numero de Threads deve ser maior que 0\n");
        return 1;
    }

    printf("\nQuantidade de Threads = %d  | J = %d | K = %d\n\n", N_THREADS, J, K);
    
    pthread_t threads[N_THREADS]; //inicializa as threads
    pthread_mutex_init(&the_mutex, 0);//inicializa o mutex

    int i, L = K-J+1;
    int n_por_T = L/N_THREADS;
    primosT = calloc(L, sizeof(int));//cria vetor para todos os primos
    for(i=0; i<L; i++){ primosT[i] = 0;}// zerar vetor
    
    // --------- Pega os indices
    printf("\nDividindo os indices (j,k) por Thread:\n");
    int indices[N_THREADS][2];
    int j = J, k=j+n_por_T;
    indices[0][0] = j;
    indices[0][1] = k;

    for(i = 1; i < N_THREADS; i++){
        j = k+1;
        k += n_por_T;
        indices[i][0] = j;
        indices[i][1] = k;
    }
    indices[N_THREADS-1][1] = K; // ultimo termo deve ser igual a K

    //printando eles
    for(i = 0; i < N_THREADS; i++){
        printf("ind[%d][%d] = %d\n", i, 0, indices[i][0]);
        printf("ind[%d][%d] = %d\n\n", i, 1, indices[i][1]);
    }

    //--------Threads
    // cria as threads
    for(i = 0; i < N_THREADS; i++){
        pthread_create(&threads[i], 0, nprimos, (void *) indices[i]);
    }

    //executa as threads
    for(i = 0; i < N_THREADS; i++){
        pthread_join(threads[i], 0);
    }
    pthread_mutex_destroy(&the_mutex);//destroi o mutex

    //--------Printando primos
    printf("\n\nprintando primosT:\n");
    for(i=0; i<Qprimos; i++){
        printf("primos[%d]: %d\n", i, primosT[i]);
    }


    return 0;
}