#include <stdio.h>

void ex2(){
    // ex 2
    float n1, n2, n3, me, ma;
    char letra[1];

    printf("Digite n1:\n"); scanf("%f", &n1);
    printf("Digite n2:\n"); scanf("%f", &n2);
    printf("Digite n3:\n"); scanf("%f", &n3);
    me = (n1 + n2 + n3) / 3;
    ma = (n1 + n2*2 + n3*3 + me)/7;
    printf("me = %.2f, ma = %.2f\n\n", me, ma);

    if (me >= 9.0){
        letra[0] = *"A";
    }
    if ((me < 9.0) && (me >= 7.5)){
        letra[0] = *"B";
    }
    if ((me < 7.5) && (me >= 6.0)){
        letra[0] = *"C";
    }
    if ((me < 6.0) && (me >= 4.0)){
        letra[0] = *"D";
    }
    if (me < 4){
        letra[0] = *"E";
    }
    printf("Sua nota eh = %s\n\n", letra);
}

void ex8(){
    int l,c; //pegando o n de linhas e colunas
    printf("\n\n\nDigite o numero de linhas:"); scanf("%d", &l);
    printf("Digite o numero de colunas:"); scanf("%d", &c);
    int m[l][c], t[c][l]; // criando a matriz e a transposta

    // Inserindo os elementos na matriz
    printf("\nInsira os elementos da matriz: a(linha)(coluna)\n");
    for (int i = 0; i < l; ++i)
    for (int j = 0; j < c; ++j) {
        printf("Insira o elemento a(%d)(%d): ", i + 1, j + 1);
        scanf("%d", &m[i][j]);
    }

    // printando a matriz m[][]
    printf("\nMatriz inserida: \n");
    for (int i = 0; i < l; ++i)
    for (int j = 0; j < c; ++j) {
        printf("%d  ", m[i][j]);
        if (j == c - 1)
        printf("\n");//pula linha apos a ultima coluna
    }

    // Calculando a matriz transposta
    for (int i = 0; i < l; ++i)
    for (int j = 0; j < c; ++j) {
        t[j][i] = m[i][j];
    }

    // printando a matriz transposta
    printf("\nTranspose of the matrix:\n");
    for (int i = 0; i < c; ++i)
    for (int j = 0; j < l; ++j) {
        printf("%d  ", t[i][j]);
        if (j == l - 1)
        printf("\n");
    }
}


int main() {
    ex2();
    // ex8();
    return 0;
}