## Trabalho Final de Programação Paralela (OPRP)

### Compilação e execução
```
make clean

make

time ./knights-queens <número  de  linhas/colunas  do  board>  <número  de  cavalos>
```

### Problema

> O problema N Queens and K knights envolve posicionar K cavalos em um
> tabuleiro M x M e, além disso, posicionar a maior quantidade de
> rainhas possíveis nas células restantes, de modo que nenhum cavalo ou
> rainha esteja sob ataque.

### Arquitetura da Solução

- A lógica da solução desenvolvida é a seguinte: primeiro a rotina de posicionamento de cavalos é executada, e em seguida, quando todos os K cavalos foram inseridos no tabuleiro, executamos o posicionamento do maior número de rainhas possível.
	- Para posicionar os cavalos é executada uma estratégia gulosa, passando apenas uma vez por todas as células do tabuleiro e inserindo o cavalo caso seja possível.
	- Já para as rainhas, a estratégia foi:
		- Utilizar um backtracking que recursivamente procura todas as soluções válidas e salva a melhor, assim sempre retornando a solução ótima;
		- Implementar uma técnica de pruning para cortar caminhos da árvore de recursão que não são interessantes de se explorar (ou seja, que não conseguem nos trazer uma solução melhor do que a que já foi encontrada até o momento);
		- E paralelizar a função de posicionamento das rainhas, utilizando a biblioteca OpenMP.
- A paralelização foi feita baseada na diretiva de tasks. Tasks são blocos/seções de código que são criados para serem executados em algum momento por uma thread disponível. A ideia é que usamos a diretiva parallel para criar um pool de threads; a diretiva single para que apenas uma thread chame a função `queens()` e seja responsável por dar o empurrão inicial para começar a explorar a árvore de soluções; e a diretiva task, que cria um bloco de código contendo a nossa chamada recursiva como uma tarefa e adiciona ela automaticamente a uma "fila" para ser executada por alguma thread da pool criada.
- Como sabemos que as árvores de recursão de backtracking para um problema complexo, com tantas possíveis soluções como o das rainhas, é gigante, adicionamos uma lógica de limitação de criação dessas tasks: toda vez que fazemos uma chamada recursiva, verificamos em que profundidade dessa árvore estamos, baseado na coluna em qual estamos tentando alocar a rainha. Caso estivermos dentro do limite de profundidade definido pela constante `LEVEL`, criamos uma task para ela. Caso contrário, não criamos.

### Comparação

- Uma versão sequencial do mesmo código paralelo está presente no arquivo seq.cpp. Para testes e comparações de tempo e speedup deve-se compilar e executar a mesma como abaixo:
```
g++ seq.cpp -o sequencial -std=c++14

time ./sequencial <número  de  linhas/colunas  do  board>  <número  de  cavalos>
```