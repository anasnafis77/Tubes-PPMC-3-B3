//Library yg dipake
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Implementasi saveProject
void saveProject(jalur pcb[][40], char filename[], int n, int m){
	FILE *flayout, *froute;
	char temp1, temp2, temp[3]; //Variabel temporer untuk menggabungkan char pcb.listrik.nama dan pcb.listrik.nomor
	char file[20]; //Variabel temporer untuk menyimpan sementara char filename[]
	
	strcpy(file, filename);
	flayout = fopen(strcat(file, "_layout.csv"), "w"); //Variabel file digunakan untuk eksternal file layout
	//Memindahkan isi array ke excel
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(pcb[i][j].listrik.nama == ' '){
				fprintf(flayout, ",");
			}
			else{
				//Menggabungkan char menjadi string
				temp1 = pcb[i][j].listrik.nama;
				temp2 = pcb[i][j].listrik.nomor;
				temp[0] = temp1;
				temp[1] = temp2;
				temp[2] = '\0';
				fprintf(flayout, "%s", temp);
			}
		}
	}
	fclose(flayout);
	froute = fopen(strcat(filename, "_routing.csv"), "w"); //filename digunakan untuk eksternal file routing
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			fprintf(flayout, ",");
			if(pcb[i][j].simbol == ' '){
				fprintf(froute, ",");
			}
			else{
				fprintf(froute, "%c", pcb[i][j].simbol);
			}
		}
	}
	fclose(froute);
	
	return;
}
