#include <stdio.h>
#include <stdbool.h>
#include "lib.h"
#include <math.h>

void make_layout(int n, int m,jalur pcb[40][40]) {
	komponen masuk;
	int inp_x1, inp_y1, inp_x2, inp_y2,i,j;
	double jarak;
	
	for (j=0; j<m; j+=1) {
		for(i=0; i<n ; i+=1){
			pcb[i][j].listrik.nomor = NULL;
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
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else if (masuk.nama == 'C' && (jarak>=2)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else if (masuk.nama == 'T' && (jarak>=2)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
				}
				else if (masuk.nama == 'J' && (jarak>=1)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
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

int main () {
	
	make_layout(5,10, pcb);
	
	print_layout(5,10,pcb);
	
	return 0;
}
