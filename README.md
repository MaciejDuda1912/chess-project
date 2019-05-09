#include<stdio.h>
void print_chessboard();
void fill_chessboard();
void fill_chessman();
void play(int x);

enum Color{WHITE,BLACK};
enum Type{PIONEK,SKOCZEK,GONIEC,HETMAN,WIEZA,KROL};
enum Dead_alive{DEAD,ALIVE};
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
int k;
void fill_chessman(){
	for  (k=0; k<8;k++)
		pieces[k]=(chessman){WHITE,PIONEK,'P',k,1};
	for  (k=16; k<24;k++)
		pieces[k]=(chessman){BLACK,PIONEK,'p',k-16,6};
	for (k=8; k<10;k++)
		pieces[k]=(chessman){WHITE,WIEZA,'W',(k-8)*7,0};
	for (k=10; k<12;k++)
		pieces[k]=(chessman){WHITE,SKOCZEK,'S',-49+k*5,0};
	for (k=12; k<14;k++)
		pieces[k]=(chessman){WHITE,GONIEC,'G',k*3-34,0};
	pieces[14]=(chessman){WHITE,HETMAN,'H',4,0};
	pieces[15]=(chessman){WHITE,KROL,'K',3,0};
	for (k=24;k<26;k++)
		pieces[k]=(chessman){BLACK,WIEZA,'w',(k-24)*7,7};
	for (k=26;k<28;k++)
		pieces[k]=(chessman){BLACK,SKOCZEK,'s',k*5-129,7};
	for(k=28;k<30;k++)
		pieces[k]=(chessman){BLACK,GONIEC,'g',k*3-82,7};
	pieces[30]=(chessman){BLACK,HETMAN,'h',4,7};
	pieces[31]=(chessman){BLACK,KROL,'k',3,7};
	for (k=0; k<32;k++)
		pieces[k].dead_alive=ALIVE;
}


void print_chessboard(){
	int i,j,k;
	int flag=0;
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++){
			printf("[");
			flag=0;
			for(k=0;k<32;k++){
				if (pieces[k].x==j && pieces[k].y==i && pieces[k].dead_alive==ALIVE) {
					printf("%c",pieces[k].symbol);
					flag=1	;
				}
			}
			if (flag==0)
				printf(" ");
			printf("]")	;
		}
		printf("\n");

	}
}
void play(int x){
	
}

int main(){
	int gra=0;
	fill_chessman();
	while (gra=0)
	ruch=1;
	play(ruch)
	print_chessboard();

return 0;
}
