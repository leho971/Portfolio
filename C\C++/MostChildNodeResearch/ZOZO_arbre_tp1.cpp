/****************************************************************************************************************/
/*                                               TP de Théorie des Arbre                                        */
/*                                                                                                              */
/*Ce programme a pour but: recherche le sommet avec le plus de fils et de le retourne avec le nombre de fils    */
/*                                                                                                              */
/* Le résultat sera de savoir combien de fils a la racine                                                       */
/*																												*/
/*La methode utilisée : Compte pour chaque Sommets le nombre de fils et stock le sommet et le nombre de fils	*/
/*de ce sommets puis l'affiche																					*/
/*																												*/
/*Resultat Obtenu : Le programme répond au cahier des charges. Il permet à l'utilisateur de remplir		        */
/*l'arborescence puis l'affiche. Ensuite affiche le sommet avec le plus de fils								    */
/*                                                                                                              */
/*                                                                                                              */
/* Date de création: 15/09/2023																					*/
/*                                                                                                              */
/* Date de dernière Modification: 04/12/2023                                                                    */
/*																												*/
/* Outil de developpement : Microsoft Visual Studio 2019, Windows                                               */
/*																												*/
/* Auteur: ZOZO léo                                                                                             */
/****************************************************************************************************************/



#include<stdio.h>
const int longueur = 10;
const int largeur = 10;
int max = 0;
int nbreDeS = 0;
int S;



void RechercheDeSommetMax(int a[longueur][largeur]) {
	int maxT;
	int j;
	int l;
	int taille = 0;
	while (a[taille][0]) {
		taille++;
	}
	for (int i = 0; i < taille; i++) {/*boucle pour tester tout les sommets*/
		j = 0;
		l = j;
		maxT = a[i][j];
		do { /* boucle pour savoir combien de fils a notre sommets actuel*/
			if (a[i][l + 1]) {
				l++;
			}
		} while (a[i][l + 1] != NULL);/*boucle pour savoir si le sommet actuel a au moins un fils suivant*/
		if (nbreDeS < l) {
			nbreDeS = l;
			max = maxT;
		}
	}
}/*RechercheDeSommetMax*/



void RemplirArborescence(int a[longueur][largeur]) {
	bool fils;
	int F;
	int rep;
	printf("Combien de sommets a votre arborescence ?\n");
		scanf_s("%d", &S);
		while (S > 10 or S < 0) {
			printf(" Entre 0 et 10\n");
			scanf_s("%d", &S);
		}
		for (int i = 0; i < S; i++) {
			printf("quel est le sommet n°%d\n", (i + 1));
			scanf_s("%d", &a[i][0]);
			fils = true;
			F = 1;
			while (fils) {
				printf("Il y a t'il un fils %d ?(oui = 1, non = 0)", F);
				scanf_s("%d", &rep);
				if (rep == 1) {
					printf("quel est se sommet ?\n");
					scanf_s("%d", &a[i][F]);
					F++;
				}
				else {
					fils = false;
				}
			}
		}
}/*RemplirArborescence*/



void RemplirArborescence2(int a[longueur][largeur]) {
	int r;
	int tmp = 1;
	int i = 0;
	int s = 0;
	int j = 0;
	
	printf("quel est la racine ");
	scanf_s("%d", &r);
	
	a[s][i] = r;
	while (a[s][0] != NULL) {
		while (tmp != 0) {
			printf("quel est le fils de %d (0 si aucun) ?  ", a[s][0]);
			scanf_s("%d", &tmp);
			if (tmp != 0) {
				i++;
				a[s][i] = tmp;
				
				j++;
				a[j][0] = tmp;
			}
		}
		i = 0;
		s++;
		tmp = 1;
	}
	
}/*RemplirArborescence2*/



void AfficherArborescence(int a[longueur][largeur]) {
	int k = 0;
	int i = 0;
	int j = 0;
	while (a[i][j] != 0 || a[i][j] != NULL) {
		while (a[i][j] != 0 || a[i][j] != NULL) {
			if (k != i) {
				printf("\n");
				k++;
			}
			printf(" %d ", a[i][j]);
			if (j == 0) { printf("\n"); }
			if (a[i][j + 1] == 0 || a[i][j + 1] == NULL) { printf("\n"); }
			j++;
		}
		j = 0;
		i++;
	}
}/*AfficherArborescence*/



void AfficherArborescence2(int a[longueur][largeur]) {
	int t = 0;
	int t2;
	
	for (int i = 0; i < largeur; i++) {
		for (int j = 0; j < longueur; j++) {
			if (i > 0 && j == 0) { printf("\n"); }
			printf(" %d ", a[i][j]);
		}
	}
}/*AfficherArborescence2*/


void AfficherArborescence3(int a[longueur][largeur]) {
	int t = 0;
	int t2;

	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {
			printf(" %d ", a[j][i]);
			if (j == S - 1) { printf("\n"); }
		}
	}
}/*AfficherArborescence3*/



int main() {
	int arbre2[longueur][largeur] = {0};
	S = 9;
	int arbre[longueur][largeur] = {
		{1,2,3,0,0,0,0,0,0},
		{2,5,0,0,0,0,0,0,0},
		{3,7,4,0,0,0,0,0,0},
		{4,8,0,0,0,0,0,0,0},
		{5,6,9,0,0,0,0,0,0},
		{6,0,0,0,0,0,0,0,0},
		{7,0,0,0,0,0,0,0,0},
		{8,0,0,0,0,0,0,0,0},
		{9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	};
	RemplirArborescence2(arbre2);
	AfficherArborescence3(arbre2);
	RechercheDeSommetMax(arbre2);
	printf("\n");
	printf("banana \n");
	printf("le 1er sommet avec le plus de fils est S%d avec %d fils", max, nbreDeS);
	return 0;
}
