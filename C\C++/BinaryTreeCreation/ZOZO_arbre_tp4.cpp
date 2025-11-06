/****************************************************************************************************************/
/*                                               TP de Théorie des Arbre                                        */
/* Ce programme a pour but de permettre de remplir un Arbre binaire par l'utilisateur                           */
/* Le résultat sera d'afficher l'arbre rentré par l'utilisateur                                                 */
/*                                                                                                              */
/*                                       																		*/
/*                                                                                                              */
/*                                                                                                              */
/* Date de création:                                                                                            */
/* Date de dernière Modification :                                                                              */
/*                                                                                                              */
/*                                                                                                              */
/* Résultats obtenus: Rien                                                                                      */
/*                                                                                                              */
/*                                                                                                              */
/* Outil de developpement : Microsoft Visual Studio 2019                                                        */
/* Auteur: ZOZO Léo                                                                                             */
/****************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "ZOZO_Tp4_pile.h"

pile* b;

void Remplir(Sommets arbre) {
	int val;
	int nom;

	printf("donnez le nom de la racine : ");
	scanf_s("%d", &nom);
	arbre.Nom = nom;

	printf("donnez la valeur de la racine : ");
	scanf_s("%d", &val);
	arbre.Val = val;

	printf("donnez le nom d'un fils de S%d (0 si aucun): ",nom);
	scanf_s("%d", &nom);
	if (nom != 0) {
		printf("donnez la valeur du fils de S%d : ", nom);
		scanf_s("%d", &val);
	}

	
}

void Afficher() {

}

int main() {
	Creer(b);
	free(b);
}

