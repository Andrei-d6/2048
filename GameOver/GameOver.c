#include <stdio.h>

int checkGameOver( int **a)
{
	int i,j;

	// 1 inseamnca Game Over
	// 0 inseamnca ca inca nu s-a terminat jocul

	for(j = 1; j < 3; j++)
	{
		if(a[0][j-1] == 0 || a[0][j-1] == a[0][j] || a[1][j] == 0 || a[1][j] == a[0][j] || a[0][j+1] == 0 || a[0][j+1] == a[0][j])
			return 0;

		if(a[3][j-1] == 0 || a[3][j-1] == a[3][j] || a[2][j] == 0 || a[2][j] == a[3][j] || a[3][j+1] == 0 || a[3][j+1] == a[3][j])
			return 0;
	}

	for(i = 1; i < 3; i++)
	{
		if(a[i-1][0] == 0 || a[i-1][0] == a[i][0] || a[i][1] == 0 || a[i][1] == a[i][0] || a[i+1][0] == 0 || a[i+1][0] == a[i][0])
			return 0;

		if(a[i-1][3] == 0 || a[i-1][3] == a[i][3] || a[i][2] == 0 || a[i][2] == a[i][3] || a[i+1][3] == 0 || a[i+1][3] == a[i][3])
			return 0;

	}

	for(i = 1; i < 3; i++)
		for(j = 1; j < 3; j++)
		{
			if(a[i-1][j] == 0 || a[i-1][j] == a[i][j])
				return 0;

			if(a[i+1][j] == 0 || a[i+1][j] == a[i][j])
				return 0;	


			if(a[i][j-1] == 0 || a[i][j-1] == a[i][j])
				return 0;

			
			if(a[i][j+1] == 0 || a[i][j+1] == a[i][j])
				return 0;

		}

	return 1;
}
/*
int main()
{
	int a[4][4];
	int i,j;
	int x = 1;

	for(i =0; i < 4; i++)
		for(j = 0;j < 4; j++)
		{
			a[i][j] = x;
			x++;
		}
			a[3][2]=0;
	x = checkGameOver(a);


	for(i = 1; i < 4; i++){
		for(j = 1;j < 4; j++)
			printf("%d ",a[i][j]);
		    printf("\n");
	}

	printf("%d\n",x);
	return 0;
}
*/