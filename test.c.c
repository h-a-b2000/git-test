//in the name of God
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
char matrix[7][12];
int score=0;
COORD coord ={0,0};
void gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*int main() {
	gotoxy(3,2);
	printf("!");
}*/
typedef struct{
	int x;
	int y;
}location;
location pakman;

void print_matrix()
{
	for(int i=0;i<7;i++)
	{
		for(int l=0;l<12;l++)
			printf("%c",matrix[i][l]);
		printf("\n");
	}
}

location make_matrix()
{
	char c;
	location pakman;
	int k=0;
	FILE *f;
	f=fopen("test.txt","r");
	if(f==NULL)
		printf("!");
	for(int i=0;i<12;i++)
		matrix[k][i]=176;
	while(!feof(f))
	{
		k++;
		int i=0;
		matrix[k][i++]=176;
		for(;i<11;i++)
		{
			fscanf(f,"%c",&c);
			switch(c){
				case '1':
					matrix[k][i]=' ';
					break;
				case '#':
					matrix[k][i]=176;
					break;
				case '0':
					matrix[k][i]='O';
					pakman.x=i;
					pakman.y=k;
					break;
				case '*':
					matrix[k][i]='*';
					break;					
			}
		}
		matrix[k][i]=176;
		fgetc(f);
	}
	k++;
	for(int i=0;i<12;i++)
		matrix[k][i]=176;
	return pakman;
}
int check_food(){
	for(int i=0;i<7;i++)
		for(int j=0;j<12;j++)
			if(matrix[i][j]=='*')
				return 0;
	return 1;
}
void move(){
	char c1,c2;
	while(1)
	{
	c1=getch();
	if(c1=='-')
	{
		c2=getch();
		if(c2=='1')
		return;
	}
	if(c1==-32)
	{
	c2=getch();
	switch(c2){
		case 72:
			up();
			break;
		case 75:
			left();
			break;
		case 77:
			right();
			break;
		case 80:
			down();
			break;
	}
	}
	if(check_food())
	return;
	}
}
//////////////////////////////////
void left(){
	if(matrix[pakman.y][(pakman.x)-1]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.x--;
	if(matrix[pakman.y][pakman.x]=='*')
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,10);
	printf("%d",score);
}
//////////////////////////////////
void right(){
	if(matrix[pakman.y][(pakman.x)+1]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.x++;
	if(matrix[pakman.y][pakman.x]=='*')
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,10);
	printf("%d",score);
}
/////////////////////////////////
void down(){
	if(matrix[pakman.y+1][(pakman.x)]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.y++;
	if(matrix[pakman.y][pakman.x]=='*')
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,10);
	printf("%d",score);
}
/////////////////////////////////
void up(){
	if(matrix[pakman.y-1][(pakman.x)]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.y--;
	if(matrix[pakman.y][pakman.x]=='*')
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,10);
	printf("%d",score);
}
/////////////////////////////////
main()
{
	pakman=make_matrix(matrix);
	print_matrix(matrix);
	move();
	gotoxy(0,10);
	printf("%d",score);
	printf("\nend of game!");
	printf("\npress any key to exit");
	getch();
}
