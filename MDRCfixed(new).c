//ASUMSI : 
//1. J1 = Vin, J2 = VOUT, J3 = VCC, T1 = VB = VC = VE
//2. Simbol untuk jalur yang tidak nyambung harus berbeda
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variable.h"

int **DRC; 
int **Mpcb;
int Error;
char string[5];
char c;
int i, j, JumlahKomponen;
char filename[8];
komponen *ComponentDRC;

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

//Merubah matriks PCB menjadi matriks MPCB
// J1 = Vin, J2 = Vout, J3 = VCC, T1 = Vb = Vc = Ve. asumsi masukan nama komponen pada DRC selalu benar. jika berbeda nama, kasih pesan error
int **ShortComponent(jalur PCB[40][40], komponen *KomponenDRC, int JmlKomponen, int *Kolom,int *Baris) { 
	int **mpcb;
	mpcb = (int**) malloc ( JmlKomponen*sizeof(int*)); 
	for ( int i = 0; i < JmlKomponen; i++ ) {
		mpcb[i] = (int*) malloc ( 4 * sizeof(int*)); 
			for ( int j = 0; j < 4; j++ ) {
				mpcb[i][j] = 0; 
			}
	}
	//inisiasi node
	komponen Node[3];
	Node[0].nama = 'J';
	Node[0].nomor = '1';
	Node[1].nama = 'J';
	Node[1].nomor = '2';
	Node[2].nama = 'J';
	Node[2].nomor = '3';
	Node[3].nama = 'T';
	Node[3].nomor = '1';
	
	//Mencari koordinat node pada PCB
	int found;
	for( int I = 0; I < 3 ; I++ ) {
		found = 0; 
		for (int i = 0; i < *Baris; i++ ) {
			for (int j = 0; j < *Kolom; j++ ) {
				if ( PCB[i][j].listrik.nama == Node[I].nama && PCB[i][j].listrik.nomor == Node[I].nomor ) {
					found++;	
						if ( (Node[I].nama == 'J') && (Node[I].nomor == '1') ) {
							if ( found == 1 ) { //Vin
								ArrKorNode[0].x = i; 
								ArrKorNode[0].y = j;
								
							} else if ( found == 2 ) {//GND
								ArrKorNode[3].x = i; 
								ArrKorNode[3].y = j;
								
							}
						} else if ( (Node[I].nama == 'J') && (Node[I].nomor == '2') ) {
							if ( found == 1 ) {
								ArrKorNode[1].x = i;//Vout
								ArrKorNode[1].y = j;
								
							} 
						} else if ( (Node[I].nama == 'J') && (Node[I].nomor == '3') ) {
							if ( found == 1 ) {
								ArrKorNode[2].x = i; //VCC
								ArrKorNode[2].y = j;
								
							} 
						} else if ( Node[I].nama == 'T') {
							if ( found == 1 ) {
								ArrKorNode[4].x = i; // Vc
								ArrKorNode[4].y = j;
								
							} else if ( found == 2 ) {
								ArrKorNode[5].x = i; //Vb
								ArrKorNode[5].y = j;
								
							} else if ( found == 3 ) {
								ArrKorNode[6].x = i; //Ve
								ArrKorNode[6].y = j;
							
							}
						} 
					}	
				//Penanganan terminasi loop 1		
				if ( Node[I].nama == 'T' ) {
					if ( found == 3 ) { break;}
				} else { 
					if ( found == 2 ) { break;}
				}
			}
			//Penanganan terminasi	loop 2
			if ( Node[I].nama == 'T' ) {
				if ( found == 3 ) { break;}
			} else { //J, R, dan C
				if ( found == 2 ) { break;}
			}
		}
	
	}
	
	//Search Component in PCB, Mengisi matriks MPCB
	for( int I = 0; I < JmlKomponen ; I++ ) {
		found = 0; 
		for (int i = 0; i < *Baris; i++ ) {
			for (int j = 0; j < *Kolom; j++ ) {
				if ( PCB[i][j].listrik.nama == KomponenDRC[I].nama && PCB[i][j].listrik.nomor == KomponenDRC[I].nomor ) {
					found++;	

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
						
						
						} else { // u/ kasus R dan C. Node ditentukan melalui pemeriksaan konektivitas thd Node yang sudah ditentukan sebelumnya
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
				//Penanganan kasus terminasi loop 2
				if ( KomponenDRC[I].nama == 'T' ) {
					if ( found == 3 ) { break;}
				} else { //J, R, dan C
					if ( found == 2 ) { break;}
				}
			}
			//Penangan kasus terminasi loop 1
			if ( KomponenDRC[I].nama == 'T' ) {
				if ( found == 3 ) { break;}
			} else { //J, R, dan C
				if ( found == 2 ) { break;}
			}
		}
	}
		// Jika PCB tidak memiliki komponen pada file DRC, misal DRC u/ Filter sederhana digunakan pada Rangkaian Common Emiter
		if ( found <= 1 ) {
			printf("File DRC tidak sesuai dengan rangkaian!\n");
		break;
		}
	}
	return mpcb; 
}
//Mencari error pada matriks DRC dan MPCB
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
			//penanganan kasus galat
			for ( int j = 0; j < 4; j++ ) {
				sumDRC = drc[i][j] + sumDRC; 
				sumPCB = mpcb[i][j] + sumPCB;
			}
			//jika penangan kasus galat bernilai true
			if ( sumDRC == sumPCB ){
				while( j < 4 ) {
					found = 0;
					k = 0;
					//membandingkan elemen tiap baris pada Matriks DRC dengan MPCB satu-satu dengan iterasi elemen DRC
					while( found == 0 && k < 4){
						if ( drc[i][k] == mpcb[i][j] ) {
							found = 1; 
						}
						k++;
					}
					j++;
					//Jika elemen DRC tidak ditemukan pada baris I
					if (found == 0) {
						E++;
					break;
					}
				}
			//jika penanganan kasus galat bernilai false
			} else { E++; } 
		}
return E;
}

//program utama
int MDRC(jalur PCB[40][40], int n, int m) {
	//masukan nama file DRC
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
	//Mengubah bentuk file DRC ke Matriks DRC
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
	
	Mpcb = ShortComponent(PCB,ComponentDRC, JumlahKomponen, &n, &m);
	Error = SearchError(DRC, Mpcb, JumlahKomponen);
	
	printf("%d/%d Rule is Checked", JumlahKomponen - Error, JumlahKomponen); 
	
	free(ComponentDRC);
	free(Mpcb);
	free(DRC);
	fclose(fp);
	return 0;
}

