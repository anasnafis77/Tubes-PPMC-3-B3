//4. Routing Manual
#include <stdio.h>
#include "variable.h"

typedef struct 
{
	int x,y;
} koordinat;

int main ()
{
	koordinat koordinatKe[100];
	int jumlahKoor,i,kolom;
	int a,b; //menyimpan koordinat sementara
	char sym;//menyimpan simbol sementara
	printf ("Isi `q` atau `Q` untuk kembali ke menu\n");
	printf ("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
	do
	{
		do
		{
			printf ("Pilih Simbol (!,@,#,$,%,^,&,*,(,)):");
			scanf ("%c", &sym);
		}
		while (sym!='!'||sym!='@'||sym!='#'||sym!='$'||sym!='%'||sym!='^'||sym!='&'||sym!='*'||sym!=',');//validasi simbol
	
		jumlahKoor=1;
		do
		{
			printf ("Koordinat %d",jumlahKoor);
			do
			{
				scanf ("%d%*c%d", &a,&b);
			}
			while ((a>40 && a<0 && b>40 && b<0) || (pcb[a][b].listrik.nama=' '));//validasi matriks
			koordinatKe[jumlahKoor].x=a;
			koordinatKe[jumlahKoor].y=b;
			jumlahKoor++;
		}
		while ((a!='n'||a!='N'||b!='n'||b!='N'));//validasi node
		if (a!='n'||a!='N'||b!='n'||b!='N')
		{
			for (i=1;i<=jumlahKoor;i++)
			{
				for (kolom=koordinatKe[i].y;kolom<koordinatKe[i+1].y;kolom++)
				{
					pcb[koordinatKe[i].x][kolom].simbol=sym;
				}
			}
		}
	}
	while((a!='q'||a!='Q'));
	return 0;
}
