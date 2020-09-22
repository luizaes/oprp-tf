### Trabalho Final de OPRP

##### Relatório do Checkpoint 1
* Nessa primeira fase do trabalho focamos no entendimento do código base e no estudo de como poderíamos melhorá-lo, levando em consideração otimizações, paralelização e algoritmos para solucionar os problemas em questão. Inicialmente tentamos retirar as recursões do código, mas isso só foi possível para a função de posicionamento dos cavalos. A partir daí buscamos soluções para paralelizar o posicionamento das rainhas, que é o processo mais custoso. Chegamos a algumas ideias:
    * Manter a recursividade e paralelizar as chamadas recursivas limitando a criação de threads até uma certa profundidade da árvore de recursão, para evitar o estouro devido ao excesso de threads criadas;
    * Modificar o algoritmo para posicionamento de rainhas usando outra lógica, como uma heurística. Um exemplo seria utilizar um algoritmo genético para minimizar o número de conflitos entre as rainhas, paralelizando alguns processos dentro das gerações, como as funções de crossover e fitness.
* Nos dois casos estamos estudando utilizar a biblioteca OpenMP ou MPI para realizar a paralelização, mas não decidimos ainda de forma definitiva. O código fonte anexado possui as modificações até então feitas, que envolvem a adaptação do posicionamento de cavalos sem recursão e a modificação do posicionamento das rainhas, que possui um bracktracking (garante a solução ótima) mais otimizado. Não temos certeza se esse backtracking será realmente o utilizado, pois por mais que garanta a solução ótima o tempo de execução é muito grande para casos onde n >= 30.

##### Relatório do Checkpoint 2
* *Escrever de 5 a 10 linhas sobre o desenvolvimento, desafios e ideias*

##### Links úteis
* [Paralelização de backtracking](https://www.drdobbs.com/architecture-and-design/three-parallel-backtracking-designs/232300302)
* [Solução com Min-conflicts](https://medium.com/@carlosgonzalez_39141/using-ai-to-solve-the-n-queens-problem-2a5a9cc5c84c)