# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

#define ORDER_OF_MATRIX 256

int **alocateMatrix();
void freeMemory(int **m);
void populateMatrix(int **m);
double timeDiff(struct timeval *start, struct timeval *end);
void multiplyMatrix();
void printMatrix(int **m);

int n = ORDER_OF_MATRIX;
int i, j, k;
int **a;
int **r;

int main(void){
  struct timeval start, end;
  
  a = alocateMatrix();
  populateMatrix(a);
  r = alocateMatrix();
  
  gettimeofday(&start, NULL);
  multiplyMatrix();
  gettimeofday(&end, NULL);
  // printMatrix(r);
  printf("Tempo de execucao: %.9f segundos\n\n", timeDiff(&start, &end)); 
  freeMemory(a);
  freeMemory(r);
  return 0;
}

int **alocateMatrix() {
  int **matrix;

  matrix = calloc(n, sizeof(int *));
  for (i = 0; i < n; i++)
    matrix[i] = calloc(n, sizeof(int *));
  return matrix;
}

void freeMemory(int **m) {
  for (i = 0; i < n; i++) {
    free(m[i]);
  }
  free(m);
}

void populateMatrix(int **m) {
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      m[i][j] = i + j;
    }
  }
}

double timeDiff(struct timeval *start, struct timeval *end) {
  double startTime, endTime;
  startTime = (double)start->tv_sec + (double)start->tv_usec / 1000000.0;
  endTime = (double)end->tv_sec + (double)end->tv_usec * 1e-6;
  return endTime - startTime;
}

void multiplyMatrix() {
  for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
      for (int j = 0; j < n; j++)
        r[i][j] += a[i][k] * a[k][j];
}

void printMatrix(int **m){
  for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

