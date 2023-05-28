// gcc parte2.c -o parte2 && ./parte2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPRIMENTO_MAX_LINHA 30
#define MAX_STR 10

typedef struct{
    char nome[COMPRIMENTO_MAX_LINHA];
    int idade;
    float altura;
}PESSOA;

int PegarPovo(PESSOA Povo[], int* LinhaPovo){
    /*
    Objetivo:
        - Leitura do arquivo.txt, com 10 pessoas no seguinte formato:
            - Nome
            - Idade
            - Altura
        - Colocar cada pessoa no vetor Povo
    Argumentos:
        - Povo: vetor com 10 PESSOA
        - LinhaPovo: 0 default
    Retorna:
        - 0: ok
        - 1: nok
    */
    char Linha[COMPRIMENTO_MAX_LINHA], NomeArquivo[50], c;
    PESSOA P;
    FILE *Arq;
    int LinhaPessoa= 0, LinhaArq = 0, p;
 
    // ler nome do arquivo
    strcpy(NomeArquivo, "arquivo.txt"); // comentar --------
    // printf("Digite o nome do arquivo: "); scanf("%s", &NomeArquivo);
    // printf("\nnome do arquivo: %s\n", NomeArquivo);

	Arq = fopen(NomeArquivo, "r");
	if (Arq == NULL) {
		printf("O arquivo nao pode ser aberto \n");
        return 1;
	}
    
    // printf("Conteudo do arquivo: \n");
    // metodo para ler string
    while (fgets(Linha, COMPRIMENTO_MAX_LINHA, Arq) != NULL) {
        // printf("LinhaArq[%02d] LinhaP[%02d] LinhaPovo[%02d] : %s", LinhaArq, LinhaPessoa, *LinhaPovo, Linha);
        if (LinhaPessoa == 0){
            strtok(Linha, "\n"); //remove \n da str
            strcpy(P.nome, Linha);
            ++LinhaPessoa;
        }
        else if (LinhaPessoa == 1){
            P.idade = atoi(Linha);
            ++LinhaPessoa;
        }
        else if (LinhaPessoa == 2){
            // printf("\nLinhaPessoa = %d\n", LinhaPessoa);
            P.altura = strtod(Linha, NULL);
            Povo[*LinhaPovo] = P;
            LinhaPessoa = 0;
            ++*LinhaPovo;
        }
        ++LinhaArq;
    }
    fclose(Arq);
    return 0;
}

void OrdenaPovo(PESSOA Povo[], int LinhaPovo){
    /*
    Objetivo:
        - Ordenar o vetor Povo por altura atraves 
        do Bubble Sort.
    */
    int i,j;
    PESSOA temp = Povo[0];
    for(i=0; i<LinhaPovo; i++){ // i = 0,1 primeiro termo
        for(j=0; j<LinhaPovo-1; j++){ // j = 1,2 segundo termo
            if (Povo[j].altura > Povo[j+1].altura){//troca
                temp = Povo[j];
                Povo[j] = Povo[j+1];
                Povo[j+1] = temp;
            }
        }
    }
}

int ExportarPovo(PESSOA Povo[], int LinhaPovo){
    /*
    Objetivo:
        - Exportar o povo para txt, seguindo o padrao
        do arquivo inicial.
    */ 
    
    int p;
    char altura[MAX_STR], idade[MAX_STR];

    char *NomeArquivo = "arquivo_altura_ordenada.txt";
    FILE *Arq = fopen(NomeArquivo, "w");
    for (p = 0; p < LinhaPovo; p++){
        gcvt(Povo[p].altura, 6, altura); // altura: f -> str
        sprintf(idade, "%d", Povo[p].idade); // idade: d -> str
        // printf("\n\nPessoa[%d]:\nnome:%sidade:%s\naltura:%s\n",p, Povo[p].nome, idade, altura);
        fprintf(Arq, "%s\n", Povo[p].nome);
        fprintf(Arq, "%s\n", idade);
        fprintf(Arq, "%s\n", altura);
    }
    fclose(Arq);
    return 0;
}

void PrintarPovo(PESSOA Povo[], int LinhaPovo){
    int i;
    
    // printando as alturas do povo
    // for(i=0; i<LinhaPovo; i++){
    //     printf("Altura %.2f\n", Povo[i].altura);
    // }

    // printando o povo
    for(i=0; i<LinhaPovo; i++){
        printf("\nPessoa[%d]:  nome:%s    idade:%d    altura:%.2f",
        i, Povo[i].nome, Povo[i].idade, Povo[i].altura);
    }

    // // pegar as alturas como vetores
    // float alturas[10];
    // for(p=0; p<LinhaPovo; p++){
    //     alturas[p] = Povo[p].altura;
    // }
}

int main()
{
    PESSOA Povo[10];
    int LinhaPovo = 0, i;
    PegarPovo(Povo, &LinhaPovo);

    printf("\n******Printando o povo******"); PrintarPovo(Povo, LinhaPovo);
    OrdenaPovo(Povo, LinhaPovo);
    printf("\n\n******Printando o povo com alturas ordenadas******"); PrintarPovo(Povo, LinhaPovo);
    printf("\n\n");

    ExportarPovo(Povo, LinhaPovo);
    return 0;
}