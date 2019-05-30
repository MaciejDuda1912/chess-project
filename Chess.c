#include <stdio.h>
#include <string.h>

void print_chessboard();
void fill_chessman();
void moves(int p, int r, int s, int o);
int validate_move_format();
int validate_move(rowStart, rowEnd, colStart, colEnd);

enum Color { WHITE, BLACK };
enum Type { PAWN, KNIGHT, BISHOP, QUEEN, ROOK, KING };
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
		pieces[k] = (chessman) { WHITE, PAWN, 'O', k , 1 };
	for (k = 16; k < 24; k++)
		pieces[k] = (chessman) { BLACK, PAWN, 'o', k - 16, 6 };
	for (k = 8; k < 10; k++)
		pieces[k] = (chessman) { WHITE, ROOK, 'R', (k - 8) * 7, 0 };
	for (k = 10; k < 12; k++)
		pieces[k] = (chessman) { WHITE, KNIGHT, 'N', -49 + k * 5, 0 };
	for (k = 12; k < 14; k++)
		pieces[k] = (chessman) { WHITE, BISHOP, 'B', k * 3 - 34, 0 };
	pieces[14] = (chessman) { WHITE, QUEEN, 'Q', 4, 0 };
	pieces[15] = (chessman) { WHITE, KING, 'K', 3, 0 };
	for (k = 24; k < 26; k++)
		pieces[k] = (chessman) { BLACK, ROOK, 'r', (k - 24) * 7, 7 };
	for (k = 26; k < 28; k++)
		pieces[k] = (chessman) { BLACK, KNIGHT, 'n', k * 5 - 129, 7 };
	for (k = 28; k < 30; k++)
		pieces[k] = (chessman) { BLACK, BISHOP, 'b', k * 3 - 82, 7 };
	pieces[30] = (chessman) { BLACK, QUEEN, 'q', 4, 7 };
	pieces[31] = (chessman) { BLACK, KING, 'k', 3, 7 };
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
			if ((pieces[k].color != WHITE && move % 2 == 0) || (pieces[k].color != BLACK && move % 2 == 1)){
				printf("Cannot move enemy pawn!	");
				return 0;
			}
		}
	}

	tempDigit = 0;
	for (k = 0; k < 32; k++) {
		if (pieces[k].x == colStart && pieces[k].y == rowStart)
			tempDigit = 1;
	}
	if (tempDigit == 0)
	{
		printf("There's no pawn here. ");
		return 0;
	}

	for (k = 0; k < 32; k++) {
		if (pieces[k].x == colEnd && pieces[k].y == rowEnd && ((pieces[k].color == WHITE && move % 2 == 0) || (pieces[k].color == BLACK && move % 2 == 1))) {
			printf("You have a pawn there. ");
			return 0;
		}
	}

	return 1;
}

