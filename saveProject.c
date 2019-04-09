//Library yg dipake
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//Implementasi saveProject
void saveProject(jalur pcb[][40], char filename[], int neff){
	FILE *fptr;
	char (*c[2])[160];
	int k = 0;
	
	strcat(filename, ".csv");
	fptr = fopen(filename, "w");
	/* Bagian ini bisa dicompile, tapi keluaran masih salah
	for(int i = 0; i < neff; i++){
		for(int j = 0; j < neff; j++){
			(*c[0])[k] = pcb[i][j].listrik.nama;
			(*c[1])[k] = pcb[i][j].listrik.nomor;
			(*c[2])[k] = '\0';
			k++;
		}
	} */
	//Memindahkan isi array ke excel
	for(int i = 0; i < neff; i++){
		for(int j = 0; j < neff; j++){
			if(!isspace(pcb[i][j].listrik.nama)){
				printf("%c%c ", pcb[i][j].listrik.nama, pcb[i][j].listrik.nomor);
				fprintf(fptr, "%c", pcb[i][j].listrik.nama);
				fprintf(fptr, "%c", pcb[i][j].listrik.nomor);
				fprintf(fptr, ",");
			}
			else{
				fprintf(fptr, ", ,");
			}
		}
		printf("\n");
		fprintf(fptr, "\n");
	}
	fprintf(fptr, "\n");
	for(int i = 0; i < neff; i++){
		for(int j = 0; j < neff; j++){
			if(!isspace(pcb[i][j].simbol)){
				printf("%c", pcb[i][j].simbol);
				fprintf(fptr, "%c,", pcb[i][j].simbol);
			}
			else{
				fprintf(fptr, ", ,");
			}
		}
		printf("\n");
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	
	return;
}
