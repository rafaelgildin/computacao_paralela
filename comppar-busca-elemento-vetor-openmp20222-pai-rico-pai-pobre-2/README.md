## Alunos
Rafael Avraham Gildin Acherboim - TIA: 31940242

- linear-search.c com números que existem e que não existem nos vetores
- ![Alt text](imagens/ex.png?raw=true "foto")

----------------------------------------------------------------------
# comppar-busca-elemento-vetor-openmp
Busca paralela com OpenMP

Crie um código-fonte em C, utilizando somente #pragma omp parallel para encontrar um elemento em um vetor de tamanho de 2^16. Para isso:

- garanta que os elementos no vetor sejam únicos

- faça a busca em um elemento que realmente exista

- utilize as primitiva omp_get_num_threads(), omp_get_max_threads() e omp_get_thread_num()

- compile preferencialmente sem a opção -O2

- não utilize qualquer outra função OpenMP, ou de sincronização, além daquela descrita acima

- para testar a lógica do seu algoritmo, faça testes em vetores de tamanho pequenos.



Ao final, imprima a posição do elemento encontrado.

Submeter: o código fonte e prints da tela da execução.
