#include <stdio.h>
#include <stdlib.h>

void MoveDown(int **a, int *score, int *valid)
{
	int i,j,k,last_x,last_y;

	for(j = 0; j < 4; j++)
	{   
		last_x = last_y = -1;

		for(i = 2; i >= 0; i--)
		{	
			if(a[i][j]!= 0)
			{
				for(k = i+1; k < 3; k++)
				{
					if(a[k][j] != 0)
						break;
				}

				if(a[k][j] == a[i][j] && (k != last_x || last_y != j))
				{
					a[k][j] = a[k][j]+a[i][j];
					last_x = k;
					last_y = j;
					(*score) += a[k][j];
					a[i][j] = 0;
					*valid = 1;
				}
				else
				if(a[k][j] == a[i][j] && k == last_x && last_y == j && (k-1) != i)
				{
					a[k-1][j] = a[i][j];
					a[i][j] = 0;
					*valid = 1;
				}
				else
				if(a[k][j] == 0)
				{
					a[k][j] = a[i][j];
					a[i][j] = 0;
					*valid = 1;
				}	
				else
				if(a[k][j] != 0 && a[k][j] != a[i][j] && (k-1) != i)
				{
					a[k-1][j] = a[i][j];
					a[i][j] = 0;
					*valid = 1;
				}

			}

		}
	}

}

int valid_down(int **a)
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

	MoveDown(b,&t_scor,&t_valid);
	for(i = 0; i < 4; i++)
		free(b[i]);
	free(b);
	return t_valid;
}
