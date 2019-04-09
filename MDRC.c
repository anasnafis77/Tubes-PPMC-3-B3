#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variable.h"

int **DRC; 
int **Mpcb;
int Error;
char filename[8];
komponen *ComponentDRC;
jalur PeCeBe[40][40];//dummy

typedef struct {
	int x;
	int y;
} Koordinat; 

Koordinat ArrKorNode[7]; // [Vin,Vout,Vcc,GND,Vc,Vb,Ve] urutan koordinat
//masih bermasalah kalo ada simbol yang sama namun ga nyambung, solusi -> tambahin ( int node ) pada struct jalur.
int isConnected(jalur C, jalur D) {
	if (C.simbol == D.simbol) {
		return 1; 
	} else {
		return 0; 
	}
	
}

// J1 = Vin, J2 = Vout, J3 = VCC, T1 = Vb = Vc = Ve. //asumsi masukan nama komponen pada DRC selalu benar. jika berbeda kasih pesan error
void ShortComponent(jalur PCB[40][40], int **mpcb, komponen *KomponenDRC, int JmlKomponen, int *Kolom,int *Baris) { 
	mpcb = (int**) malloc ( JmlKomponen*sizeof(int*)); 
	for ( int i = 0; i < JmlKomponen; i++ ) {
		mpcb[i] = (int*) malloc ( 4 * sizeof(int*)); 
			for ( int j = 0; j < 4; j++ ) {
				mpcb[i][j] = 0; 
			}
	}
	int found;
	for( int I = 0; I < JmlKomponen ; I++ ) {
		found = 0; 
		for (int i = 0; i < *Baris; i++ ) {
			for (int j = 0; j < *Kolom; j++ ) {
				if ( PCB[i][j].listrik.nama == KomponenDRC[I].nama && PCB[i][j].listrik.nomor == KomponenDRC[I].nomor ) {
					found++;	
						if ( KomponenDRC[I].nama == 'J' && KomponenDRC[I].nomor == '1' ) {
							if ( found == 1 ) {
								mpcb[I][0] = 1;//Vin
								mpcb[I][1] = 3;//GND
								ArrKorNode[0].x = i; 
								ArrKorNode[0].y = j;
							} else if ( found == 2 ) {
								ArrKorNode[3].x = i; 
								ArrKorNode[3].y = j;
							
						} else if ( KomponenDRC[I].nama == 'J' && KomponenDRC[I].nomor == '2' ) {
							mpcb[I][0] = 2;//Vout
							mpcb[I][1] = 3;//GND
							ArrKorNode[1].x = i; 
							ArrKorNode[1].y = j;
						} else if ( KomponenDRC[I].nama == 'J' && KomponenDRC[I].nomor == '3' ) {
							mpcb[I][0] = 5;//VCC
							mpcb[I][1] = 3;//GND
							ArrKorNode[2].x = i; 
							ArrKorNode[2].y = j;
						} else if ( KomponenDRC[I].nama == 'T') {
							if ( found == 1 ) {
								mpcb[I][0] = 4;//Ve 
								mpcb[I][1] = 4;// Vb
								mpcb[I][2] = 4;//Vc
								ArrKorNode[4].x = i; 
								ArrKorNode[4].y = j;
							} else if ( found == 2 ) {
								ArrKorNode[5].x = i; 
								ArrKorNode[5].y = j;
							} else if ( found == 3 ) {
								ArrKorNode[6].x = i; 
								ArrKorNode[6].y = j;
							}
						}
						
						} else { //R dan C
							if (isConnected(PCB[i][j],PCB[ArrKorNode[0].x][ArrKorNode[0].y] ) == 1) {
								mpcb[I][found - 1] = 1;
							} else if (isConnected(PCB[i][j],PCB[ArrKorNode[1].x][ArrKorNode[1].y] ) == 1) {
								mpcb[I][found - 1] = 2;
							} else if (isConnected(PCB[i][j],PCB[ArrKorNode[2].x][ArrKorNode[2].y] ) == 1) {
								mpcb[I][found - 1] = 5; 
							} else if (isConnected(PCB[i][j],PCB[ArrKorNode[4].x][ArrKorNode[4].y] ) == 1 || isConnected(PCB[i][j], PCB[ArrKorNode[5].x][ArrKorNode[5].y] ) == 1  || isConnected(PCB[i][j], PCB[ArrKorNode[6].x][ArrKorNode[6].y]) == 1 ){
								mpcb[I][found - 1] = 4; 
							} else if (isConnected(PCB[i][j], PCB[ArrKorNode[3].x][ArrKorNode[3].y]) == 1 ) {
								mpcb[I][found - 1] = 3; 
						}
					}	
							
				if ( KomponenDRC[I].nama == 'T' ) {
					if ( found == 3 ) { break;}
				} else if ( KomponenDRC[I].nama == 'J' && KomponenDRC[I].nomor != '1') {
					if ( found == 1 ) { break;}
				} else { //J1, R, dan C
					if ( found == 2 ) { break;}
				}
			}
			if ( KomponenDRC[I].nama == 'T' ) {
				if ( found == 3 ) { break;}
			} else if ( KomponenDRC[I].nama == 'J' && KomponenDRC[I].nomor != '1') {
				if ( found == 1 ) { break;}
			} else { //J1, R, dan C
				if ( found == 2 ) { break;}
			}
		}
		if ( found < 2 ) {
			printf("Rangkaian File DRC tidak sesuai!\n");
			break;
		}
		printf("\n");
	}
			
}
}

