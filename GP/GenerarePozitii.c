#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//#include "Random2,4.c"

void GenerarePozitii(int **a, int *px, int *py)
{
	// px reprezinta indicele de linie
	// py reprezunta indicele de coloana

	int i,j,s_libere;
	s_libere = 0;

	// s_libere sau "spatii libere" reprezinta cate casute din tabla nu sunt ocupate

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(a[i][j] == 0)
				{
					s_libere++;
					*px = i;
					*py = j;
				}

	int ok = 0;
	if(s_libere == 0)
	{
	// pentru o tabla fara spatii libere se intoarce prin px si py valoarea -1 
	// pentru a indica faptul ca nu se mai poate adauga o noua valoare aleatoare
		*px = -1;
		*py = -1;
	}
	if( s_libere > 1)
	{
		
		while(ok != 1)
		{
			*px = rand() % 4;
			*py = rand() % 4;

			if(a[*px][*py] == 0)
				ok = 1;
		}
		
	}


}
