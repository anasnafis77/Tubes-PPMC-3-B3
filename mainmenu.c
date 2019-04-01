#include <stdio.h>
#include "variable.h"

int pilihan, menu;

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

int main ()
{
	do 
	{
	halamanAwal();
	}
	while (pilihan < 1 || pilihan > 3);
	if (pilihan == 1)
		{
			do
			{
			menuUtama ();
			} while (menu<1 || menu > 8);
			switch (menu)
			{
				case 1 :;
					break;
				case 2 :;
					break;
				case 3 :;
					break;
				case 4 :;
					break;
				case 5 :;
					break;
				case 6 :;
					break;
				case 7 :;
					break;
				case 8 :;
					break;
			}					
		} else if (pilihan == 2)
		{
			
		} else if (pilihan == 3)
		{
			return 0;
		}
	 
	return (0);
}
