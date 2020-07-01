#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

#define S_TO_WAIT 		5
#define MILIS_TO_WAIT	0
#define SELECT_EVENT		1
#define SELECT_NO_EVENT		0

#include "Menu/Menu.h"
#include "Move/MoveUp/MoveUp.h"
#include "Move/MoveDown/MoveDown.h"
#include "Move/MoveRight/MoveRight.h"
#include "Move/MoveLeft/MoveLeft.h"
#include "Draw/Draw.h"
#include "GameOver/GameOver.h"
#include "BestMove/BestMove.h"
#include "GP/GenerarePozitii.h"
#include "Random2,4/Random2,4.h"

int main()
{
	char c;
	int nfds, sel;

	fd_set read_descriptors;
	struct timeval timeout;
	WINDOW *wnd = initscr();
	WINDOW *wnd2 = initscr();

	nfds = 1;
	clear();
	noecho();
	cbreak();
	curs_set(0);

	start_color();
	use_default_colors();
	
	refresh();

	
	int choice, inGame, GameOver, areYouSure, afterGO, afkchoice, score,fromResume,boardType,valid;
	int W,A,S,D,max,valid_w,valid_a,valid_s,valid_d,dirIfEqual;
	srand(time(NULL));

	inGame = 0;		// variabila care arata daca un joc se afla in desfasurare
	GameOver = 0;	// variabila de verificare a posibilitatii de continuare a jocului
	afterGO = -1;	//variabila de decizie dupa GameOver care indica daca jucatorul da restart sau quit
	fromResume = 0;	
	boardType = 1;	// variabila decizionala pentru tipul de tabla ales
	valid = 0;		// variabila pentru determinarea validitatii unei miscari facute de jucator
	int **a,px,py;

	a = (int **)malloc(4*sizeof(int *));
	int i;

	for(i = 0; i < 4; i++)
		a[i] = (int *)malloc(4*sizeof(int));


	while(1)
	{	
		if(afterGO == 1 || fromResume == 1)
			choice = 0;
		else
			choice = MainMenu(wnd);
		
		if(choice == 3)		// Quit din Main Menu
		{
			break;
		}

		if(choice == 0)		//NewGame
		{		
				afterGO = -1;
				
				wclear(wnd);
				wrefresh(wnd);
				if(fromResume == 0)
				{
					NewBoard(a);
					score = 0;
				}
				fromResume = 0;
				inGame = 1;
				
				FD_ZERO(&read_descriptors);
				FD_SET(0, &read_descriptors);
				nfds =1;
				timeout.tv_sec = S_TO_WAIT;
				timeout.tv_usec = MILIS_TO_WAIT;

				
			while(1)
			{	
				
				if(boardType == 0)
					DrawMatrice(wnd, a);
				else
					DrawMatriceWithColor(wnd,a);

				DrawScore(wnd,score);
				valid_w = valid_up(a);
				valid_a = valid_left(a);
				valid_s = valid_down(a);
				valid_d = valid_right(a);
				DrawPanel(wnd,valid_w,valid_a,valid_s,valid_d);
				wrefresh(wnd);
				refresh();
				sel = select(nfds, &read_descriptors, NULL, NULL, &timeout);
				
				

				if(sel == 1)
				{	
					c = wgetch(wnd);
					
				if (tolower(c) == 'q') 
				{	
					clear();
					areYouSure = AreYouSure(wnd2);

					if(areYouSure == 0)
					{	
						clear();
						break;
					}
					else
					{
						clear();
						
						if(boardType == 0)
							DrawMatrice(wnd, a);
						else
							DrawMatriceWithColor(wnd,a);
					}
					
				}

				switch(tolower(c))
					{	
					case 'w':MoveUp(a, &score, &valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;

					case 'a':MoveLeft(a, &score, &valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;

					case 's':MoveDown(a, &score,&valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;

					case 'd':MoveRight(a, &score,&valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;
					}
				
				}

				if(sel == 0)
				{	
					// W,A,S,D retin numarul de celule care s-ar elibera prin apasarea 
					// tastei respective iar valid_w, valid_a, valid_s si valid_d
					// determina validitatea miscarii respective
					// pentru 2 miscari egale ca numar de celule eliberate 
					// considerand ca acele mutari sunt valide
					// se va alege la intamplare una dintre cele doua
					W = BestW(a);
					A = BestA(a);
					S = BestS(a);
					D = BestD(a);

					valid_w = valid_up(a);
					valid_a = valid_left(a);
					valid_s = valid_down(a);
					valid_d = valid_right(a);

					max = -1;
					// determinarea celei mai bune mutari pe tabla
					// ( ca numar de celule eliberate )
					if(W > max && valid_w == 1)
						{afkchoice = 0; max = W;}

					if(A > max && valid_a == 1)
						{afkchoice = 1; max = A;}


					if(A == max && valid_a == 1)
					{
						dirIfEqual = CoinFlip();
						if(dirIfEqual == 0)
							afkchoice = 1;
					}

					if(S > max && valid_s == 1)
						{afkchoice = 2; max = S;}

					if(S == max && valid_s == 1)
					{
						dirIfEqual = CoinFlip();
						if(dirIfEqual == 0)
							afkchoice = 2;
					}

					if(D > max && valid_d == 1)
						{afkchoice = 3; max = D;}

					if(D == max && valid_d == 1)
					{
						dirIfEqual = CoinFlip();
						if(dirIfEqual == 0)
							afkchoice = 3;
					}


					switch(afkchoice)
					{	
					case 0:MoveUp(a, &score, &valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;

					case 1:MoveLeft(a, &score, &valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;

					case 2:MoveDown(a, &score, &valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;

					case 3:MoveRight(a, &score, &valid);
						GenerarePozitii(a,&px,&py);
						if(px != -1 && valid == 1)
							a[px][py] = RNG();
						break;
					}
				}	
				
 				// verificare pentru GameOver
				GameOver = checkGameOver(a);
				valid = 0;
				
				if(GameOver == 1)
				{	
					inGame = 0;
					clear();
					afterGO = DrawGOScreen(wnd,score);


					if(afterGO == 0)  // QUIT to Main Menu
					{	
						clear();
						break;
					}
					else			//RESTART
					{
						clear();     
						choice = 0;
						break;	
					}


				}
				wrefresh(wnd);
				refresh();
				FD_SET(0, &read_descriptors);
		
				timeout.tv_sec = S_TO_WAIT;
				timeout.tv_usec = MILIS_TO_WAIT;
				
			}
		}

			if(choice == 1) //Resume
			 	{
			 		if( inGame == 1)
			 		{
			 			choice = 0;
			 			fromResume = 1;
			 		}
			 		else
			 		{	
			 			clear();
			 			DrawResumeScreen(wnd);
			 			refresh();	
			 		}
			 	}

			if(choice == 2) //Options
			 {	
			 	clear();
			 	boardType = WhatBoard(wnd);
			 	wrefresh(wnd);
			 }
				
		
		refresh();
	}

	endwin();

	for(i = 0; i < 4; i++)
		free(a[i]);
	free(a);

	return 0;
}