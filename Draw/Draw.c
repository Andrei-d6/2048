#include <stdio.h>
#include <curses.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../GP/GenerarePozitii.h"
#include "../Random2,4/Random2,4.h"

/* 
	functie pentru incarcarea pe doua pozitii aleatoare 
	a 2 valori cuprinse in multime {2,4}

*/
void NewBoard(int **a)
{
	int i,j;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			a[i][j] = 0;

	int x,y;
	x = y = 0;

	GenerarePozitii(a,&x,&y);	
	a[x][y] = RNG();

	GenerarePozitii(a,&x,&y);	
	a[x][y] = RNG();

}

// functie pentru desenarea ecranului de game over

int DrawGOScreen(WINDOW *wnd, int scor)
{	
	// returneaza 0 pentru quit
	// returneaza 1 pentru restart
	char c;
	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);

	while(1){

	mvwprintw(wnd, nrows/3 -2, ncols/4,"Congratulations, your final score is:");
	mvwprintw(wnd, nrows/3 ,ncols/3 + 10,"%d",scor);
	mvwprintw(wnd, nrows/3 +2, ncols/4,"Press Q to quit, R to restart:");


	c = wgetch(wnd);

	if(tolower(c) == 'q')
		return 0;

	if(tolower(c)=='r')
		return 1;

	}
	

}

void print_in_middle( WINDOW *wnd, int startx, int starty, int width, char *string)
{
	int x, y;
	

	if(wnd == NULL)
		wnd = stdscr;

	getyx(wnd, x, y);

	if(startx != 0)
		x = startx;

	if( starty != 0)
		y = starty;

	if(width == 0)
		width = 80;

	mvwprintw(wnd, x, y, "%s", string);
	refresh(); 

}
/* 
	functie pentru desenarea color a unei matrici a 
	impreuna cu declararea perechilor de culori aferente
	fiecarei valori din matrice ( fundal + culoarea pentru numarul in sine )
*/
void DrawMatriceWithColor( WINDOW *wnd, int **a)
{
	init_color(9, 238 * 200 / 51, 228 * 200 / 51 ,218 * 200 / 51);
	init_pair(1,COLOR_BLACK,9);	 // 2

	init_color(10, 237 * 200 / 51, 224 * 200 / 51 ,200 * 200 / 51);
	init_pair(2,COLOR_BLACK,10);	 // 4

	init_color(11, 242 * 200 / 51, 177 * 200 / 51 ,121 * 200 / 51);
	init_pair(3,COLOR_WHITE,11);	 // 8

	init_color(12, 245 * 200 / 51, 149 * 200 / 51 ,99 * 200 / 51);
	init_pair(4,COLOR_WHITE,12);	 // 16

	init_color(13, 246 * 200 / 51, 124 * 200 / 51 ,95 * 200 / 51);
	init_pair(5,COLOR_WHITE,13);	 // 32

	init_color(14, 246 * 200 / 51, 94 * 200 / 51 ,95 * 200 / 51);
	init_pair(6,COLOR_WHITE,14);	 // 64

	init_color(15, 237 * 200 / 51, 207 * 200 / 51 ,114 * 200 / 51);
	init_pair(7,COLOR_BLACK,15);	 // 128

	init_color(16, 237 * 200 / 51, 204 * 200 / 51 , 97 * 200 / 51);
	init_pair(8,COLOR_BLACK,16);	 // 256

	init_color(17, 237 * 200 / 51, 200 * 200 / 51 , 80 * 200 / 51);
	init_pair(9,COLOR_WHITE,17);	 // 512

	init_color(18, 237 * 200 / 51, 197 * 200 / 51 , 63 * 200 / 51);
	init_pair(10,COLOR_WHITE,18);	 // 1024

	init_color(19, 237 * 200 / 51, 194 * 200 / 51 , 46 * 200 / 51);
	init_pair(11,COLOR_WHITE,19);	 // 2048

	init_color(20, 203 * 200 / 51, 192 * 200 / 51 , 177 * 200 / 51);
	init_pair(12,COLOR_BLACK,20);	 // empty

	init_color(21, 65 * 200 / 51, 105 * 200 / 51 , 225 * 200 / 51);
	init_pair(13,COLOR_WHITE,21);	 // 4096

	init_color(22, 25 * 200 / 51, 25 * 200 / 51 , 112 * 200 / 51);
	init_pair(14,COLOR_WHITE,22);	 // larger



	int i,j,x,y;
	char *numar,*adaugare;

	// numar - reprezinta numarul final cu tot cu spatii (ceea ce se va afisa)
	// adaugare - reprezinta elementul din matrice care va fi afisat

	numar = (char *)malloc(8*sizeof(char));
	adaugare = (char *)malloc(8*sizeof(char));

	x = y = 0;

	for(i = 3; i < 13; i = i + 3)
		for(j = 5; j < 27 ; j = j + 7)
		{
			if(a[x][y] == 0)
			{	
				attron(COLOR_PAIR(12));
				print_in_middle(wnd, i, j, 7,  "       ");
				print_in_middle(wnd, i+1, j, 7,"   *   ");
				print_in_middle(wnd, i+2, j, 7,  "       ");
				attroff(COLOR_PAIR(12));
			}

			if(a[x][y] != 0)
			{	
				sprintf(adaugare, "%d" ,a[x][y]);

				if(a[x][y] < 10)  // numar de  o cifra
				{
					strcpy(numar,"   ");
					strcat(numar, adaugare);
					strcat(numar,"   ");
				}

				if(a[x][y] > 9 && a[x][y] < 100)  // numar de 2 cifre
				{
					strcpy(numar,"   ");
					strcat(numar, adaugare);
					strcat(numar,"  ");
				}

				if(a[x][y] > 99 && a[x][y] < 1000)	// numar de 3 cifre
				{

					strcpy(numar,"  ");
					strcat(numar, adaugare);
					strcat(numar,"  ");
				}

				if(a[x][y] > 999 && a[x][y] < 10000) // numar de 4 cifre
				{

					strcpy(numar,"  ");
					strcat(numar, adaugare);
					strcat(numar," ");
				}


				if(a[x][y] > 9999 && a[x][y] < 100000) // numar de 5 cifre
				{

					strcpy(numar," ");
					strcat(numar, adaugare);
					strcat(numar," ");
				}


				if(a[x][y] == 2)
				{
					attron(COLOR_PAIR(1));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(1));
				}


				if(a[x][y] == 4)
				{
					attron(COLOR_PAIR(2));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(2));
				}

				if(a[x][y] == 8)
				{
					attron(COLOR_PAIR(3));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(3));
				}

				if(a[x][y] == 16)
				{
					attron(COLOR_PAIR(4));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(4));
				}

				if(a[x][y] == 32)
				{
					attron(COLOR_PAIR(5));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(5));
				}
			

				if(a[x][y] == 64)
				{
					attron(COLOR_PAIR(6));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(6));
				}
				

				if(a[x][y] == 128)
				{
					attron(COLOR_PAIR(7));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(7));
				}


				if(a[x][y] == 256)
				{
					attron(COLOR_PAIR(8));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(8));
				}


				if(a[x][y] == 512)
				{
					attron(COLOR_PAIR(9));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(9));
				}


				if(a[x][y] == 1024)
				{
					attron(COLOR_PAIR(10));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(10));
				}


				if(a[x][y] == 2048)
				{
					attron(COLOR_PAIR(11));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(11));
				}	

				if(a[x][y] == 4096)
				{
					attron(COLOR_PAIR(13));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(13));
				}	

				if(a[x][y] > 4096)
				{
					attron(COLOR_PAIR(14));
					print_in_middle(wnd, i, j,7,"       ");
					print_in_middle(wnd, i+1, j,7,numar);
					print_in_middle(wnd, i+2, j,7,"       ");
					attroff(COLOR_PAIR(14));
				}	
			}
				y++;
				if(y == 4)
				{
					x++;
					y = 0;
				}
	}
}

