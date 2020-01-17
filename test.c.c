//in the name of God
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
/*COORD coord ={0,0};
void gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main() {
	gotoxy(3,2);
	printf("!");
}*/
typedef struct{
	int x;
	int y;
}location;

void print_matrix(char matrix[][12])
{
	for(int i=0;i<7;i++)
	{
		for(int l=0;l<12;l++)
			printf("%c",matrix[i][l]);
		printf("\n");
	}
}

location make_matrix(char matrix[][12])
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
void move
main()
{
	char matrix[7][12];
	location pakman=make_matrix(matrix);
	print_matrix(matrix);
	printf("%d %d",pakman.x,pakman.y);
}
