#pragma once
#include "ZOZO_Tp4.cpp"

typedef struct Sommets{
	int Nom;
	int Val;
	Sommets* FG;
	Sommets* FD;
}Sommets;

typedef struct pile{
	Sommets* suiv;
}pile;


void Creer(pile *A) {
	A->suiv = (Sommets*)malloc(sizeof(Sommets));
}

void Ajouter(Sommets* X, pile *A) {
	X->FG = A->suiv;
	A->suiv = X;
}

void Supprimer(pile* A) {
	if (A->suiv != NULL) {
		A->suiv = A->suiv->FG;
	}
}

bool Vide(pile* A) {
	return (A->suiv == NULL);
}

int Valeur(pile* A) {
	return A->suiv->Val;
}

