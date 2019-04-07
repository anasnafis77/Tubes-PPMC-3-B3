#ifndef LIB_H
#define LIB_H
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

jalur pcb[40][40]; //matriks PCB 

char fileName[20];
int n, m;

//deklarasi fungsi
void routingManual (jalur pcb[40][40]);
void make_layout(int n, int m,jalur pcb[40][40]);

#endif
