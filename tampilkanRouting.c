//3. Tampilkan Routing
#include <stdio.h>
#include "variable.h"

void main ()
{
	int i,j;
	for (i=0;i<40;i++)
	{
		for (j=0;j<40;j++)
		{
			printf ("%c  ",pcb[i][j].simbol);
		}
		printf (" \n");
	}
}
