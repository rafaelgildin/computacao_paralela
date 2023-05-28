// p=merge-sort && gcc -o $p -fopenmp $p.c && ./$p

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;

    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }

    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];

    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];

    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}

void mergesort(int a[],int i,int j)
{
    // printf("N threads: %d\n", omp_get_thread_num());
    int mid;

    if(i<j)
    {
        mid=(i+j)/2;

        #pragma omp task firstprivate (a, i, mid)
        mergesort(a,i,mid);        //left recursion
 		
        #pragma omp task firstprivate (a, j, mid)
        mergesort(a,mid+1,j);    //right recursion

        //Wait for both paralel tasks to complete execution
        #pragma omp taskwait
        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
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
//     int *a, num, i;
//     scanf("%d",&num);

//    a = (int *)malloc(sizeof(int) * num);
//     for(i=0;i<num;i++)
//         scanf("%d",&a[i]);
    int i, num = 10, thread_count = 4;
    int a[10] = {8,7,9,1,2,5,4,3,0,6};
    
    printf("\nInicial array :\n");
    print_array(a, num);
    
    #pragma omp parallel num_threads(thread_count)
    {
        #pragma omp single
        printf("\nN threads: %d\n", omp_get_num_threads());
        mergesort(a, 0, num-1);
    }

    printf("\nSorted array :\n");
    print_array(a, num);
    return 0;
}