// functie pentru desenarea unei table de joc alb-negru
// pentru o matrice a

void DrawMatrice( WINDOW *wnd, int **a)
{
	int i,j,x,y;
	x = y = 0;
	clear();

	for(i = 2; i < 31; i++ )
	{
		mvaddstr(2,i,"-");
		mvaddstr(7,i,"-");

	}	
	
	for(j = 3; j < 7; j++ )
	{
		mvaddstr(j,2,"|");
		mvaddstr(j,9,"|");
		mvaddstr(j,16,"|");
		mvaddstr(j,23,"|");
		mvaddstr(j,30,"|");
	}

	for(i = 3; i < 7; i++)
		for(j = 6; j < 30 ; j=j+7)
			{
			if(a[x][y] != 0)
			 {
				if(a[x][y] < 10)
					mvwprintw(wnd,i,j,"%d",a[x][y]);

				if(a[x][y] > 9 && a[x][y] < 1000)
					mvwprintw(wnd,i,j-1,"%d",a[x][y]);

				if(a[x][y] > 1000)
					mvwprintw(wnd,i,j-2,"%d",a[x][y]);
			 }

				y++;
				if(y == 4)
				{
					x++;
					y = 0;
				}
			}
}

void DrawScore(WINDOW *wnd, int score)
{		
	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);

	mvwprintw(wnd,nrows/5-1,ncols/2,"Score:");
	mvwprintw(wnd,nrows/5-1,ncols/2+7,"%d",score );
}


void DrawResumeScreen(WINDOW *wnd)
{
	char *choices;

	choices = (char *)malloc(2*sizeof(char ));
	strcpy(choices,"OK");
	
	keypad(wnd, true);

	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);

	int choice;
   
	while(1)
	{	
		mvwprintw(wnd, nrows/4, ncols/4,"In order to resume you must already be in a game");
		


			wattron(wnd, A_REVERSE);
			mvwprintw(wnd, nrows/3, ncols/2, choices);
			wattroff(wnd, A_REVERSE);
		

		choice = wgetch(wnd);

		if(choice == 10)
			break;

	}

	free(choices);
	clear();

}

