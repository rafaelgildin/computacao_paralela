Tarefa 2

Aluno: Rafael Avraham Gildin Acherboim - 31940242

Exercícios com processos:
* 1) Rode o programa anterior para valores grandes de n. As mensagens sempre estarão ordenadas pelo valor de i?
* 2) O que acontece se o programa anterior escreve-se as mensagens para sys.stdout, usando print, ao invés de para sys.stderr?

Respostas:
1) Sim. Pois com o comando sys.stderr as mensagens são enviadas como se fossem erros, logo são enviadas imediatamente quando ocorrem, o que mantem a ordem dessas.
![Alt text](imagens/ex1.jpg?raw=true "Tarefa")

2) As mensagens poderiam estar desordenadas, uma vez que com o comando sys.stdout elas são armazenadas em um buffer antes de serem printadas na tela, o que pode gerar a desordenação destas.
![Alt text](imagens/ex2.jpg?raw=true "Tarefa")
