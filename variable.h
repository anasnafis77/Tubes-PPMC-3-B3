#include <stdio.h>


typedef struct {//nama komponen yang terdiri atas huruf simbol komponen dan nomor komponen
	char nama;
	int nomor;
}komponen;

typedef struct {//tipe data untuk menyatakan komponen dan simbol jalur pada PCB
	komponen listrik;
	char simbol;
}jalur;

jalur pcb [40][40]; //matriks PCB 