/*
 	functie pentru Menu-ul Options in care se efectueaza alegerea
 	tipului de tabla dorit (alb-negru sau color)
 	afisand de asemenea un exemplu pentru aspectul tablei 
*/

int WhatBoard( WINDOW *wnd)
{
	char **choices;
	int i,j;

	int **a;
	a = (int **)malloc(4*sizeof(int *));
	
	for(i = 0; i < 4; i++)
		a[i] = (int *)malloc(4*sizeof(int));
	int x = 2;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
		{
			if(x < 8193)
			{
				a[i][j] = x;
				x = x*2;
			}
			else
				a[i][j] = 0;
		}

	choices = (char **)malloc(2*sizeof(char *));
	for(i = 0; i < 3; i++)
		choices[i] = (char *)malloc(20*sizeof(int));

	strcpy(choices[0],"Black-and-White");
	strcpy(choices[1],"Colorful");

	keypad(wnd, true);

	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);

	int choice;
	int highlight = 0;
   
	DrawMatrice(wnd,a);
	while(1)
	{	
		mvwprintw(wnd, nrows/3 -2, ncols/2,"Choose a type of board");

		for(i = 0; i < 2; i++)
		{	
			if(i == highlight)
				wattron(wnd, A_REVERSE);
			mvwprintw(wnd, i+nrows/3, ncols/2, choices[i]);
			wattroff(wnd, A_REVERSE);
		}

		choice = wgetch(wnd);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if( highlight == -1)
					highlight = 0;
				break;

			case KEY_DOWN:
				highlight++;
				if( highlight == 2)
					highlight = 1;
				break;
			default:
				break;
		}

		if(!strcmp(choices[highlight],"Black-and-White"))
			{clear(); DrawMatrice(wnd,a);}

		if(!strcmp(choices[highlight],"Colorful"))
			{clear(); DrawMatriceWithColor(wnd,a);}
		
		if(choice == 10)
			break;

	}

	if(!strcmp(choices[highlight],"Black-and-White"))
		choice = 0;

	if(!strcmp(choices[highlight],"Colorful"))
		choice = 1;



	for(i = 0; i < 2; i++)
		free(choices[i]);
	free(choices);

	for(i = 0; i < 4; i++)
		free(a[i]);
	free(a);
	clear();

	return choice;
}

// Desenare a panoului aditional tablei de joc

void DrawPanel(WINDOW *wnd,int w,int a,int s,int d)
{	
	// w,a,s,d sunt 1 daca miscarea in directia respective este una valida si 0 in caz contrar
	// pentru o miscare invalida indicatia de directie a acesteia va fi desenata cu rosu,
	// iar pentru o miscare valida culoarea asociata indicatiei de directie va fi verde
	
	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);
	time_t t;
	time(&t);
	init_color(23, 0 * 200 / 51, 0 * 200 / 51 ,0 * 200 / 51);
	init_pair(15,COLOR_GREEN,23);	 // valid -> Verde
	init_pair(16,COLOR_RED,23);	 // not valida-> Rosu

	mvwprintw(wnd,nrows/5-3,ncols/2,"Date and Time: %s",ctime(&t));
	mvwprintw(wnd,nrows/3,ncols/2,"Use W,A,S,D to move the tiles");
	if(w == 1)
	{
		attron(COLOR_PAIR(15));
		print_in_middle(wnd,nrows/3+2,ncols/2,10,"W - up");
		attroff(COLOR_PAIR(15));
	}
	else
	{
		attron(COLOR_PAIR(16));
		print_in_middle(wnd,nrows/3+2,ncols/2,10,"W - up");
		attroff(COLOR_PAIR(16));
	}

	if(a == 1)
	{
		attron(COLOR_PAIR(15));
		print_in_middle(wnd,nrows/3+3,ncols/2,10,"A - left");
		attroff(COLOR_PAIR(15));
	}
	else
	{
		attron(COLOR_PAIR(16));
		print_in_middle(wnd,nrows/3+3,ncols/2,10,"A - left");
		attroff(COLOR_PAIR(16));
	}


	if(s == 1)
	{
		attron(COLOR_PAIR(15));
		print_in_middle(wnd,nrows/3+4,ncols/2,10,"S - down");
		attroff(COLOR_PAIR(15));
	}
	else
	{	
		attron(COLOR_PAIR(16));
		print_in_middle(wnd,nrows/3+4,ncols/2,10,"S - down");
		attroff(COLOR_PAIR(16));
	}

	if(d == 1)
	{
		attron(COLOR_PAIR(15));
		print_in_middle(wnd,nrows/3+5,ncols/2,10,"D - right");
		attroff(COLOR_PAIR(15));
	}
	else
	{
		attron(COLOR_PAIR(16));
		print_in_middle(wnd,nrows/3+5,ncols/2,10,"D - right");
		attroff(COLOR_PAIR(16));
	}
	mvwprintw(wnd,nrows/3+7,ncols/2,"Press Q to quit to main menu");
}
