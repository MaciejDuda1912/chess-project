#include <stdio.h>
#include <string.h>

void print_chessboard();
void fill_chessboard(); // nie ma takiej funkcji
void fill_chessman();
void play(int x);
int move(enum Color);

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
	enum Color enum_color = BLACK;
	char str_color[5]; //uzywana do wyswietlenia koloru gracza podczas jego tury

	do {

		if (enum_color == BLACK) {
			enum_color = WHITE;
			strcpy_s(str_color, 6, "White"); // funkcja przypisujaca zmiennej str_color wartosc
		}
		else {
			enum_color = BLACK;
			strcpy_s(str_color, 6, "Black"); // funkcja przypisujaca zmiennej str_color wartosc
		}
		 
		printf("%s's turn\n\n", str_color);
		print_chessboard();

		while(validate_move_format(enum_color) == 0) { // tu warunkiem jest sprawdzanie poprawnosci wprowadzonej komendy
			printf("Invalid move!\n");
		}
	
	} while (gra == 0);
	return 0;
}


int validate_move_format(enum_color) {

	char command[99]; // za duzo, aby uniknac overflow
	int rowStart, rowEnd, colStart, colEnd;
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
			if (pieces[k].color != enum_color) {
				printf("Cannot move enemy pawn!	");
				return 0;
			}
		}
	}


	move(rowStart, rowEnd, colStart, colEnd); // W przyszlosci zastapione przez odwolanie do funkcji validate_move()

	return 1;
}

// FUNKCJA SPRAWDZAJACA LEGALOSC RUCHOW DLA POSZCZEGOLNYCH TYPOW PIONKOW
int validate_move()
{

}

int move(row_start, row_end, col_start, col_end)
{

	// nadanie pionkom nowych wspolrzednych
	for (k = 0; k < 32; k++) {
		if (pieces[k].x == col_start && pieces[k].y == row_start) {
				pieces[k].x = col_end;
				pieces[k].y = row_end;
				for (i = 0; i < 32; i++) {
					if (pieces[k].x == pieces[i].x && pieces[k].y == pieces[i].y && k != i && pieces[k].color != pieces[i].color)
						pieces[i].dead_alive = DEAD;
					// usuwanie pionkow
				}
		}
	}
}