//Library yg dipake
#include <stdio.h>
#include <string.h>

//Implementasi saveProject
void saveProject(jalur pcb[][40], char filename[], int n, int m){
	FILE *flayout, *froute;
	char temp1, temp2, temp[3];
	char file[20];
	
	strcpy(file, filename);
	flayout = fopen(strcat(file, "_layout.csv"), "w");
	//Memindahkan isi array ke excel
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			temp1 = pcb[i][j].listrik.nama;
			temp2 = pcb[i][j].listrik.nomor;
			temp[0] = temp1;
			temp[1] = temp2;
			temp[2] = '\0';
			fprintf(flayout, "%s", temp);
		}
	}
	fclose(flayout);
	froute = fopen(strcat(filename, "_routing.csv"), "w");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			fprintf(flayout, "%c", pcb[i][j].simbol);
		}
	}
	fclose(froute);
	
	return;
}
