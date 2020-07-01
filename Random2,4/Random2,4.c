#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int RNG()
{
	int x;

	// in x se va retine 2 sau 4
	// cu o sansa mai mare de a pica 2

	x = rand() % 3;

	if(x == 2)
		return 4;
	else
		return 2;

	// pentru 0,1 se va intoarce 2, iar pentru 2 se va intoarce 4
	// adica o sansa de aproximativ 66% de a pica 2
}
