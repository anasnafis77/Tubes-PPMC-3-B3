#include <stdio.h>
#include "lib.h"
#include <math.h>

void make_layout(int n, int m,jalur pcb[40][40], int *x) { /*x nya itu int count ya */
	komponen masuk;
	int inp_x1, inp_y1, inp_x2, inp_y2,i,j;
	double jarak;
	
	*x=0;
	
	for (j=0; j<m; j+=1) {
		for(i=0; i<n ; i+=1){
			pcb[i][j].listrik.nama = ' ';
			pcb[i][j].listrik.nomor = ' ';
		}
	}
	
	printf("[Mode Layout]\n");
	printf("Isi 'q' atau 'Q' untuk kembali ke menu\n"); /*WARNING!!! MASUKKAN JUGA ANGKA SETELAH Q ATAU q */

	printf("Pilih Komponen (R,C,T,J): "); scanf("%c%c", &masuk.nama, &masuk.nomor);/*asumsi tidak ada nama komponen yang diulang*/
	while(!(masuk.nama == 'q' || masuk.nama == 'Q')){ /*jika dia q atau Q maka stop*/
		if(masuk.nama == 'R' || masuk.nama=='C' || masuk.nama=='J' || masuk.nama=='T') { /*jika bukan 4 karakter ini maka muncul error message*/
			printf("Koordinat kaki 1 : "); scanf(" %d%*c%d", &inp_x1, &inp_y1);
			printf("Koordinat kaki 2 : "); scanf(" %d%*c%d", &inp_x2, &inp_y2);	
			if(inp_x1 > n || inp_x2 > n || inp_y1 > m || inp_y2 > m) {/*jika di luar range maka muncul error message*/
				printf("Input salah. Masukkan lagi.\n");
				printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
			}
			else {
				jarak = sqrt(((inp_x2-inp_x1)*(inp_x2-inp_x1)) + ((inp_y2-inp_y1)*(inp_y2 - inp_y1)) );
				if(masuk.nama == 'R' && (jarak >= 4) )
				{
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else if (masuk.nama == 'C' && (jarak>=2)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else if (masuk.nama == 'T' && (jarak>=2)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else if (masuk.nama == 'J' && (jarak>=1)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else {
					printf("Input salah. Masukkan lagi.\n");
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
			}
			
		}
		else {	
		printf("Koordinat kaki 1 : "); scanf(" %d%*c%d", &inp_x1, &inp_y1);
		printf("Koordinat kaki 2 : "); scanf(" %d%*c%d", &inp_x2, &inp_y2);	
		printf("Input salah. Masukkan lagi. \n");
		printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
		}
	}

}


void print_layout(int n, int m, jalur pcb[40][40]){
	int i,j;
	
	for (i=0; i<n; i+=1){
		printf("	%d", i+1);
	}
	printf("\n");
	
	for (j=0; j<m; j+=1) {
		printf("%d	", j+1);
		for(i=0; i<n ; i+=1){
			printf("%c%c	", pcb[i][j].listrik.nama, pcb[i][j].listrik.nomor);
		}
		printf("\n");
	}
	
}

void auto_layout(jalur pcb [40][40]) {
	pcb[4][0].listrik.nama = 'R';
	pcb[4][0].listrik.nomor = '1';
	pcb[4][4].listrik.nama = 'R';
	pcb[4][4].listrik.nomor = '1';
	
	pcb[5][0].listrik.nama = 'J';
	pcb[5][0].listrik.nomor = '3';
	pcb[5][9].listrik.nama = 'J';
	pcb[5][9].listrik.nomor = '3';
	
	pcb[6][5].listrik.nama = 'C';
	pcb[6][5].listrik.nomor = '1';
	pcb[8][5].listrik.nama = 'C';
	pcb[8][5].listrik.nomor = '1';
	
	pcb[6][6].listrik.nama = 'T';
	pcb[6][6].listrik.nomor = '1';
	pcb[6][8].listrik.nama = 'T';
	pcb[6][8].listrik.nomor = '1';
	
	pcb[6][0].listrik.nama = 'R';
	pcb[6][0].listrik.nomor = '2';
	pcb[6][4].listrik.nama = 'R';
	pcb[6][4].listrik.nomor = '2';
	
	pcb[4][5].listrik.nama = 'R';
	pcb[4][5].listrik.nomor = '3';
	pcb[4][9].listrik.nama = 'R';
	pcb[4][9].listrik.nomor = '3';
	
	pcb[7][8].listrik.nama = 'R';
	pcb[7][8].listrik.nomor = '4';
	pcb[7][11].listrik.nama = 'R';
	pcb[7][11].listrik.nomor = '4';
	
	pcb[9][5].listrik.nama = 'J';
	pcb[9][5].listrik.nomor = '2';
	pcb[5][10].listrik.nama = 'J';
	pcb[5][10].listrik.nomor = '2';
	
	pcb[0][4].listrik.nama = 'J';
	pcb[0][4].listrik.nomor = '1';
	pcb[5][11].listrik.nama = 'J';
	pcb[5][11].listrik.nomor = '1';
	
	pcb[1][4].listrik.nama = 'C';
	pcb[1][4].listrik.nomor = '2';
	pcb[3][4].listrik.nama = 'C';
	pcb[3][4].listrik.nomor = '2';
	
	pcb[8][8].listrik.nama = 'C';
	pcb[8][8].listrik.nomor = '3';
	pcb[8][10].listrik.nama = 'C';
	pcb[8][10].listrik.nomor = '3';
	
}

void auto_routing(jalur pcb[40][40]) {
	pcb[4][0].simbol = '*';
	pcb[5][0].simbol = '*';
	pcb[6][0].simbol = '*';
	
	pcb[0][4].simbol = '!';
	pcb[1][4].simbol = '!';
	
	pcb[3][4].simbol = '@';
	pcb[4][4].simbol = '@';
	pcb[4][5].simbol = '@';
	
	pcb[6][4].simbol = '#';
	pcb[6][5].simbol = '#';
	pcb[6][6].simbol = '#';
	
	pcb[8][5].simbol = '$';
	pcb[9][5].simbol = '$';
	
	pcb[6][8].simbol = '%';
	pcb[7][8].simbol = '%';
	pcb[8][8].simbol = '%';
	
	pcb[4][9].simbol = '^';
	pcb[5][9].simbol = '^';
	pcb[5][10].simbol = '^';
	pcb[5][11].simbol = '^';
	pcb[6][11].simbol = '^';
	pcb[7][11].simbol = '^';
	pcb[8][11].simbol = '^';
	pcb[8][10].simbol = '^';
}
