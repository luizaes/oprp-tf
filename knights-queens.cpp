#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

using namespace std;

/* 
	Define o nível máximo para criação de tasks
	que serão executadas de forma paralela
*/ 
#define LEVEL 4

/* Define variáveis globais */
int m, n, k, lin, col;
int count_queens = 0;
char **final_board;

/* Preenche o tabuleiro */
void makeBoard(char** board)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = '_';
		}
	}
}

/* Funções para printar o tabuleiro */
void displayBoard(char** board)
{
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << "\t" << board[i][j] << " ";
		}
		cout << endl;
	}
}

void displayBoardCoordenatesMatrix(char** board)
{
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] != 'K') && (board[i][j] != 'Q')) {
				cout << "\t" << (i*m)+(j+1) << ";" ;
			} else {
				cout << "\t" << board[i][j] << ";" ;
			}
		}
		cout << endl;
	}
	cout << endl;
}

void displayResult(char** board)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'K') {
				cout << "K" << (i*m)+(j+1) << ";" ;
			}
			if (board[i][j] == 'Q') {
				cout << "Q" << (i*m)+(j+1) << ";" ;
			}
		}
	}
	cout << endl;
}

void displayBoardCoordenates(char** board)
{
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] == 'K') || (board[i][j] == 'Q')) {
				cout << (i*m)+(j+1) << ";" ;
			}
		}
	}
	cout << endl;
}

/* 
	Função responsável por marcar as posições de 
	ataque de um cavalo no tabuleiro
*/
void attack(int i, int j, char a, char** board)
{

	if ((i + 2) < m && (j - 1) >= 0) {
		board[i + 2][j - 1] = a;
	}
	if ((i - 2) >= 0 && (j - 1) >= 0) {
		board[i - 2][j - 1] = a;
	}
	if ((i + 2) < m && (j + 1) < n) {
		board[i + 2][j + 1] = a;
	}
	if ((i - 2) >= 0 && (j + 1) < n) {
		board[i - 2][j + 1] = a;
	}
	if ((i + 1) < m && (j + 2) < n) {
		board[i + 1][j + 2] = a;
	}
	if ((i - 1) >= 0 && (j + 2) < n) {
		board[i - 1][j + 2] = a;
	}
	if ((i + 1) < m && (j - 2) >= 0) {
		board[i + 1][j - 2] = a;
	}
	if ((i - 1) >= 0 && (j - 2) >= 0) {
		board[i - 1][j - 2] = a;
	}
}

