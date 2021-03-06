#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct {//nama komponen yang terdiri atas huruf simbol komponen dan nomor komponen
	char nama;
	char nomor;
}komponen;

typedef struct {//tipe data untuk menyatakan komponen dan simbol jalur pada PCB
	komponen listrik;
	char simbol;
}jalur;

typedef struct 
{
	int x,y;
} koordinat;

jalur pcb[40][40]; //matriks PCB 

char fileName[20];
int n, m, pilihan, menu, count = 0;
int validasi;
char sym;

//deklarasi fungsi
void halamanAwal();
void pilihanHalaman();
void menuUtama();
void pilihanMenu();
void cobaRouting();
void simpanSymbol (int n, int m, jalur pcb[40][40]);
void make_layout(int n, int m,jalur pcb[40][40], int *x);
void tampilkanRouting(int n, int m, jalur pcb[40][40]);
void print_layout(int n, int m, jalur pcb[40][40]);
void auto_layout(jalur pcb [40][40]);
void auto_routing(jalur pcb[40][40]);


int main ()
{	
	int i,j;
	for (j=0; j<m; j+=1) 
	{
		for(i=0; i<n ; i+=1)
		{
			pcb[i][j].listrik.nama = ' ';
			pcb[i][j].listrik.nomor = ' ';
		}
	}
	do 
	{
	halamanAwal();
	}
	while (pilihan < 1 || pilihan > 3);
	pilihanHalaman();
	 
	return (0);
}

void pilihanHalaman()
{
	if (pilihan == 1)
		{
			do
			{
			printf ("========= Membuat Proyek Baru =========\n");
			printf ("Masukkan nama proyek : ");
			scanf("%s",&fileName);
			do 
			{
				printf ("Masukkan ukuran PCB NxM (N dan M <40) : ");
				scanf (" %d", &n);
				scanf(" %d", &m);
			}while (!(n>0 && n<40)||!(m>0 && m<40));
			menuUtama ();
			} while (menu<1 || menu > 8);	
			pilihanMenu ();	
		} else if (pilihan == 2)
		{
			do
			{
			printf ("========= Mengubah File Lama =========\n");
			printf ("Masukkan nama proyek : ");
			scanf("%s",&fileName);
			menuUtama();
			} while (menu<1 || menu > 8);	
			pilihanMenu ();
			
		} else if (pilihan == 3)
		{
			return;
		}
}

void pilihanMenu()
{
	switch (menu) 
			{
				case 1 :print_layout(n,m,pcb);
						printf ("\n");
						menuUtama ();
						pilihanMenu ();
					break;
				case 2 : make_layout(n, m, pcb, &count);
						printf ("\n");
						menuUtama ();
						pilihanMenu ();
					break;
				case 3 :tampilkanRouting (n, m, pcb);
						printf ("\n");
 						menuUtama ();
						pilihanMenu ();
					break;
				case 4 :
						if (validasi!=1)
						{
							printf ("Layouting manual belum dilakukan\n\n");						
						}else
						{
							cobaRouting();
							printf ("\n");
						}
						menuUtama ();
						pilihanMenu ();	
					break;
				case 5 :auto_layout(pcb);
						printf ("\n");
						menuUtama ();
						pilihanMenu ();
					break;
				case 6 :auto_routing(pcb);
						printf ("\n");
						menuUtama ();
						pilihanMenu ();
					break;
				case 7 :
						printf ("\n");
						menuUtama ();;
						pilihanMenu ();
					break;
				case 8 : halamanAwal();
						 pilihanHalaman();
					break;
			}			
	
}


void halamanAwal ()
// prosedur untuk menampilkan menu utama
{ 
	printf ("-------------------------**********------------------------\n");
	printf ("*                    SIMULASI DESAIN PCB                   *\n");
	printf ("-------------------------**********------------------------\n\n");
	printf ("MENU : \n"); 
	printf ("*isi pilihan dengan nomor pilihan \n\n");
	printf (" 1. Buat Proyek Baru \n 2. Muat Proyek dari Berkas \n 3. Keluar\n");
	printf ("Masukkan pilihan anda : ");
	scanf ("%d", &pilihan);
	printf ("\n\n");
	return;
}

void menuUtama ()
// prosedur menampilkan pilihan menu utama
{
	printf ("	[Menu utama]	\n");
	printf ("1. Tampilkan layout \n");
	printf ("2. Layouting Manual \n");
	printf ("3. Tampilkan Routing \n");
	printf ("4. Routing Manual \n");
	printf ("5. Layout Otomatis \n");
	printf ("6. Routing Otomatis \n");
	printf ("7. Design Rule Checker \n");
	printf ("8. Simpan Proyek dan Keluar\n");
	printf ("masukkan nomor menu : ");
	scanf ("%d", &menu);
	printf ("\n\n");
	return;
}

