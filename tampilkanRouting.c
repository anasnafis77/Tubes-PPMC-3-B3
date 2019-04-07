//3. Tampilkan Routing
#include <stdio.h>
#include "variable.h"

void tampilkanRouting(int n, int m, jalur pcb[40][40]){
	int i,j;
	
	for (i=0; i<n; i+=1){
		printf("	%d", i+1);
	}
	printf("\n");
	
	for (j=0; j<m; j+=1) {
		printf("%d	", j+1);
		for(i=0; i<n ; i+=1){
			printf("%c	", pcb[i][j].listrik.simbol);
		}
		printf("\n");
	}
	
}
