#include <stdio.h>
#include <stdlib.h>

void MoveLeft(int **a, int *score, int *valid)
{
	int i,j,k,last_x,last_y;

	for(i = 0; i < 4; i++)
	{
		last_x = last_y = -1;

		for(j = 1; j < 4; j++)
		{
			if(a[i][j] != 0)
			{
				for(k = j-1; k > 0; k--)
				{
					if(a[i][k] != 0)
						break;
				}


				if(a[i][k] == a[i][j] && (i != last_x || last_y != k))
				{
					a[i][k] = a[i][k]+a[i][j];
					last_x = i;
					last_y = k;
					(*score) += a[i][k];
					a[i][j] = 0;
					*valid = 1;
				}
				else
				if(a[i][k] == a[i][j] && i == last_x && last_y == k && (k+1) != j)
				{
					a[i][k+1] = a[i][j];
					a[i][j] = 0;
					*valid = 1;
				}
				else
				if(a[i][k] == 0)
				{
					a[i][k] = a[i][j];
					a[i][j] = 0;
					*valid = 1;
				}	
				else
				if(a[i][k] != 0 && a[i][k] != a[i][j] && (k+1) != j)
				{
					a[i][k+1] = a[i][j];
					a[i][j] = 0;
					*valid = 1;
				}
			}
		}
	}
} 

int valid_left(int **a)
{
	int **b,i,j;
	int t_scor,t_valid;
	b = (int **)malloc(4*sizeof(int *));
	for(i = 0; i < 4; i++)
		b[i] = (int *)malloc(4*sizeof(int));

	t_scor = 0;
	t_valid = 0;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			b[i][j]=a[i][j];

	MoveLeft(b,&t_scor,&t_valid);
	for(i = 0; i < 4; i++)
		free(b[i]);
	free(b);

	return t_valid;
}