/* 
	Função que verifica se é possível posicionar uma 
	rainha na célula especificada
*/
int attackqueens(int oi, int oj, char** board)
{
	int i,j;

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal cima/esquerda
	while ((i > 0) && (j > 0)) {
		if (board[i-1][j-1] == 'K' || board[i-1][j-1] == 'Q') {
			return 1;
		}
		i--;
		j--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições em cima
	while (i > 0) {
		if (board[i-1][j] == 'Q' || board[i-1][j] == 'K') {
			
			return 1;
		}
		i--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal cima/direita
	while ((i > 0) && (j < n)) {
		if (board[i-1][j+1] == 'Q' || board[i-1][j+1] == 'K') {
			return 1;
		}
		i--;
		j++;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na esquerda
	while (j > 0) {
		if (board[i][j-1] == 'Q' || board[i][j-1] == 'K') {
			return 1;
		}
		j--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na direita
	while (j+1 < n) {
		if (board[i][j+1] == 'Q' || board[i][j+1] == 'K') {
			return 1;
		}
		j++;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal baixo/esquerda
	while ((i+1 < m) && (j > 0)) {
		if (board[i+1][j-1] == 'Q' || board[i+1][j-1] == 'K') {
			return 1;
		}
		i++;
		j--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições pra baixo
	while (i+1 < m) {
		if (board[i+1][j] == 'Q' || board[i+1][j] == 'K') {
			return 1;
		}
		i++;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal baixo/direita
	while ((i+1 < m) && (j+1 < n)) {
		if (board[i+1][j+1] == 'Q' || board[i+1][j+1] == 'K') {
			return(1);
		}
		i++;
		j++;
	}

	return 0;
}

/* Verificar se a posição no tabuleiro está disponível */
bool canPlace(int i, int j, char** board)
{
	if (board[i][j] == '_')
		return true;
	else
		return false;
}

/* 
	Para cavalos, posiciona eles no tabuleiro e marca seus ataques
	Para rainhas, verifica se é possível posicioná-las
*/
int place(int i, int j, char k, char a, char** board)
{
	if (k == 'K') {
		board[i][j] = k;
		attack(i, j, a, board);
	} else {
		return(attackqueens(i, j, board));
	}
	return 0;
}

/*
	Função que verifica se um caminho da árvore de recursão
	já chegou em uma solução válida, e salva ela caso seja
	a melhor encontrada até então
*/
int foundSolution(int quj, char** board, int local_queens) {
	if(quj == m) {
		// Lock pra região crítica com escrita nas variáveis globais count_queens e final_board
		#pragma omp critical 
		{
			if(local_queens > count_queens) {
				count_queens = local_queens;

				for(int i = 0; i < m; i++) {
					for(int j = 0; j < n; j++) {
						final_board[i][j] = board[i][j];
					}
				}
			}
		}
		return 1;
	}

	return 0;
}

/*
	Função que cuida do posicionamento das rainhas
*/
void queens (int qui, int quj, char ** board, int qtd_rainhas) {

	if((qtd_rainhas + m - quj) <= count_queens)
		return;

	if(foundSolution(quj, board, qtd_rainhas))
		return;

	for(int i = qui; i < n; i++) {
		if (canPlace(i, quj, board)) {
			if (!place(i, quj, 'Q', 'a', board)) {
				board[i][quj] = 'Q';
				if (quj-col < LEVEL) {
		        	char** new_board = new char*[m];
					for (int x = 0; x < m; x++) {
						new_board[x] = new char[n];
					}

					for (int y = 0; y < m; y++) {
						for (int z = 0; z < n; z++) {
							new_board[y][z] = board[y][z];
						}
					}
					#pragma omp task 
					{
		        		queens(lin, quj+1, new_board, qtd_rainhas+1);
		        	}
		        	board[i][quj] = '_';
		      	} else {
		      		queens(lin, quj+1, board, qtd_rainhas+1);
		      		board[i][quj] = '_';
		      	}
			}
		}
	}

	if (quj-col < LEVEL) {
    	char** new_board = new char*[m];
		for (int x = 0; x < m; x++) {
			new_board[x] = new char[n];
		}

		for (int y = 0; y < m; y++) {
			for (int z = 0; z < n; z++) {
				new_board[y][z] = board[y][z];
			}
		}
		#pragma omp task 
		{
    		queens(lin, quj+1, new_board, qtd_rainhas);
    	}
  	} else {
  		queens(lin, quj+1, board, qtd_rainhas);
  	}
}

/* 
	Função responsável por posicionar os k cavalos
	no tabuleiro
*/
void kkn(int k, char** board)
{

	int max = k/m;
	int total_max = (k%m > 0) ? max+1 : max;
	bool stop = false;

	if(total_max + (total_max-1)*2 > m){
		cout << "It's not possible to position this number of knights in the board" << endl;
		exit(1);
	}

	lin = col = 0;

	for (int i = 0; i < m && !stop; i++) {
		for (int j = 0; j < n && !stop; j++) {
			if(k == 0) {
				stop = true;
			} else {
				if (canPlace(i, j, board)) {
					place(i, j, 'K', 'A', board);
					if(j >= col) {
						col = j+1;
						lin = i+1;
					}
					k--;
				}
			}
		}
	}

	if(k == 0) {
		for(int x = 0; x < m; x++) {
			for(int y = 0; y < n; y++) {
				final_board[x][y] = board[x][y];
			}
		}
		#pragma omp parallel
		{
		 	#pragma omp single 
		 	{
				queens(lin, col, board, 0);
		 	}	
		}

		cout << endl << "Final board:" << endl;
		displayBoardCoordenatesMatrix(final_board);
		cout << "Positions:" << endl;
		displayResult(final_board);

		cout << endl << "All the knights were placed" << endl;
		cout<< "Total number of queens placed: " << count_queens << endl;

		for (int x = 0; x < m; x++) {
			delete[] board[x];
		}
		delete[] board;

		for (int x = 0; x < m; x++) {
			delete[] final_board[x];
		}
		delete[] final_board;

		exit(1);
	}
}

/* Função main */
int main( int argc, char *argv[])
{
	if (argc <= 2 ) {
		printf("./knights-queens <linha_tabuleiro> <nro_cavalos>\n");
		return -1;
	}

	m = atoi(argv[1]);
	n = m;
	k = atoi(argv[2]);

	// Cria os tabuleiros
	char** board = new char*[m];
	for (int i = 0; i < m; i++) {
		board[i] = new char[n];
	}

	final_board = new char*[m];
	for (int i = 0; i < m; i++) {
		final_board[i] = new char[n];
	}	

	makeBoard(board);

	kkn(k, board);

	return 0;
}