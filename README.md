#include<stdio.h>
void print_chessboard();
void fill_chessboard();
void fill_chessman();
	
enum Color{WHITE,BLACK};
enum Type{PIONEK,SKOCZEK,GONIEC,HETMAN,WIEZA,KROL};
typedef struct 
{
	enum Color color;
	enum Type type;
	char symbol;
}chessman;

chessman pieces[32];
int k, j;
void fill_chessman(){
	for  (k=0; k<8;k++)
		pieces[k]=(chessman){WHITE,PIONEK,"P"};
	for  (k=16; k<24;k++)
		pieces[k]=(chessman){BLACK,PIONEK,"p"};
	for (k=8; k<10;k++)
		pieces[k]=(chessman){WHITE,WIEZA,"W"};
	for (k=10; k<12;k++)
		pieces[k]=(chessman){WHITE,SKOCZEK,"S"};
	for (k=12; k<14;k++)
		pieces[k]=(chessman){WHITE,GONIEC,"G"};
	pieces[14]=(chessman){WHITE,HETMAN,"H"};
	pieces[15]=(chessman){WHITE,KROL,"K"};
	for (k=24;k<26;k++)
		pieces[k]=(chessman){BLACK,WIEZA,"w"};
	for (k=26;k<28;k++)
		pieces[k]=(chessman){BLACK,SKOCZEK,"s"};
	for(k=28;k<30;k++)
		pieces[k]=(chessman){BLACK,GONIEC,"g"};
	pieces[30]=(chessman){BLACK,HETMAN,"h"};
	pieces[31]=(chessman){BLACK,KROL,"k"};
}
	
	chessman chessboard[8][8];
	
	void fill_chessboard(){
		
		for (k=0;k<8;k++)
			chessboard[k][1]=pieces[k];
		for (k=0;k<8;k++)
			chessboard[k][6]=pieces[k+16];
		chessboard [0][0]=pieces[8];
		chessboard [1][0]=pieces[10];
		chessboard [2][0]=pieces[12];
		chessboard [3][0]=pieces[14];
		chessboard [4][0]=pieces[15];
		chessboard [5][0]=pieces[13];
		chessboard [6][0]=pieces[11];
		chessboard [7][0]=pieces[9];
		chessboard [0][7]=pieces[24];
		chessboard [1][7]=pieces[26];
		chessboard [2][7]=pieces[28];
		chessboard [3][7]=pieces[30];
		chessboard [4][7]=pieces[31];
		chessboard [5][7]=pieces[29];
		chessboard [6][7]=pieces[27];
		chessboard [7][7]=pieces[25];
	}
		char *Symbol[8][8];
	void get_symbol(){
		for (k=0;k<8;k++)
	{
		for (j=0;j<8;j++)
			Symbol[k][j]=&chessboard[k][j].symbol;
}
	}
int main(){
	fill_chessman();
	fill_chessboard();
	get_symbol();
	print_chessboard();


return 0;
}
void print_chessboard(){
	int i,j;
	for (i=7;i>-1;i--)
	{
		for (j=7;j>-1;j--)
			printf("%s",*Symbol[j][i]);
		printf("\n");
		
	}
}
