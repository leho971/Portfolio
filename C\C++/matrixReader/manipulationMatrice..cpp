#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int LIG_MAX = 10;
const int COL_MAX = 15;

typedef int matrice[LIG_MAX][COL_MAX];
matrice t_matrice;

void initialiserMatrice(matrice &m) {
	for (int i = 0; i < LIG_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			m[i][j] = 0;
		}
	}
}

void afficherMatrice(matrice &m) {
	cout << "\n";
	for (int i = 0; i < LIG_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			cout << " " << m[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void lireCoordonnees(matrice m, int &x,  int &y) {
	
	cout << "Saisir la ligne : ";
	cin >> x;
	cout << "Saisir la cologne : ";
	cin >> y;

	cout << "La valeur au coordonnee (" << x << "," << y << ") est " << m[x][y] << "\n";
}

void lireVal(matrice &m, int x, int y) {
	int val;
	cout << "Saisir la valeur a entree : ";
	cin >> val;
	m[x - 1][y - 1] = val;
	cout << "La valeur " << val << " a ete ajouter au coordonnee (" << x << "," << y << ")";
}

void lireLigne(matrice &m) {
	int x, y;
	cout << "Saisir la ligne a lire : ";
	cin >> x;
	cout << "Saisir la cologne : ";
	cin >> y;

	for (int i = y - 1; i < COL_MAX; i++)
	{
		cout << "donner la valeur au coordonnee (" << x << "," << i+1 << ") : ";
		cin >> m[x - 1][i];
	}

	cout << "\n Voici les valeur ajouter en ligne dans la matrice : \n";
	for (int i = y - 1; i < COL_MAX; i++)
	{
		cout << " " << m[x - 1][i] << " ";
	}
	cout << "\n";
}

void lireColonne(matrice& m) {
	int x, y;
	cout << "Saisir la ligne a lire : ";
	cin >> x;
	cout << "Saisir la cologne : ";
	cin >> y;

	for (int i = x - 1; i < LIG_MAX; i++)
	{
		cout << "donner la valeur au coordonnee (" << i + 1 << "," << y << ") : ";
		cin >> m[i][y - 1];
	}

	cout << "\n Voici les valeur ajouter en colonne dans la matrice : \n";
	for (int i = x - 1; i < LIG_MAX; i++)
	{
		cout << " " << m[i][y - 1] << " ";
	}
	cout << "\n";
}

void initialiserAleatoirement(matrice &m) {
	srand(time(NULL));

	for (int i = 0; i < LIG_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			m[i][j] = rand() % (RAND_MAX + 1);
		}
	}
}

void effacerDirection(matrice &m) {
	int choix = 1;
	int x, y;
	cout << "Saisir la ligne a lire : ";
	cin >> x;
	cout << "Saisir la cologne : ";
	cin >> y;

	cout << "La valeur au coordonnee (" << x << "," << y << ") est " << m[x][y] << "\n";
	cout << "Saisir la direction d'effacement :\n"
		<< "(1) haut \n"
		<< "(2) bas\n"
		<< "(3) gauche\n"
		<< "(4) droite\n"
		<< "(0) annuler\n";
	cin >> choix;
	
	switch (choix)
	{
	case 1:
		for (int i = (x - 1) ; i >= 0; i--)
		{
			m[i][y] = 0;
		}
		break;
	case 2:
		for (int i = (x + 1); i < LIG_MAX; i++)
		{
			m[i][y] = 0;
		}
		break;
	case 3:
		for (int i = (y - 1); i >= 0; i--)
		{
			m[x][i] = 0;
		}
		break;
	case 4:
		for (int i = (y + 1); i < COL_MAX; i++)
		{
			m[x][i] = 0;
		}
		break;
	default:
		cout << "F";
		break;
	}
}

void effacerDirectionEnSerie(matrice& m) {
	int choix = 1;
	int x, y, i;
	bool drap;
	cout << "Saisir la ligne a lire : ";
	cin >> x;
	cout << "Saisir la cologne : ";
	cin >> y;

	while (choix > 0 && choix < 5)
	{
		cout << "La valeur au coordonnee (" << x << "," << y << ") est " << m[x-1][y-1] << "\n";
		cout << "Saisir la direction d'effacement :\n"
			<< "(1) haut \n"
			<< "(2) bas\n"
			<< "(3) gauche\n"
			<< "(4) droite\n"
			<< "(0) annuler\n";
		cin >> choix;

		switch (choix)
		{
		case 1:
			i = (x - 2);
			drap = true; 
			while (i >= 0 && drap)
			{
				if (m[i][y-1] != 0)
				{
					m[i][y-1] = 0;
				}
				else
				{
					drap = false;
					i++;
				}
				i--;
			}
			x = i + 2;
			break;
		case 2:
			i = x;
			drap = true;
			while (i < LIG_MAX && drap)
			{
				if (m[i][y-1] != 0)
				{
					m[i][y-1] = 0;
				}
				else
				{
					drap = false;
					i--;
				}
				i++;
			}
			x = i;
			break;
		case 3:
			i = (y - 2);
			drap = true;
			while (i >= 0 && drap)
			{
				if (m[x-1][i] != 0)
				{
					m[x-1][i] = 0;
				}
				else
				{
					drap = false;
					i++;
				}
				i--;
			}
			y = i + 2;
			break;
		case 4:
			i = y;
			drap = true;
			while (i < COL_MAX && drap)
			{
				if (m[x-1][i] != 0)
				{
					m[x-1][i] = 0;
				}
				else
				{
					drap = false;
					i--;
				}
				i++;
			}
			y = i;
			break;
		default:
			cout << "F";
			break;
		}
		afficherMatrice(m);
	}
}

int main() {
	setlocale(LC_ALL, "");
	system("mode 120,50");
	int choix = 1;
	int x, y = 0;

	while (choix < 8 && choix > 0)
	{
		cout << "Que voulez vous faire ?\n"
			<< "(1) initialisation de la matrice, \n"
			<< "(2) affichage de la matrice,\n"
			<< "(3) lire une valeur,\n"
			<< "(4) lire les valeurs d'une ligne à partir d'une case de départ,\n"
			<< "(5) lire les valeurs d'une colonne à partir d'une case de départ,\n"
			<< "(6) remplir la matrice avec des valeurs aléatoires,\n"
			<< "(7) effacer les valeurs à partir d'une case de départ et d'une direction,\n"
			<< "(8) effacer les valeurs à partir d'une case de départ et d'une direction en serie,\n"
			<< "(9) quitter,\n"
			<< " Saisisser un chiffre : ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			initialiserMatrice(t_matrice);
			afficherMatrice(t_matrice);
			break;
		case 2:
			afficherMatrice(t_matrice);
			break;
		case 3:
			lireCoordonnees(t_matrice, x, y);
			lireVal(t_matrice, x, y);
			afficherMatrice(t_matrice);
			break;
		case 4:
			lireLigne(t_matrice);
			afficherMatrice(t_matrice);
			break;
		case 5:
			lireColonne(t_matrice);
			afficherMatrice(t_matrice);
			break;
		case 6:
			initialiserAleatoirement(t_matrice);
			afficherMatrice(t_matrice);
			break;
		case 7:
			effacerDirection(t_matrice);
			afficherMatrice(t_matrice);
			break;
		case 8:
			effacerDirectionEnSerie(t_matrice);
		case 9:
			cout << " Bye Bye ";
			break;
		default:
			cout << "Pas de choix disponible";
			break;
		}
	}
}