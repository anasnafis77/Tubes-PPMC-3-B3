//4. Routing Manual
#include <stdio.h>
#include <stdlib.h>
#include "variable.h"

typedef struct 
{
	int x,y;
} koordinat;

void routingManual (int n, int m, jalur pcb[40][40])
{
	koordinat koordinatKe[100];
	int jumlahKoor,i,kolom,baris;
	char a,b; //menyimpan koordinat sementara
	char sym;//menyimpan simbol sementara
	printf ("Isi `q` atau `Q` untuk kembali ke menu\n");
	printf ("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
	do
	{
		do
		{
			printf ("Pilih Simbol (!,@,#,$,%,^,&,*,(,)):");
			scanf (" %c", &sym);
		}
		while (!(sym=='!'||sym=='@'||sym=='#'||sym=='$'||sym=='%'||sym=='^'||sym=='&'||sym=='*'||sym==','));//validasi simbol
		jumlahKoor=1;
		do
		{
			printf ("Koordinat %d : ",jumlahKoor);
			do
			{
				scanf (" %c%*c%c", &a,&b);
			}
			while ((atoi(&a)>n && atoi(&a)<0 && atoi(&b)>m && atoi(&b)<0) || (pcb[atoi(&a)][atoi(&b)].listrik.nama==' '));//validasi matriks
			koordinatKe[jumlahKoor].x=atoi(&a);
			koordinatKe[jumlahKoor].y=atoi(&b);
			jumlahKoor++;
		}
		while (!(a=='n'||a=='N'||b=='n'||b=='N'));//validasi node
		if ((a=='n'||a=='N'||b=='n'||b=='N'))
		{
			for (i=1;i<jumlahKoor;i++)
			{
				if (koordinatKe[i].x==koordinatKe[i+1].x)
				{
					for (kolom=koordinatKe[i].y;kolom<koordinatKe[i+1].y;kolom++)
					{
						pcb[koordinatKe[i].x][kolom].simbol=sym;
					}
				}
				else if (koordinatKe[i].y==koordinatKe[i+1].y)
				{
					for (baris=koordinatKe[i].x;baris<koordinatKe[i+1].x;baris++)
					{
						pcb[koordinatKe[i].y][baris].simbol=sym;
					}
				}
			}
		}
	}
	while(!(a=='q'||a=='Q'));
}
