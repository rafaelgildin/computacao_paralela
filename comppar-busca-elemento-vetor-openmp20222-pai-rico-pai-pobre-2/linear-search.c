// p=linear-search && gcc -o $p -fopenmp $p.c && ./$p
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

typedef struct
{
	int num;
} Vetor;

void linearSearch(Vetor vetor[], int n, int tos, int *idx){
	int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
	int local_idx = -1;
	int iter;
	int local_n = n/thread_count;
	int local_start = my_rank * local_n;
	int local_end = local_start + local_n -1;
	printf("my_rank=%d, local_start=%d, local_end=%d,Als=%d, Ale=%d, A0=%d, An=%d\n",
	my_rank,local_start,local_end,vetor[local_start].num, vetor[local_end].num,
	vetor[0].num, vetor[65535].num);

	// arrumando a última posição
	if(local_end >= n){
		local_end = n-1;
	}

	// printf("int my_rank = %d\n", omp_get_thread_num());
	for(iter=local_start; iter<= local_end; iter++){
		// printf("%d = %d\n", iter, A[iter]);
		if(vetor[iter].num == tos){
			local_idx = iter;
			break;
		}
	}

	if(local_idx == -1){
		iter-=1;
	}
	// #pragma omp critical
	if (local_idx != -1) {
		*idx = local_idx;
	}

	// printf("\nlocal_n=%d, tos=%d, local_idx=%d,", local_n, tos, local_idx);
	// printf("\nmy_rank=%d, local_start=%d, local_end=%d, iter=%d, last_num=%d\n", my_rank,local_start,local_end, iter, A[iter]);
}

int read_file(char filename[], int csv_rows, Vetor vetor[]){
	FILE* file = fopen(filename, "r");
	int read = 0, row = 0;

    if (file == NULL){
        printf("Erro ao abrir o arquivo \n");
		return 1;
	}
	do
	{
		read = fscanf(
			file, 
			"%d\n",
			&vetor[row].num);
		if (read == 1) row ++;
		if (read != 1 && !feof(file)){
			printf("Formato incorreto do arquivo\n");
			return 1;
		}
		if (ferror(file)){
			printf("Erro no arquivo\n");
			return 1;
		}
	} while (!feof(file));

	fclose(file);
	printf("\n%d linhas lidas. \n\n", row);
	// for (int i=0; i<row; i++){
	// 	printf("%d\n", vetor[i].num);
	// }
	// printf("\n");
	return 0;
}

int find_number(char filename[], int find, int csv_rows){
	int idx=-1, thread_count=4;
	Vetor vetor[csv_rows];

	printf("filename = %s, find = %d, threads=%d\n", filename, find, thread_count);

	int file_response = read_file(filename, csv_rows, vetor);
	if (file_response) return 1;

	#pragma omp parallel num_threads (thread_count)
	{	
		linearSearch(vetor, csv_rows, find, &idx);
	}
	if(idx == -1)
		printf("Não encontrado");
	else
		printf("Encontrado na posição = %d", idx);
	printf("\n\n");
	return 0;
}


int main(){
	int csv_rows = 65536;
	char file_name1[] = "vetor1.csv"; int find1 = 165207;
	char file_name2[] = "vetor2.csv"; int find2 = 1158899;
	int find3 = 181818181;//numero que não existe

	printf("---------------\n"); find_number(file_name1, find1, csv_rows);
	printf("---------------\n"); find_number(file_name2, find2, csv_rows);
	
	printf("---------------\n"); find_number(file_name1, find3, csv_rows);
	printf("---------------\n"); find_number(file_name2, find3, csv_rows);
	return 0;
}