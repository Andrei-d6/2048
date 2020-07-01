#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CoinFlip()
{
	int x;
	x = rand() % 2;

	if(x == 0)
		return 0;
	else
		return 1;

}

int BestW(int **a)
{
	int i,W,j,k,last_x,last_y;

	W = 0;

	 // Pentru W - se determina numarul de celule eliberate  

	for(j = 0; j < 4; j++)
	{ 
		last_x = last_y = -1;
		
		for(i = 0; i < 3; i++)
			{
				if(a[i][j] != 0)
				{
					for(k = i+1; k < 3; k++)
					{
						if(a[k][j] != 0)
						break;
					}


				if(a[k][j] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = k;
					last_y = j;
					W++;
				}

				}
			}
	}

	return W;
}

int BestA(int **a)
{
	int i,A,j,k,last_x,last_y;

	A = 0;

	// Pentru A - se determina numarul de celule eliberate 

	for(i = 0; i < 4; i++)
	{ 
		last_x = last_y = -1;
		
		for(j = 0; j < 3; j++)
			{
				if(a[i][j] != 0)
				{
					for(k = j+1; k < 3; k++)
					{
						if(a[i][k] != 0)
						break;
					}


				if(a[i][k] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = i;
					last_y = k;
					A++;
				}

				}
			}
	}

	return A;
}

int BestS(int **a)
{
	int i,S,j,k,last_x,last_y;

	S = 0;

	// Pentru S - se determina numarul de celule eliberate 

	for(j = 0; j < 4; j++)
	{ 
		last_x = last_y = -1;
		
		for(i = 3; i > 0; i--)
			{
				if(a[i][j] != 0)
				{
					for(k = i-1; k > 0; k--)
					{
						if(a[k][j] != 0)
						break;
					}


				if(a[k][j] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = k;
					last_y = j;
					S++;
				}

				}
			}
	}

	return S;
}

int BestD(int **a)
{

	int i,D,j,k,last_x,last_y;

	D = 0;

	// Pentru D - se determina numarul de celule eliberate 

	for(i = 0; i < 4; i++)
	{ 
		last_x = last_y = -1;
		
		for(j = 3; j > 0; j--)
			{
				if(a[i][j] != 0)
				{
					for(k = j-1; k > 0; k--)
					{
						if(a[i][k] != 0)
						break;
					}


				if(a[i][k] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = i;
					last_y = k;
					D++;
				}

				}
			}
	}

	return D;

}
int BestMove(int **a )
{
	int i,W,A,S,D,j,k,last_x,last_y;

	W = A = S = D = 0;
    
    // Pentru W - se determina numarul de celule eliberate  

	for(j = 0; j < 4; j++)
	{ 
		last_x = last_y = -1;
		
		for(i = 0; i < 3; i++)
			{
				if(a[i][j] != 0)
				{
					for(k = i+1; k < 3; k++)
					{
						if(a[k][j] != 0)
						break;
					}


				if(a[k][j] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = k;
					last_y = j;
					W++;
				}

				}
			}
	}

	// Pentru S - se determina numarul de celule eliberate 

	for(j = 0; j < 4; j++)
	{ 
		last_x = last_y = -1;
		
		for(i = 3; i > 0; i--)
			{
				if(a[i][j] != 0)
				{
					for(k = i-1; k > 0; k--)
					{
						if(a[k][j] != 0)
						break;
					}


				if(a[k][j] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = k;
					last_y = j;
					S++;
				}

				}
			}
	}

	// Pentru A - se determina numarul de celule eliberate 

	for(i = 0; i < 4; i++)
	{ 
		last_x = last_y = -1;
		
		for(j = 0; j < 3; j++)
			{
				if(a[i][j] != 0)
				{
					for(k = j+1; k < 3; k++)
					{
						if(a[i][k] != 0)
						break;
					}


				if(a[i][k] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = i;
					last_y = k;
					A++;
				}

				}
			}
	}

	// Pentru D - se determina numarul de celule eliberate 

	for(i = 0; i < 4; i++)
	{ 
		last_x = last_y = -1;
		
		for(j = 3; j > 0; j--)
			{
				if(a[i][j] != 0)
				{
					for(k = j-1; k > 0; k--)
					{
						if(a[i][k] != 0)
						break;
					}


				if(a[i][k] == a[i][j] && (i != last_x || last_y != j))
				{
					last_x = i;
					last_y = k;
					D++;
				}

				}
			}
	}

	int max,dir,dirIfEqual;

	/*
	 variabila dir indica directia rezultata
	   W - 0
	   A - 1
	   S - 2
	   D - 3
	*/

	max = W;
	dir = 0;

	if( A > max )
		{max = A; dir = 1;}

	if( A == max)
		{  
			dirIfEqual = CoinFlip();
			if(dirIfEqual == 0)
				dir = 1;
		}

	if( S > max )
		{max = S; dir = 2;}

	if( S == max)
		{  
			dirIfEqual = CoinFlip();
			if(dirIfEqual == 0)
				dir = 2;
		}

	if( D > max )
		{max = D; dir = 3;}

	if( D == max)
		{  
			dirIfEqual = CoinFlip();
			if(dirIfEqual == 0)
				dir = 3;
		}
	
	return dir;
}
