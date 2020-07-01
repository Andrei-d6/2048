#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>

/*
   functie pentru desenarea menu-ului principal 
   New Game
   Resume
   Options
   Quit	

*/
int MainMenu( WINDOW *wnd)
{
	char **choices;
	int i;

	choices = (char **)malloc(4*sizeof(char *));
	for(i = 0; i < 4; i++)
		choices[i] = (char *)malloc(10*sizeof(int));

	strcpy(choices[0],"New Game");
	strcpy(choices[1],"Resume");
	strcpy(choices[2],"Options");
	strcpy(choices[3],"Quit");

	keypad(wnd, true);

	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);

	int choice;
	int highlight = 0;
   

	while(1)
	{	
		box(wnd, -1,-1);
		for(i = 0; i < 4; i++)
		{	
			if(i == highlight)
				wattron(wnd, A_REVERSE);
			mvwprintw(wnd, i+nrows/3, ncols/3, choices[i]);
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
				if( highlight == 4)
					highlight = 3;
				break;
			default:
				break;
		}

		if(choice == 10)
			break;

	}

	if(!strcmp(choices[highlight],"New Game"))
		choice = 0;

	if(!strcmp(choices[highlight],"Resume"))
		choice = 1;

	if(!strcmp(choices[highlight],"Options"))
		choice = 2;

	if(!strcmp(choices[highlight],"Quit"))
		choice = 3;

	for(i = 0; i < 4; i++)
		free(choices[i]);
	free(choices);

	return choice;
}

// functie de interogare pentru parasirea jocului si intoarcerea catre MainMenu

int AreYouSure( WINDOW *wnd)
{
	char **choices;
	int i;

	choices = (char **)malloc(2*sizeof(char *));
	for(i = 0; i < 3; i++)
		choices[i] = (char *)malloc(4*sizeof(int));

	strcpy(choices[0],"YES");
	strcpy(choices[1],"NO");

	keypad(wnd, true);

	int nrows,ncols;
	getmaxyx(wnd, nrows, ncols);

	int choice;
	int highlight = 0;
   

	while(1)
	{	
		mvwprintw(wnd, nrows/3 -2, ncols/4,"Are you sure you want to quit?");
		mvwprintw(wnd, nrows/3 + 3, ncols/4 - 5," ( Remember you can still resume afterwards )");


		for(i = 0; i < 2; i++)
		{	
			if(i == highlight)
				wattron(wnd, A_REVERSE);
			mvwprintw(wnd, i+nrows/3, ncols/3, choices[i]);
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

		if(choice == 10)
			break;

	}

	if(!strcmp(choices[highlight],"YES"))
		choice = 0;

	if(!strcmp(choices[highlight],"NO"))
		choice = 1;



	for(i = 0; i < 2; i++)
		free(choices[i]);
	free(choices);

	return choice;
}
