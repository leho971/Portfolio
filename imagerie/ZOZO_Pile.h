#pragma once
#include "ZOZO_image.h"

typedef struct coord {
	int x;
	int y;
};

typedef struct pile {
	coord c[10000000];
	int h;
};

void initP(pile a) {
	a.h = -1;
}

bool vide(pile a) {
	return a.h == -1;
}

void ajoute(pile a, int b, int c) {
	a.h++;
	a.c->x = b;
	a.c->y = c;
}

void supprimer(pile a) {
	a.h--;
}

coord affiche(pile a) {
	return a.c[a.h];
}

/*************************************************************************************/
#define max2 10000

void cree_f(int f[max2][2]) {
	f[0][0] = 0;
	f[0][1] = 0;
}

bool vide_f(int f[max2][2]) {
	return f[0][0] == f[0][1];
}

void ajouter_f(int f[max2][2], int x, int y) {
	if (f[0][1] == max2 - 1)
	{
		f[0][1] = 1;
	}
	else
	{
		f[0][1]++;;
	}
	f[f[0][1]][0] = x;
	f[f[0][1]][1] = y;
}

void supp(int f[max2][2]) {
	if (f[0][0] == max2 - 1)
	{
		f[0][0] = 1;
	}
	else
	{
		f[0][0]++;;
	}
}

int* afffile_f(int  f[max2][2]) {
	return f[f[0][0]];
}