//in the name of God
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

char matrix[100][100];
int distance_matrix[100][100];
int score=0,ifix,jfix;
COORD coord ={0,0};
void gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
typedef struct{
	int x;
	int y;
}location;
location pakman;
/////////////////////////////////////////////////
location search_foods(int i,int j)
{
	while(j<jfix && matrix[j][i]!=-8){
		if(i==ifix)
		{
			j++;
			i=0;
		}
		else
		i++;
	}
	location food;
	food.x=i;
	food.y=j;
	return food;
}
////////////////////////////////////////////////////
int find_distance(location a,location b){
	return (fabs(a.x-b.x)+fabs(a.y-b.y));
}
///////////////////////////////////////////////////
location nearest_food(){
	location food={0,0},minfood={-100,-100};
	int i=-1,j=0,distance;
	while(food.y<jfix){
		food=search_foods(i+1,j);
		i=food.x;
		j=food.y;
		if(food.y<jfix)
		{
		if(find_distance(pakman,food) < find_distance(pakman,minfood)){
			minfood.x=i;
			minfood.y=j;
		}
		}
	}
	if(minfood.x>=ifix || minfood.x<0 || minfood.y<0 || minfood.y>=jfix)
	end();
	return minfood;
}
/////////////////////////////////////////////////////////////////////
int minf(int a,int b,int c,int d){
	int min=(a<b?a:b);
	min=(min<c?min:c);
	min=(min<d?min:d);
	return min;
}
/////////////////////////////////////////////////////////////
void make_distance_matrix(){
	int flag=1;
	for(int j=0;j<jfix;j++)
		for (int i=0;i<ifix;i++)
			distance_matrix[j][i]=INFINITY;
	while(flag){
		flag=0;
		for (int j=0;j<jfix;j++)
		{
			for (int i=0;i<ifix;i++)
			{
				int save=distance_matrix[j][i];
				if(i==pakman.x && j==pakman.y)
					distance_matrix[j][i]=0;
				else if(matrix[j][i]==(-80))
					distance_matrix[j][i]=INFINITY;
					else if(distance_matrix[j][i]>minf(distance_matrix[j+1][i],distance_matrix[j-1][i],distance_matrix[j][i+1],distance_matrix[j][i-1]))
						distance_matrix[j][i]=minf(distance_matrix[j+1][i],distance_matrix[j-1][i],distance_matrix[j][i+1],distance_matrix[j][i-1])+1;
				if (save!=distance_matrix[j][i])
					flag=1;
			}
		}
	}
}
//////////////////////////////////////////////////////
location search_around(int value,location food)
{
	location temp;
	if(value==distance_matrix[food.y+1][food.x])
	{
		temp.x=food.x;
		temp.y=food.y+1;
	}
	else if(value==distance_matrix[food.y-1][food.x])
	{
		temp.x=food.x;
		temp.y=food.y-1;
	}
	else if(value==distance_matrix[food.y][food.x+1])
	{
		temp.x=food.x+1;
		temp.y=food.y;
	}
	else if(value==distance_matrix[food.y][food.x-1])
	{
		temp.x=food.x-1;
		temp.y=food.y;
	}
	else
		temp.x=-1;
	return temp;
}
/////////////////////////////////////////////////////////////////////////////
void set_path(){
	location food=nearest_food();
	while(distance_matrix[food.y][food.x]!=0)
	{
	location temp=search_around(distance_matrix[food.y][food.x]-1,food);
	distance_matrix[food.y][food.x]=0;
	food.x=temp.x;
	food.y=temp.y;
	}
}
//////////////////////////////////////////////////////////////
void move_auto()
{
	int flag=0;
	while(flag!=-1)
	{
	sleep(1);
	location temp=search_around(0,pakman);
	flag=temp.x;
	if(flag!=-1){
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	distance_matrix[pakman.y][pakman.x]=1000;
	pakman.x=temp.x;
	pakman.y=temp.y;
	if(matrix[pakman.y][pakman.x]==-8)
	score++;
	matrix[pakman.y][pakman.x]='O';
	gotoxy(pakman.x,pakman.y);
	printf("O");
	}
	gotoxy(0,jfix);
	printf("your score:%d",score);
	}
}
//*********************************************************************************************//
void print_matrix(){
	for(int i=0;i<jfix;i++)
	{
		for(int l=0;l<ifix;l++)
			printf("%c",matrix[i][l]);
		printf("\n");
	}
}
////////////////////////////////////////////////
location make_matrix(){
	char c;
	location pakman;
	int k=0;
	FILE *f;
	f=fopen("test.txt","r");
	if(f==NULL)
	{
		printf("can not find the map!");
		exit(1);
	}
	while(!feof(f))
	{
		c=fgetc(f);
		k++;
		int i=0;
		matrix[k][i++]=176;
		while(c!='\n' && !feof(f))
		{
			switch(c){
				case '1':
					matrix[k][i++]=' ';
					break;
				case '#':
					matrix[k][i++]=176;
					break;
				case '0':
					matrix[k][i]='O';
					pakman.x=i++;
					pakman.y=k;
					break;
				case '*':
					matrix[k][i++]=248;
					break;					
			}
			c=fgetc(f);
		}
		matrix[k][i]=176;
		ifix=i+1;
	}
	k++;
	for(int i=0;i<ifix;i++)
		matrix[k][i]=176;
	jfix=k+1;
	for(int i=0;i<ifix;i++)
		matrix[0][i]=176;
	return pakman;
}
/////////////////////////////////////////////
int check_food(){
	for(int i=0;i<jfix;i++)
		for(int j=0;j<ifix;j++)
			if(matrix[i][j]==-8)
				return 0;
	return 1;
}
//*****************************************************************************************//
void move_man(){
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
//////////////////////////////////////////////////
void left(){
	if(matrix[pakman.y][(pakman.x)-1]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.x--;
	if(matrix[pakman.y][pakman.x]==-8)
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,jfix);
	printf("your score:%d",score);
}
//////////////////////////////////////////////////
void right(){
	if(matrix[pakman.y][(pakman.x)+1]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.x++;
	if(matrix[pakman.y][pakman.x]==-8)
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,jfix);
	printf("your score:%d",score);
}
///////////////////////////////////////////////////
void down(){
	if(matrix[pakman.y+1][(pakman.x)]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.y++;
	if(matrix[pakman.y][pakman.x]==-8)
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,jfix);
	printf("your score:%d",score);
}
///////////////////////////////////////////////////
void up(){
	if(matrix[pakman.y-1][(pakman.x)]!=(-80))
	{
	gotoxy(pakman.x,pakman.y);
	printf(" ");
	matrix[pakman.y][pakman.x]=' ';
	pakman.y--;
	if(matrix[pakman.y][pakman.x]==-8)
	score++;
	gotoxy(pakman.x,pakman.y);
	printf("O");
	matrix[pakman.y][pakman.x]='O';
	}
	gotoxy(0,jfix);
	printf("your score:%d",score);
}
//////////////////////////////////////////////////
void end(){
	gotoxy(0,jfix);
	printf("your score:%d",score);
	printf("\nend of game!");
	printf("\npress any key to exit");
	getch();
	exit(1);
}
main()
{
	pakman=make_matrix(matrix);
	print_matrix(matrix);
	char c;
	printf("\nchoose how to play:\n1.manualy\n2.auto\n");
	c=getchar();
	system("cls");
	print_matrix(matrix);
	if(c=='2'){
	while(1){
	make_distance_matrix();
	set_path();
	move_auto();
	}
	}
	else{
	move_man();
	end();
	}
}
