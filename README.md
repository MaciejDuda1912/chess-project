#include<stdio.h>
#include <string.h>

void print_chessboard();
void fill_chessboard();
void fill_chessman();
void play(int x);

enum Color { WHITE, BLACK };
enum Type { PIONEK, SKOCZEK, GONIEC, HETMAN, WIEZA, KROL };
enum Dead_alive { DEAD, ALIVE };

typedef struct
{
	enum Color color;
	enum Type type;
	char symbol;
	int x;
	int y;
	enum Dead_alive dead_alive;
}chessman;

chessman pieces[32];
int k, i;

void fill_chessman() {

	for (k = 0; k < 8; k++)
		pieces[k] = (chessman) { WHITE, PIONEK, 'P', k, 1 };
	for (k = 16; k < 24; k++)
		pieces[k] = (chessman) { BLACK, PIONEK, 'p', k - 16, 6 };
	for (k = 8; k < 10; k++)
		pieces[k] = (chessman) { WHITE, WIEZA, 'W', (k - 8) * 7, 0 };
	for (k = 10; k < 12; k++)
		pieces[k] = (chessman) { WHITE, SKOCZEK, 'S', -49 + k * 5, 0 };
	for (k = 12; k < 14; k++)
		pieces[k] = (chessman) { WHITE, GONIEC, 'G', k * 3 - 34, 0 };
	pieces[14] = (chessman) { WHITE, HETMAN, 'H', 4, 0 };
	pieces[15] = (chessman) { WHITE, KROL, 'K', 3, 0 };
	for (k = 24; k < 26; k++)
		pieces[k] = (chessman) { BLACK, WIEZA, 'w', (k - 24) * 7, 7 };
	for (k = 26; k < 28; k++)
		pieces[k] = (chessman) { BLACK, SKOCZEK, 's', k * 5 - 129, 7 };
	for (k = 28; k < 30; k++)
		pieces[k] = (chessman) { BLACK, GONIEC, 'g', k * 3 - 82, 7 };
	pieces[30] = (chessman) { BLACK, HETMAN, 'h', 4, 7 };
	pieces[31] = (chessman) { BLACK, KROL, 'k', 3, 7 };
	for (k = 0; k < 32; k++)
		pieces[k].dead_alive = ALIVE;
}
void print_chessboard() {
	int i, j, k;
	int flag = 0;

	//system("cls"); // czyszczenie konsoli

	for (i = 0; i < 8; i++)
	{
		printf("%d", i + 1);
		for (j = 0; j < 8; j++) {
			printf("[");
			flag = 0;
			for (k = 0; k < 32; k++) {
				if (pieces[k].x == j && pieces[k].y == i && pieces[k].dead_alive == ALIVE) {
					printf("%c", pieces[k].symbol);
					flag = 1;
				}
			}
			if (flag == 0)
				printf(" ");
			printf("]");
		}
		printf("\n");
	}
	printf("  h  g  f  e  d  c  b  a\n");
}
void play(int x) {
}
int main() {
	int gra = 0;
	fill_chessman();
	do{
	
		print_chessboard();
		move();
	}while ( gra==0);
	return 0;
}

//FUNKCJA TESTOWA, OBECNIE NIE U—YWANA !!!!!!!

int UpdateChessboard(int colStart, int rowStart, int colEnd, int rowEnd) {
	int i;
	int j;
	int flag;

	system("cls"); // czyszczenie konsoli

	//printf("col start %d, row start %d \n \n", colStart, rowStart);

	for (k = 0; k < 32; k++) {
		if (pieces[k].x == colStart && pieces[k].y == rowStart) {
			pieces[k].x = colEnd;
			pieces[k].y = rowEnd;
		}
	}

	for (i = 0; i < 8; i++)
	{
		printf("%d", i + 1);
		for (j = 0; j < 8; j++) {
			printf("[");
			flag = 0;
			for (k = 0; k < 32; k++){
				if (pieces[k].x == j && pieces[k].y == i && pieces[k].dead_alive == ALIVE) {

					printf("%c", pieces[k].symbol);
					//printf(", %d", pieces[k].y);
					flag = 1;
				}
			}
			if (flag == 0)
				printf(" ");
			printf("]");
		}
		printf("\n");

	}
	printf("  h  g  f  e  d  c  b  a\n");
}


int move() {

	char move[9]; // 8 znaków + znak konca listy
	int rowStart, rowEnd, colStart, colEnd;
	int tempDigit; // u?ywana do wyci1gniecia cyfry z ci1gu znaków

	printf("Enter your move\n"); // Schemat: [start row][start col] to [end row][end col]
	gets(move);


	/*
	NIE DZIALA, funkcja sprawdzaj1ca poprawnooa wprowadzonej komendy
	if (strlen(move != 9)) {
		printf("Unknown command");
		return 0;
	}
	*/


	// zamiana liter na cyfry, aby mo?na by3o ich u?ywaa jak indeksów

	if (move[0] == 'h')
		colStart = 0;
	else if (move[0] == 'g')
		colStart = 1;
	else if (move[0] == 'f')
		colStart = 2;
	else if (move[0] == 'e')
		colStart = 3;
	else if (move[0] == 'd')
		colStart = 4;
	else if (move[0] == 'c')
		colStart = 5;
	else if (move[0] == 'b')
		colStart = 6;
	else if (move[6] == 'a')
		colStart = 7;

	if (move[6] == 'h')
		colEnd = 0;
	else if (move[6] == 'g')
		colEnd = 1;
	else if (move[6] == 'f')
		colEnd = 2;
	else if (move[6] == 'e')
		colEnd = 3;
	else if (move[6] == 'd')
		colEnd = 4;
	else if (move[6] == 'c')
		colEnd = 5;
	else if (move[6] == 'b')
		colEnd = 6;
	else if (move[6] == 'a')
		colEnd = 7;

	tempDigit = move[1] - '0';
	rowStart = tempDigit - 1; //-1 poniewa? numeracja wierszy zaczyna sie od 0

	tempDigit = move[7] - '0';
	rowEnd = tempDigit - 1; //-1 poniewa? numeracja wierszy zaczyna sie od 0


	// nadanie pionkom nowych wspó3rzednych
	for (k = 0; k < 32; k++) {
		if (pieces[k].x == colStart && pieces[k].y == rowStart) {
			pieces[k].x = colEnd;
			pieces[k].y = rowEnd;
			for (i=0; i<32;i++){
				if (pieces[k].x==pieces[i].x && pieces[k].y==pieces[i].y && k!=i)
				pieces[i].dead_alive=DEAD;
				// usuwanie pionków
			}
		}
	}
} 