void cobaRouting ()
{	
	printf ("Isi `q` atau `Q` untuk kembali ke menu\n");
	printf ("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");

		do
		{
			printf ("Pilih Simbol (!,@,#,$,%,^,&,*,(,)):");
			scanf (" %c", &sym);
		}
		while (!(sym=='!'||sym=='@'||sym=='#'||sym=='$'||sym=='%'||sym=='^'||sym=='&'||sym=='*'||sym==','||sym=='q'||sym=='Q'));//validasi simbol
		if (sym=='q'||sym=='Q')
		{
			printf ("\n\n");
			menuUtama();
			pilihanMenu();
		}else if (sym=='!'||sym=='@'||sym=='#'||sym=='$'||sym=='%'||sym=='^'||sym=='&'||sym=='*'||sym==',');
		{
			simpanSymbol(n,m,pcb);		
		}
		
}

void simpanSymbol (int n, int m, jalur pcb[40][40])
{
	koordinat koordinatKe[100];
	int jumlahKoor,i,kolom,baris;
	char koorX,koorY; //menyimpan koordinat sementara
	jumlahKoor =1;
	do
	{
		//asumsi routing dimulai dari titik2 yang ada kaki komponennya
		printf ("Koordinat %d : ",jumlahKoor);
		scanf (" %c%*c%c", &koorX,&koorY);
	}while (!(atoi(koorX)>0 || atoi(koorX)<n || atoi(koorY)>0 ||atoi(koorY)<m));
	{
		while(koorX!='n'||koorX!='N'||koorY!='n'||koorY!='N'||koorX!='q'||koorX!='Q'||koorY!='q'||koorY!='Q')
		{
			jumlahKoor++;
			printf ("Koordinat %d : ",jumlahKoor);
			scanf ("%c%*c%c", &koorX,&koorY);
		}
		{
			if (koorX=='n'||koorX=='N'||koorY=='n'||koorY=='N')
			{
			jumlahKoor =1;
			cobaRouting();
			}else if (koorX=='q'||koorX=='Q'||koorY=='q'||koorY=='Q')
			{
			printf ("\n\n");
			menuUtama();
			pilihanMenu();
			}
		}
	}

}

void tampilkanRouting(int n, int m, jalur pcb[40][40]){
	int i,j;
	
	for (i=0; i<n; i+=1){
		printf("	%d", i+1);
	}
	printf("\n");
	
	for (j=0; j<m; j+=1) {
		printf("%d	", j+1);
		for(i=0; i<n ; i+=1){
			printf("%c	", pcb[i][j].simbol);
		}
		printf("\n");
	}
	
}

void make_layout(int n, int m,jalur pcb[40][40], int *x) {
	komponen masuk;
	int inp_x1, inp_y1, inp_x2, inp_y2,i,j;
	double jarak;
	
	*x=0;
		
	printf("[Mode Layout]\n");
	printf("Isi 'q' atau 'Q' untuk kembali ke menu\n"); /*WARNING!!! MASUKKAN JUGA ANGKA SETELAH Q ATAU q */

	printf("Pilih Komponen (R,C,T,J): "); 
	scanf(" %c%c", &masuk.nama, &masuk.nomor);/*asumsi tidak ada nama komponen yang diulang*/
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
					validasi=1;
				}
				else if (masuk.nama == 'C' && (jarak>=2)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
					validasi=1;
				}
				else if (masuk.nama == 'T' && (jarak>=2)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
					validasi=1;
				}
				else if (masuk.nama == 'J' && (jarak>=1)) {
					/*input ke array*/
					pcb[inp_x1-1][inp_y1-1].listrik.nama=masuk.nama;
					pcb[inp_x1-1][inp_y1-1].listrik.nomor=masuk.nomor;
					pcb[inp_x2-1][inp_y2-1].listrik.nama=masuk.nama;
					pcb[inp_x2-1][inp_y2-1].listrik.nomor=masuk.nomor;
					*x+=1;
					printf("\nPilih Komponen (R,C,T,J): "); scanf(" %c%c", &masuk.nama, &masuk.nomor);
					validasi=1;
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
	
	int i,j;
	
	for (i=0; i<10; i+=1){
		printf("	%d", i+1);
	}
	printf("\n");
	
	for (j=0; j<12; j+=1) {
		printf("%d	", j+1);
		for(i=0; i<10 ; i+=1){
			printf("%c%c	", pcb[i][j].listrik.nama, pcb[i][j].listrik.nomor);
		}
		printf("\n");
	}
	
}

void auto_routing(jalur pcb[40][40]) {
	int i,j;
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
	
	for (i=0; i<10; i+=1){
		printf("	%d", i+1);
	}
	printf("\n");
	
	for (j=0; j<12; j+=1) {
		printf("%d	", j+1);
		for(i=0; i<10 ; i+=1){
			printf("%c	", pcb[i][j].simbol);
		}
		printf("\n");
	}
}
