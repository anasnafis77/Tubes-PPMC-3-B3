#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variable.h"

int **DRC; 
int **Mpcb;
int Error;
char filename[8];
komponen *ComponentDRC;
jalur PCB[40][40];//dummy

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
int g = 0;
// J1 = Vin, J2 = Vout, J3 = VCC, T1 = Vb = Vc = Ve. //asumsi masukan nama komponen pada DRC selalu benar. jika berbeda kasih pesan error

int **ShortComponent(jalur PCB[40][40], komponen *KomponenDRC, int JmlKomponen, int *Kolom,int *Baris, int g) { 
	int **mpcb;
	mpcb = (int**) malloc ( JmlKomponen*sizeof(int*)); 
	for ( int i = 0; i < JmlKomponen; i++ ) {
		mpcb[i] = (int*) malloc ( 4 * sizeof(int*)); 
			for ( int j = 0; j < 4; j++ ) {
				mpcb[i][j] = 0; 
			}
	}
	komponen Node[3];
	Node[0].nama = 'J';
	Node[0].nomor = '1';
	Node[1].nama = 'J';
	Node[1].nomor = '2';
	Node[2].nama = 'J';
	Node[2].nomor = '3';
	Node[3].nama = 'T';
	Node[3].nomor = '1';
	
	//Search Koordinat Node
	int found;
	printf("\nSearching Node...\n");
	for( int I = 0; I < 3 ; I++ ) {
		found = 0; 
		for (int i = 0; i < *Baris; i++ ) {
			for (int j = 0; j < *Kolom; j++ ) {
				if ( PCB[i][j].listrik.nama == Node[I].nama && PCB[i][j].listrik.nomor == Node[I].nomor ) {
					found++;	
						if ( (Node[I].nama == 'J') && (Node[I].nomor == '1') ) {
							if ( found == 1 ) {
								ArrKorNode[0].x = i; 
								ArrKorNode[0].y = j;
								printf("Node Vin found\n");
							} else if ( found == 2 ) {//GND
								ArrKorNode[3].x = i; 
								ArrKorNode[3].y = j;
								printf("Node GND found\n");
							}
						} else if ( (Node[I].nama == 'J') && (Node[I].nomor == '2') ) {
							if ( found == 1 ) {
								ArrKorNode[1].x = i; 
								ArrKorNode[1].y = j;
								printf("Node Vout found\n");
							} 
						} else if ( (Node[I].nama == 'J') && (Node[I].nomor == '3') ) {
							if ( found == 1 ) {
								ArrKorNode[2].x = i; 
								ArrKorNode[2].y = j;
								printf("Node VCC found\n");
							} 
						} else if ( Node[I].nama == 'T') {
							if ( found == 1 ) {
								ArrKorNode[4].x = i; 
								ArrKorNode[4].y = j;
								printf("Node Vc found\n");
							} else if ( found == 2 ) {
								ArrKorNode[5].x = i; 
								ArrKorNode[5].y = j;
								printf("Node Vb found\n");
							} else if ( found == 3 ) {
								ArrKorNode[6].x = i; 
								ArrKorNode[6].y = j;
								printf("Node Ve found\n");
							}
						} 
					}	
							
				if ( Node[I].nama == 'T' ) {
					if ( found == 3 ) { break;}
				} else { 
					if ( found == 2 ) { break;}
				}
			}
			if ( Node[I].nama == 'T' ) {
				if ( found == 3 ) { break;}
			} else { //J, R, dan C
				if ( found == 2 ) { break;}
			}
		}
	
	}
	printf("\nSearching Node Complete!\n");
				
	for( int I = 0; I < JmlKomponen ; I++ ) {
		printf("\nSearching component : %c%c. Please wait...\n", KomponenDRC[I].nama,KomponenDRC[I].nomor );
		found = 0; 
		for (int i = 0; i < *Baris; i++ ) {
			for (int j = 0; j < *Kolom; j++ ) {
				if ( PCB[i][j].listrik.nama == KomponenDRC[I].nama && PCB[i][j].listrik.nomor == KomponenDRC[I].nomor ) {
					found++;	
					printf("%d component has found\n",found);
						if ( (KomponenDRC[I].nama == 'J') && (KomponenDRC[I].nomor == '1') ) {
							if ( found == 1 ) {
								mpcb[I][found - 1] = 1;//Vin
								ArrKorNode[0].x = i; 
								ArrKorNode[0].y = j;
							} else if ( found == 2 ) {//GND
								mpcb[I][found - 1] = 3;
								ArrKorNode[3].x = i; 
								ArrKorNode[3].y = j;
							}
						} else if ( (KomponenDRC[I].nama == 'J') && (KomponenDRC[I].nomor == '2') ) {
							if ( found == 1 ) {
								mpcb[I][found-1] = 2;//Vout
								ArrKorNode[1].x = i; 
								ArrKorNode[1].y = j;
							} else if ( found == 2 ) {
								mpcb[I][found-1] = 3;//GND
							}
						} else if ( (KomponenDRC[I].nama == 'J') && (KomponenDRC[I].nomor == '3') ) {
							if ( found == 1 ) {
								mpcb[I][found-1] = 5;//VCC
								ArrKorNode[2].x = i; 
								ArrKorNode[2].y = j;
							} else if ( found == 2 ) {
								mpcb[I][found-1] = 3;
							}
						} else if ( KomponenDRC[I].nama == 'T') {
							if ( found == 1 ) {
								mpcb[I][found-1] = 4;//Ve 
								ArrKorNode[4].x = i; 
								ArrKorNode[4].y = j;
							} else if ( found == 2 ) {
								mpcb[I][found-1] = 4;// Vb
								ArrKorNode[5].x = i; 
								ArrKorNode[5].y = j;
							} else if ( found == 3 ) {
								mpcb[I][found-1] = 4;//Vc
								ArrKorNode[6].x = i; 
								ArrKorNode[6].y = j;
							}
						
						
						} else { //R dan C
							if (isConnected(PCB[i][j],PCB[ ArrKorNode [0].x][ArrKorNode[0].y] ) == 1) {//Vin
								mpcb[I][found - 1] = 1;
							} else if (isConnected(PCB[i][j],PCB[ArrKorNode[1].x][ArrKorNode[1].y] ) == 1) {//Vout
								mpcb[I][found - 1] = 2;
							} else if (isConnected(PCB[i][j],PCB[ArrKorNode[2].x][ArrKorNode[2].y] ) == 1) {//Vcc
								mpcb[I][found - 1] = 5; 
							} else if (isConnected(PCB[i][j],PCB[ArrKorNode[4].x][ArrKorNode[4].y] ) == 1 || isConnected(PCB[i][j], PCB[ArrKorNode[5].x][ArrKorNode[5].y] ) == 1  || isConnected(PCB[i][j], PCB[ArrKorNode[6].x][ArrKorNode[6].y]) == 1 ){
								mpcb[I][found - 1] = 4; //Ve, Vb, Vc
							} else if (isConnected(PCB[i][j], PCB[ArrKorNode[3].x][ArrKorNode[3].y]) == 1 ) {//GND
								mpcb[I][found - 1] = 3; 
						}
					}	
							
				if ( KomponenDRC[I].nama == 'T' ) {
					if ( found == 3 ) { break;}
				} else { //J, R, dan C
					if ( found == 2 ) { break;}
				}
			}
			if ( KomponenDRC[I].nama == 'T' ) {
				if ( found == 3 ) { break;}
			} else { //J, R, dan C
				if ( found == 2 ) { break;}
			}
		}
	}
	
		if ( found <= 1 ) {
			printf("Rangkaian File DRC tidak sesuai!\n");
			g = 1; 
		break;
		}
	}
	return mpcb; 
}

