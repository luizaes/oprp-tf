// C++ implementation of the above approach
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
using namespace std;

#define LEVEL 4
//http://mathworld.wolfram.com/KnightsProblem.html

/* m*n is the board dimension
k is the number of knights to be placed on board
countKnights is the number of possible solutions */
int m, n, k, lin, col;
int count_queens = 0;
char **final_board;

/* This function is used to create an empty m*n board */
void makeBoard(char** board)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = '_';
		}
	}
}

/* This function displays our board */
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

/* This function displays our board */
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

/* This function displays our board */
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


/* This function displays our board */
void displayBoardCoordenates(char** board)
{
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] == 'K') || (board[i][j] == 'Q')) {
				//cout << m << board[i][j] << i << j << (i*m)+(j+1) << ";" ;
				cout << (i*m)+(j+1) << ";" ;
			}
		}
	}
	cout << endl;
}



/* This function marks all the attacking
position of a knight placed at board[i][j]
position */
void attack(int i, int j, char a,
	char** board)
	{

		/* conditions to ensure that the
		block to be checked is inside the boardvoid displayBoardCoordenatesMatrix(char** board, char a) */
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

int attackqueens(int oi, int oj, char a,
char** board)
{
	int i,j;

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal cima/esquerda
	while ((i > 0) && (j > 0)) {
		//if ((board[i-1][j-1] != 'K') || (board[i-1][j-1] != 'A') || (board[i-1][j-1] != 'Q') || (board[i-1][j-1] != 'q')){
			//board[i-1][j-1] = a;
			if ((board[i-1][j-1] == 'K') || (board[i-1][j-1] == 'Q') || (board[i-1][j-1] == 'q')) {
				//cout << "Diagonal cima esquerda inválida" << endl;
				return(1);
			}
		//}
		i--;
		j--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições em cima
	while (i > 0) {
		if (board[i-1][j] == 'Q') {
			// cout << "Cima inválida" << endl;
			return(1);
		}
		if (board[i-1][j] == 'K') {
			// cout << "Cima inválida" << endl;
			return(1);
		}
		i--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal cima/direita
	while ((i > 0) && (j < n)) {
		if (board[i-1][j+1] == 'Q') {
			// cout << "Diagonal cima direita inválida" << endl;
			return(1);
		}
		if (board[i-1][j+1] == 'K') {
			// cout << "Diagonal cima direita inválida" << endl;
			return(1);
		}
		i--;
		j++;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na esquerda
	while (j > 0) {
		if (board[i][j-1] == 'Q') {
			// cout << "Esquerda inválida" << endl;
			return(1);
		}
		if (board[i][j-1] == 'K') {
			// cout << "Esquerda inválida" << endl;
			return(1);
		}
		j--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na direita
	while (j+1 < n) {
		if (board[i][j+1] == 'Q') {
			// cout << "Direita inválida" << endl;
			return(1);
		}
		if (board[i][j+1] == 'K') {
			// cout << "Direita inválida" << endl;
			return(1);
		}
		j++;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal baixo/esquerda
	while ((i+1 < m) && (j > 0)) {
		if (board[i+1][j-1] == 'Q') {
			// cout << "Diagonal baixo esquerda inválida" << endl;
			return(1);
		}
		if (board[i+1][j-1] == 'K') {
			// cout << "Diagonal baixo esquerda inválida" << endl;
			return(1);
		}
		i++;
		j--;
	}

	i = oi;
	j = oj;
	// Olha todas as posições pra baixo
	while (i+1 < m) {
		if (board[i+1][j] == 'Q') {
			// cout << "Baixo inválida" << endl;
			return(1);
		}
		if (board[i+1][j] == 'K') {
			// cout << "Baixo inválida" << endl;
			return(1);
		}
		i++;
	}

	i = oi;
	j = oj;
	// Olha todas as posições na diagonal baixo/direita
	while ((i+1 < m) && (j+1 < n)) {
		if (board[i+1][j+1] == 'Q') {
			// cout << "Diagonal baixo direita inválida" << endl;
			return(1);
		}
		if (board[i+1][j+1] == 'K') {
			// cout << "Diagonal baixo direita inválida" << endl;
			return(1);
		}
		i++;
		j++;
	}
	return(0);
}


/* If the position is empty,
place the knight */
bool canPlace(int i, int j, char** board)
{
	if (board[i][j] == '_')
		return true;
	else
		return false;
}

/* Place the knight at [i][j] position
on board */
int place(int i, int j, char k, char a,
char** board)
{
	/* Copy the configurations of
	old board to new board */
	// for (int y = 0; y < m; y++) {
	// 	for (int z = 0; z < n; z++) {
	// 		new_board[y][z] = board[y][z];
	// 		//printf("%d%d %c\n", y, z, new_board[y][z]);
	// 	}
	// }

	/* Place the knight at [i][j]
	position on new board */
	//displayBoard(new_board);
	//printf("%c(%d%d)", new_board[i][j], i, j);

	/* Mark all the attacking positions
	of newly placed knight on the new board */
	if (k == 'K') {
		board[i][j] = k;
		attack(i, j, a, board);
	} else {
		return(attackqueens(i, j, a, board));
	}
	return (0);
}

void queens_seq (int qui, int quj, char ** board) {

	if(quj == m) {
		int local_queens = 0;
		for (int i = lin; i < m; i++) {
			for (int j = col; j < n; j++) {
				if (board[i][j] == 'Q') {
					local_queens++;
				}
			}
		}
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
	}

	for(int i = qui; i < n; i++) {
		if (canPlace(i, quj, board)) {
			/* Create a a new board and place the
			new queen on it */
			if (!place(i, quj, 'Q', 'a', board)) {
				//cout << "Coloquei rainha na pos " << i << " " << quj << endl;
				board[i][quj] = 'Q';
	      		queens_seq(lin, quj+1, board);
	      		board[i][quj] = '_';
			}
			//displayBoard(board);
		}
	}
}


void queens (int qui, int quj, char ** board) {

	bool placed = false;

	if(quj == m) {
		int local_queens = 0;
		for (int i = lin; i < m; i++) {
			for (int j = col; j < n; j++) {
				if (board[i][j] == 'Q') {
					local_queens++;
				}
			}
		}

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
	}

	for(int i = qui; i < n; i++) {
		if (canPlace(i, quj, board)) {
			/* Create a a new board and place the
			new queen on it */
			if (!place(i, quj, 'Q', 'a', board)) {
				//cout << "Coloquei rainha na pos " << i << " " << quj << endl;
				board[i][quj] = 'Q';
				placed = true;
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
						//cout << omp_get_thread_num() << endl;
		        		queens(lin, quj+1, new_board);
		        	}
		        	board[i][quj] = '_';
		      	} else {
		      		queens_seq(lin, quj+1, board);
		      		board[i][quj] = '_';
		      	}
			}
		}
	}

	if(!placed) {
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
				//cout << omp_get_thread_num() << endl;
        		queens(lin, quj+1, new_board);
        	}
      	} else {
      		queens_seq(lin, quj+1, board);
      	}
	}
}

/* Function for placing knights on board
such that they don't attack each other */
void kkn(int k, char** board)
{

	int max = k/m;
	int total_max = (k%m > 0) ? max+1 : max;

	if(total_max + (total_max-1)*2 > m){
		cout << "It's not possible to position this number of knights in the board" << endl;
		exit(1);
	}

	lin = col = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if(k == 0) {
				// for(int k = col; k < m; k++) {
				// 	board[i][k] = 'Q';
				// }
				for(int x = 0; x < m; x++) {
					for(int y = 0; y < n; y++) {
						final_board[x][y] = board[x][y];
					}
				}
				#pragma omp parallel
				{
				 	#pragma omp single
					queens(lin, col, board);
				}
				for (int i = lin; i < m; i++) {
					for (int j = col; j < n; j++) {
						if (final_board[i][j] == 'Q') {
							if(attackqueens(i, j, 'a', final_board)) {
								cout << "Algo tá errado!!!" << endl;
								cout << i << " " << j << endl;
							}
						}
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
			} else {
				/* Is it possible to place knight at [i][j] position on board? */
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
}

// Driver code
int main( int argc, char *argv[])
{
	//m = 4, n = 3, k = 6;
	//	k = 7;

	if (argc <= 2 ) {
		printf("./knights-queens <linha_tabuleiro> <nro_cavalos>\n");
		return -1;
	}

	m = atoi(argv[1]);
	n = m;
	k = atoi(argv[2]);

	/* Creation of a m*n board */
	char** board = new char*[m];
	for (int i = 0; i < m; i++) {
		board[i] = new char[n];
	}

	final_board = new char*[m];
	for (int i = 0; i < m; i++) {
		final_board[i] = new char[n];
	}	

	/* Make all the places are empty */
	makeBoard(board);
	//displayBoard(board);

	kkn(k, board);

	return 0;
}