// FUNKCJA SPRAWDZAJACA LEGALOSC RUCHOW DLA POSZCZEGOLNYCH TYPOW PIONKOW
int validate_move(int rowStart, int rowEnd, int colStart, int colEnd)
{
	//wektory Y i X
	int j;
	int rowDiff = rowStart - rowEnd;
	int colDiff = colStart - colEnd;
	
	if (rowDiff==0 && colDiff==0)
	{
		printf("you didn't move");
		return 0;
	 } 

	/*
	//Do testow
	printf("rowDiff: %d \n", rowDiff);
	printf("colDiff: %d \n", colDiff);
	*/
	
	// Petla dla sprawdzenia typu bierki, ktora chcemy wykonac ruch
	for (k = 0; k < 32; ++k)
	{
		//PIONKI
		if ((pieces[k].y == rowStart && pieces[k].x == colStart) && pieces[k].type == PAWN && pieces[k].dead_alive==ALIVE) 
		{
			//Sprwdzenie ilosci pol, o ktore chcemy sie ruszyc
			if ((rowStart != 1 && rowStart != 6) && abs(rowDiff) > 1) {
				printf("Pawns cannot move more than one space except the first move.\n");
				return 0;
			}
			else if ((rowStart == 1 || rowStart == 6) && abs(rowDiff) > 2) {
				printf("Pawns can move up to two spaces in their first move.\n");
				return 0;
			}
			//Wykluczenie ruchow do tylu
			if ((pieces[k].color == BLACK) && rowDiff < 0) {
				printf("Pawns cannot move backwards.\n");
				return 0;
			}
			else if ((pieces[k].color == WHITE) && rowDiff > 0) {
				printf("Pawns cannot move backwards.\n");
				return 0;
			}

			//sprawdzanie, czy pionek nie wejdzie w inna figure
			if (colDiff == 0) {
				for (i = 0; i < 32; ++i) {
					if (pieces[i].y == rowEnd && pieces[i].x == colEnd && pieces[i].dead_alive==ALIVE){
						printf("Pawns do not move like that \n");
						return 0;
					}
				}
			}
			
			//Sprawdzanie, czy pionek moze wykonac ruch po przek1tnej/w bok
			if (colDiff != 0) {
				for (i = 0; i < 32; ++i) {
					if ((pieces[i].x == colEnd && pieces[i].y == rowEnd) && rowDiff != 0) {
						return 1;
					}
				}
				printf("Pawns do not move like that \n");
				return 0;
			}
		}
		
		//Wieï¿½e
		else if ((pieces[k].y == rowStart && pieces[k].x == colStart) && pieces[k].type == ROOK && pieces[k].dead_alive==ALIVE)
		{
			if (rowDiff!=0 && colDiff!=0)
			{
				printf("rooks don't move like that. \n");
				return 0;
			}
			if (rowDiff==0)
			{
				if( colDiff>0)
				{
					for( j=1; j<abs(colDiff); j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x==colStart-j && pieces[i].y==rowStart && pieces[i].dead_alive==ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
				else
				{
					for( j=1;j<abs(colDiff);j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x==colStart+j && pieces[i].y==rowStart && pieces[i].dead_alive==ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
			}
			else
			{
				if( rowDiff>0)
				{
					for( j=1;j<abs(rowDiff);j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x==colStart && pieces[i].y==rowStart-j && pieces[i].dead_alive==ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
				else
				{
					for( j=1;j<abs(rowDiff);j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x == colStart && pieces[i].y==rowStart + j && pieces[i].dead_alive == ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
			}
		}
		//skoczki
		else if ((pieces[k].y == rowStart && pieces[k].x == colStart) && pieces[k].type == KNIGHT && pieces[k].dead_alive==ALIVE)
		{
			if (abs(colDiff*rowDiff) != 2)
			{
				printf("Knights do not move like that\n");
				return 0;
			}	
		}
		
		//goñce
		else if ((pieces[k].y == rowStart && pieces[k].x == colStart) && pieces[k].type == BISHOP && pieces[k].dead_alive==ALIVE)
		{
			if (abs(colDiff/rowDiff) != 1)
			{
				printf("Bishops do not move like that\n");
				return 0;
			}
			for (i = 1 ; i < abs(colDiff) ;i++)
			{
				for (j = 0; j < 32; j++)
				{
					if (colDiff>0 && rowDiff>0 && pieces[j].x==colStart-i && pieces[j].y==rowStart-i)
					{
						printf("there is a piece in the way");
						return 0;
					}
					else if (colDiff>0 && rowDiff<0 && pieces[j].x==colStart-i && pieces[j].y==rowStart+i)
					{
						printf("there is a piece in the way");
						return 0;
					}
					else if (colDiff<0 && rowDiff>0 && pieces[j].x==colStart+i && pieces[j].y==rowStart-i)
					{
						printf("there is a piece in the way");
						return 0;
					}
					else if (colDiff<0 && rowDiff<0 && pieces[j].x==colStart+i && pieces[j].y==rowStart+i)
					{
						printf("there is a piece in the way");
						return 0;
					}
				}
			}
		}
		
		// Krole
		else if ((pieces[k].y == rowStart && pieces[k].x == colStart) && pieces[k].type == KING && pieces[k].dead_alive==ALIVE)
		{
			if( abs(rowDiff)>1 || abs(colDiff)>1)
			{
				printf("king does not  move like that ");
				return 0;
		}
		
		// hetman
		else if ((pieces[k].y == rowStart && pieces[k].x == colStart) && pieces[k].type == QUEEN && pieces[k].dead_alive==ALIVE)
		{
			if (abs(colDiff/rowDiff) != 1 && rowDiff !=0 && colDiff!=0)
			{
				printf("Queen does not move like that");
				return 0;
			}
			else if (abs(colDiff/rowDiff) == 1)
			{
				for (i = 1 ; i < abs(colDiff) ;i++)
				{
					for (j = 0; j < 32; j++)
					{
						if (colDiff>0 && rowDiff>0 && pieces[j].x==colStart-i && pieces[j].y==rowStart-i)
						{
							printf("there is a piece in the way");
							return 0;
						}
						else if (colDiff>0 && rowDiff<0 && pieces[j].x==colStart-i && pieces[j].y==rowStart+i)
						{
							printf("there is a piece in the way");
							return 0;
						}
						else if (colDiff<0 && rowDiff>0 && pieces[j].x==colStart+i && pieces[j].y==rowStart-i)
						{
							printf("there is a piece in the way");
							return 0;
						}
						else if (colDiff<0 && rowDiff<0 && pieces[j].x==colStart+i && pieces[j].y==rowStart+i)
						{
							printf("there is a piece in the way");
							return 0;
						}
					}
				}
			}
			else
			{
				if (rowDiff==0)
			{
				if( colDiff>0)
				{
					for( j=1; j<abs(colDiff); j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x==colStart-j && pieces[i].y==rowStart && pieces[i].dead_alive==ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
				else
				{
					for( j=1;j<abs(colDiff);j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x==colStart+j && pieces[i].y==rowStart && pieces[i].dead_alive==ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
			}
			else
			{
				if( rowDiff>0)
				{
					for( j=1;j<abs(rowDiff);j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x==colStart && pieces[i].y==rowStart-j && pieces[i].dead_alive==ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
				else
				{
					for( j=1;j<abs(rowDiff);j++)
					{
						for (i=0;i<32;i++)
						{
							if (pieces[i].x == colStart && pieces[i].y==rowStart + j && pieces[i].dead_alive == ALIVE)
								{
									printf("there is a piece in the way \n");
									return 0;
								}
						}
					}
				}
			}
		}	
		/*
			//DO TESTOW
			printf("colStart: %d, colEnd: %d\n", colStart, colEnd);
			printf("pieces[k].x: %d \n", pieces[k].x);
			printf("rowStart: %d, rowEnd: %d\n", rowStart, rowEnd);
			printf("pieces[k].y: %d \n", pieces[k].y);
			*/


	}

	return 1;
}

void moves(p, r, s, o)
{
	int row_for_killed;

	// nadanie pionkom nowych wspolrzednych
	for (k = 0; k < 32; k++) {
		if (pieces[k].x == s && pieces[k].y == p) {
			pieces[k].x = o;
			pieces[k].y = r;

			for (i = 0; i < 32; i++) {
				if (pieces[k].x == pieces[i].x && pieces[k].y == pieces[i].y && k != i && pieces[k].color != pieces[i].color) {
					pieces[i].dead_alive = DEAD;
					printf("Enemy piece captured! \n");

					if (pieces[i].color == WHITE) {
						row_for_killed = 0;
					}
					else {
						row_for_killed = 1;
					}
					pieces[i].x = i + 10;
					pieces[i].y = row_for_killed + 10;

					// usuwanie pionkow (nowe wspolrzedne, aby nie zaklocac dalszej gry)
				}
			}
		}
	}

	
}
int main() {
	int gra = 0;
	move = 0;
	fill_chessman();

	do {

		print_chessboard();
		if (move % 2 == 0)
			printf("White's ");
		else
			printf("Black's ");

		if (validate_move_format() == 0) { // tu warunkiem jest sprawdzanie poprawnosci wprowadzonej komendy
			printf("Invalid move!\n");
		}
		else if (validate_move(rowStart, rowEnd, colStart, colEnd) == 0) {
			printf("Invalid move!\n");
		}
		else {
			moves(rowStart, rowEnd, colStart, colEnd);
			move++;
		}

	} while (gra == 0);
	return 0 ;
}
