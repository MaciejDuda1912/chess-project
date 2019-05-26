#include <stdio.h>
#include <string.h>

void print_chessboard();
void fill_chessman();
void play(int x);
void moves(int p, int r, int s, int o);
int validate_move_format();

enum Color { WHITE, BLACK };
enum Type { PIONEK, SKOCZEK, GONIEC, HETMAN, WIEZA, KROL };
enum Dead_alive { DEAD, ALIVE };
int rowStart, rowEnd, colStart, colEnd;

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
int k, i, move;

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
	move=0;
	fill_chessman();

	do {

		print_chessboard();
		if (move%2==0)
			printf("Biale ");
		else
			printf("Czarne ");

		if(validate_move_format() == 0) { // tu warunkiem jest sprawdzanie poprawnosci wprowadzonej komendy
			printf("Invalid move!\n");
		}
		else{
			moves(rowStart,rowEnd,colStart,colEnd);
			move++;
		}

	
	} while (gra == 0);
	return 0;
}


int validate_move_format() {

	char command[99]; // za duzo, aby uniknac overflow
	int tempDigit; // uzywana do wyciagniecia cyfry z ciagu znakow

	printf("Enter your move\n"); // Schemat: [start row][start col] to [end row][end col]
	gets(command);
	
	if (strlen(command) != 8) { //sprawdza poprawna dlugosc wprowadzonej komendy
		return 0;
	}
	

	// zamiana liter na cyfry, aby mozna bylo ich uzywac jak indeksow

	if (command[0] == 'h')
		colStart = 0;
	else if (command[0] == 'g')
		colStart = 1;
	else if (command[0] == 'f')
		colStart = 2;
	else if (command[0] == 'e')
		colStart = 3;
	else if (command[0] == 'd')
		colStart = 4;
	else if (command[0] == 'c')
		colStart = 5;
	else if (command[0] == 'b')
		colStart = 6;
	else if (command[0] == 'a')
		colStart = 7;
	else {
		return 0;
	}

	if (command[6] == 'h')
		colEnd = 0;
	else if (command[6] == 'g')
		colEnd = 1;
	else if (command[6] == 'f')
		colEnd = 2;
	else if (command[6] == 'e')
		colEnd = 3;
	else if (command[6] == 'd')
		colEnd = 4;
	else if (command[6] == 'c')
		colEnd = 5;
	else if (command[6] == 'b')
		colEnd = 6;
	else if (command[6] == 'a')
		colEnd = 7;
	else {
		return 0;
	}

	tempDigit = command[1] - '0';
	rowStart = tempDigit - 1; //-1 poniewaz numeracja wierszy zaczyna sie od 0

	tempDigit = command[7] - '0';
	rowEnd = tempDigit - 1; //-1 poniewaz numeracja wierszy zaczyna sie od 0

	if (rowStart < 0 || rowStart > 7)
	{
		return 0;
	}
	if (rowEnd < 0 || rowEnd > 7)
	{
		return 0;
	}

	//DO TESTOW
	//printf("colStart: %d, colEnd: %d\n", colStart, colEnd);
	//printf("rowStart: %d, rowEnd: %d\n", rowStart, rowEnd);


	for (k = 0; k < 32; k++) {
		if (pieces[k].x == colStart && pieces[k].y == rowStart) {
			if ((pieces[k].color != WHITE && move%2==0)||(pieces[k].color!=BLACK && move%2==1) ){
				printf("Cannot move enemy pawn!	");
				return 0;
			}
		}
	}
	
	tempDigit=0;	
	for(k=0;k<32; k++){
		if (pieces[k].x == colStart && pieces[k].y == rowStart)
			tempDigit=1;
	}
	if (tempDigit==0)
	{
		printf("there's no pawn here. ");
		return 0;	
	}
	
	for (k = 0; k < 32; k++) {
		if (pieces[k].x == colEnd && pieces[k].y == rowEnd && ((pieces[k].color==WHITE && move%2==0) || (pieces[k].color==BLACK && move%2==1))) {
			printf("you have a pawn here. ");
			return 0;
		} 
	}
	
	return 1;
}

// FUNKCJA SPRAWDZAJACA LEGALOSC RUCHOW DLA POSZCZEGOLNYCH TYPOW PIONKOW
int validate_move()
{

}

void moves(p,r,s,o)
{

	// nadanie pionkom nowych wspolrzednych
	for (k = 0; k < 32; k++) {
		if (pieces[k].x == s && pieces[k].y == p) {
				pieces[k].x = o;
				pieces[k].y = r;
				for (i = 0; i < 32; i++) {
					if (pieces[k].x == pieces[i].x && pieces[k].y == pieces[i].y && k != i && pieces[k].color != pieces[i].color)
						pieces[i].dead_alive = DEAD;
					// usuwanie pionkow
				}
		}
	}
}