int SearchError(int **mpcb, int **drc, int JmlKomponen) {
		int found;
		int k;
		int j;
		int E = 0;
		for (int i = 0; i < JmlKomponen; i++ ) {
			j = 0;
			while( j < 4 ) {
				found = 0;
				k = 0;
				while( found == 0 && k < 4){
					if ( drc[i][j] == mpcb[i][k] ) {
						found = 1; 
					}
					k++;
				}
				j++;
				if (found == 0) {
					E++;
					break;
				}
			}
		}
return E;
}

char string[5];
char c;
int i, j, JumlahKomponen;

void MDRC (int n, int m, jalur pcb[40][40]) {
	printf("[DRC]\n");
	printf("Masukkan File DRC (dalam format .txt): ");
	scanf("\n");
    scanf("%[^\n]%*c", filename);
 
	FILE * fp;
	fp = fopen(filename,"r");
	DRC = (int**) malloc (sizeof(int*));
	DRC[0] = (int*) malloc (4 * sizeof(int*));

	ComponentDRC = (komponen*) malloc (sizeof(komponen*));


	c = 'x';
	i = 0;
	while (!feof(fp))  {
		j = 0;
		for (int k = 0; k < 4; k++ ) {
			DRC[i][k] = 0; 
		}
		while(1) {
			fscanf(fp, "%s", string);
			
				if (strcmp(string, "Vin") == 0) {
					DRC[i][j++] = 1; 
				} else if (strcmp(string, "Vout") == 0) {
					DRC[i][j++] = 2;
				} else if (strcmp(string, "GND") == 0) {
					DRC[i][j++] = 3; 
				} else if (strcmp(string, "Vc") == 0) {
					DRC[i][j++] = 4;
				} else if (strcmp(string, "Vb") == 0) {
					DRC[i][j++] = 4;
				} else if (strcmp(string, "Ve") == 0) {
					DRC[i][j++] = 4;
				} else if (strcmp(string, "VCC") == 0) {
					DRC[i][j++] = 5;
				} else {
					ComponentDRC[i].nama = string[0];
					ComponentDRC[i].nomor = string[1];
				}
			c = fgetc(fp);
			if ( c == '\n') {
				i++;
				DRC = (int**) realloc ( DRC,(i + 1)*sizeof(int*));
				DRC[i] = (int*) malloc (4 * sizeof(int*));
				ComponentDRC = (komponen*) realloc ( ComponentDRC,(i + 1)*sizeof(komponen*));
				break;
			}
			if (feof(fp)) {
				break;
			}
		}
	}
	
	JumlahKomponen = i + 1; 

	ShortComponent(pcb, Mpcb, ComponentDRC, JumlahKomponen, &n, &m);
	
	Error = SearchError(DRC, Mpcb, JumlahKomponen);
	
	printf("%d/%d Rule is Checked", JumlahKomponen - Error, JumlahKomponen); 

	free(ComponentDRC);
	free(Mpcb);
	free(DRC);
	fclose(fp);
	
}

