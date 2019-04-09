//Library yg dipake
#include <stdio.h>
#include <string.h>

//Implementasi saveProject
void saveProject(jalur pcb[][40], char filename[], int neff){
	FILE *fptr;
	
	strcat(filename, ".csv");
	fptr = fopen(filename, "w");
	//Memindahkan isi array ke excel
	for(int i = 0; i < neff; i++){
		for(int j = 0; j < neff; j++){
			fprintf(fptr, "%c%c", pcb[i][j].listrik.nama, pcb[i][j].listrik.nomor);
		}
	}
	fprintf(fptr, "\n");
	for(int i = 0; i < neff; i++){
		for(int j = 0; j < neff; j++){
			fprintf(fptr, "%c", pcb[i][j].simbol);
		}
	}
	fclose(fptr);
	
	return;
}
