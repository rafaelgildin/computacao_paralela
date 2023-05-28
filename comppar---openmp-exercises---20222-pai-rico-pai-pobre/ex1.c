// p=ex1 && gcc -o $p -fopenmp $p.c && ./$p 5

// verificar se o compilador tem openMP
#ifdef _OPENMP
#include <omp.h>
#endif

#include <stdio.h>
#include <stdlib.h>

double f(double x){
    return 2.0*x;
}

void Trap(double a, double b, int n, double *global_result_p){
    double h,x,my_result;
    double local_a, local_b;
    int i, local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b-a)/n;
    local_n = n/thread_count;
    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n*h;
    my_result = (f(local_a) + f(local_b)) /2.0;
    
    for (i=1; i<=local_n-1; i++){
        x = local_a + i*h;
        my_result += f(x);
    }
    my_result = my_result*h;

    #pragma omp critical
    *global_result_p += my_result;
}


int main(int argc, char* argv[])
{
    double global_result = 0.0; //Store result in global_result
    double a,b; // Left and right endpoints
    int n; //total number of trapezoids

    int thread_count = strtol(argv[1], NULL, 10); //get n threads from cli

    // pegar a,b,n
    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);
    // a = 2.0, b=10.0, n = 10;

	#pragma omp parallel num_threads (thread_count)
	
    Trap(a, b, n, &global_result);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.14e\n", a,b,global_result);
    return 0;
}