int SearchError(int **mpcb, int **drc, int JmlKomponen) {
		int found;
		int k;
		int j;
		int E = 0;
		int sumDRC, sumPCB;
		for (int i = 0; i < JmlKomponen; i++ ) {
			j = 0;
			sumDRC = 0;
			sumPCB = 0;
			for ( int j = 0; j < 4; j++ ) {
				sumDRC = drc[i][j] + sumDRC; 
				sumPCB = mpcb[i][j] + sumPCB;
			}
			if ( sumDRC == sumPCB ){
				while( j < 4 ) {
					found = 0;
					k = 0;
					while( found == 0 && k < 4){
						if ( drc[i][k] == mpcb[i][j] ) {
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
			} else { E++; } 
		}
return E;
}

char string[5];
char c;
int i, j, JumlahKomponen;
int n, m; //dummy

int MDRC() {
	printf("[DRC]\n");
	printf("Masukkan File DRC (dalam format .txt): ");
	scanf("\n");
    scanf("%[^\n]%*c", filename);
	n = 20;
	m = 10;
	FILE * fp;
	fp = fopen(filename,"r");
	DRC = (int**) malloc (sizeof(int*));
	DRC[0] = (int*) malloc (4 * sizeof(int*));

	ComponentDRC = (komponen*) malloc (sizeof(komponen*));
	//dummy
	PCB[2][3].listrik.nama = 'R';
	PCB[2][3].listrik.nomor = '1';
	PCB[2][7].listrik.nama = 'R';
	PCB[2][7].listrik.nomor = '1';
	PCB[2][8].listrik.nama = 'C';
	PCB[2][8].listrik.nomor = '1';
	PCB[4][8].listrik.nama = 'C';
	PCB[4][8].listrik.nomor = '1';
	PCB[2][2].listrik.nama = 'J';
	PCB[2][2].listrik.nomor = '1';
	PCB[4][2].listrik.nama = 'J';
	PCB[4][2].listrik.nomor = '1';
	PCB[2][9].listrik.nama = 'J';
	PCB[2][9].listrik.nomor = '2';
	PCB[4][9].listrik.nama = 'J';
	PCB[4][9].listrik.nomor = '2';
	PCB[2][10].listrik.nama = 'J';
	PCB[2][10].listrik.nomor = '3';
	PCB[4][10].listrik.nama = 'J';
	PCB[4][10].listrik.nomor = '3';
	for ( int j  = 2; j < 10; j++ ) {
		PCB[4][j].simbol = '!'; 
	}
	for ( int j = 2; j < 4; j ++ ) {
		PCB[2][j].simbol = '!'; 
	}
	for ( int j = 7; j < 10; j++ ) {
		PCB[2][j].simbol = '@'; 
	}
	
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
	
	JumlahKomponen = i ; 
	
	Mpcb = ShortComponent(PCB,ComponentDRC, JumlahKomponen, &n, &m, g);
	if ( g == 1 ) {
		return 0; 
	}
	
	printf("\nThis is DRC\n");
	
	for ( int i = 0; i < JumlahKomponen; i++ ) {
		for ( int j = 0; j < 4; j++) {
			printf("%d ", DRC[i][j]);
		}
	printf("\n");
	}
	
	printf("\nThis is MPCB\n");
	for ( int i = 0; i < JumlahKomponen; i++ ) {
		for ( int j = 0; j < 4; j++) {
			printf("%d ", Mpcb[i][j]);
		}
	printf("\n");
	}

	Error = SearchError(DRC, Mpcb, JumlahKomponen);
	
	printf("%d/%d Rule is Checked", JumlahKomponen - Error, JumlahKomponen); 
	
	free(ComponentDRC);
	free(Mpcb);
	free(DRC);
	fclose(fp);
	return 0;
}

