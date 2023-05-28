// p=selection-sort && gcc -o $p -fopenmp $p.c && ./$p

#include <stdio.h>
#include <omp.h>

struct Compare {
	int val;
	int index; 
};
#pragma omp declare reduction(maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out)

void selectionsort(int* arr, int size)
{
    for (int i = size - 1; i > 0; --i)
    {
        //declara o primeiro valor como max
		struct Compare max;
        max.val = arr[i];
        max.index = i;

		//busca o maior valor em paralelo
        #pragma omp parallel for reduction(maximum:max)
        for (int j = i - 1; j >= 0; --j)
        {
            if (arr[j] > max.val)
            {
                max.val = arr[j];
                max.index = j;
            }
        }

		//coloca o maior na última posicao do vetor
        int tmp = arr[i];
        arr[i] = max.val;
        arr[max.index] = tmp;		

    }
}

void print_array(int a[], int num){
    int i;
    for(i=0;i<num;i++)
        printf("%d ",a[i]);
    printf("\n");
}

int main()
{
    int x[10] = {8,7,9,1,2,5,4,3,0,6};
    printf("Antes da ordenação\n"); print_array(x, 10);
    selectionsort(x, 10);
    printf("Após da ordenação\n"); print_array(x, 10);
    return 0;
}