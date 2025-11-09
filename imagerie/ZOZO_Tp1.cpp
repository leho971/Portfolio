#include "ZOZO_image.h"
#include <locale.h>




//------------------------------------------------------------------------------
// Code source pour le projet d'UE035
// description : (les fonctions sont définit dans image.h)
//
// les pointeurs images dans ce code sont de type : struct fichierimage *
//
// fonction struct fichierimage * charger(char *)
// permet de charger une image presente sur le disque en memoire vive, la fonction
// renvoie un pointeur de type : struct fichierimage *
//
// fonction int enregistrer(struct fichierimage *,char *)
// permet d'enregistrer une image sur le disque sous le nom donné en arg2, cette
// image est contenue dans une pointeur de type : struct fichierimage * fournit en arg1
//
// fonction struct fichierimage * nouveau(int,int)
// permet de creer une image en memoire de largeur arg1 et de hauteur arg2, la fonction
// retourne un pointeur de type : struct fichierimage *
//------------------------------------------------------------------------------

char nom_img[20] = "Test.bmp" ;
char nom_img2[20] = "Cathy.bmp";
char nom_res[20] = "Resultat.bmp";
int choix;
int stock;
int stock2;
float Stock;
bool condition;
bool runWhile = true;
struct fichierimage** TableImage = NULL;
int** etiquettes;


void Debut_du_programme() {
    liste();
    while (runWhile){
        printf("Choisisser ce que vous vouler faire: ");
        scanf("%d", &choix);
        choix = (int)choix;

        if (choix < -50 || choix > 50){
            choix = 0;
        }

        printf("vous avez choisi : %d\n", choix);
        //system("pause");

        switch (choix) {
        case 1:
            TableImage[1] = binarisation(TableImage[1]);
            break;
        case 2:
            TableImage[1] = NivDeGris(TableImage[1]);
            break;
        case 3:
            TableImage[1] = Renvers(TableImage[1]);
            break;
        case 4:
            TableImage[1] = MiroirX(TableImage[1]);
            break;
        case 5:
            TableImage[1] = MiroirY(TableImage[1]);
            break;
        case 6:
            TableImage[1] = SymetrieY(TableImage[1]);
            break;
        case 7:
            TableImage[1] = InversSymetrieY(TableImage[1]);
            break;
        case 8:
            TableImage[1] = SymetrieX(TableImage[1]);
            break;
        case 9:
            TableImage[1] = InversSymetrieX(TableImage[1]);
            break;
        case 10:
            TableImage[1] = SymetrieXY1(TableImage[1]);
            break;
        case 11:
            TableImage[1] = SymetrieXY2(TableImage[1]);
            break;
        case 12:
            TableImage[1] = SymetrieXY3(TableImage[1]);
            break;
        case 13:
            TableImage[1] = SymetrieXY4(TableImage[1]);
            break;
        case 14:
            TableImage[1] = SymetrieDiag(TableImage[1]);
            break;
        case 15:
            TableImage[1] = InversSymetrieDiag(TableImage[1]);
            break;
        case 16:
            TableImage[1] = SymetrieDiag2(TableImage[1]);
            break;
        case 17:
            TableImage[1] = InversSymetrieDiag2(TableImage[1]);
            break;
        case 18:
            TableImage[1] = PivotG(TableImage[1]);
            break;
        case 19:
            TableImage[1] = PivotD(TableImage[1]);
            break;
        case 20:
            TableImage[1] = Negative(TableImage[1]);
            break;
        case 21:
            TableImage[1] = MonochromeRed(TableImage[1]);
            break;
        case 22:
            TableImage[1] = MonochromeBlue(TableImage[1]);
            break;
        case 23:
            TableImage[1] = MonochromeGreen(TableImage[1]);
            break;
        case 24:
            TableImage[1] = MonochromeMagenta(TableImage[1]);
            break;
        case 25:
            TableImage[1] = MonochromeCyan(TableImage[1]);
            break;
        case 26:
            TableImage[1] = MonochromeYellow(TableImage[1]);
            break;
        case 27:
            printf("Donner l'echelle pour l'agrandissement :");
            scanf("%d", &stock);
            TableImage[1] = Agrandissement(TableImage[1], stock);
            break;
        case 28:
            printf("Donner l'echelle pour la reduction :");
            scanf("%d", &stock);
            TableImage[1] = Reduction(TableImage[1], stock);
            break;
        case 29:
            printf("Egalisation en niveau de gris(Taper 1) ou en couleur(Taper 0) ?\n");
            scanf("%d", &stock);
            if (stock == 1){
                TableImage[1] = EgalisationGray(TableImage[1]);
            }
            else{
                TableImage[1] = EgalisationColor(TableImage[1]);
            }
            break;
        case 30:
            TableImage[1] = FiltreMedian(TableImage[1]);
            break;
        case 31:
            printf("Convolution flou(Taper 1) ou bord(Taper 0) ?\n");
            scanf("%d", &stock);
            if (stock == 1) {
                TableImage[1] = FiltreMoyenneur(TableImage[1]);
            }
            else {
                TableImage[1] = Convolution(TableImage[1]);
            }
            break;
        case 32:
            listeImage();
            printf("Donner l'image a incruster (exemple.bmp): ");
            scanf("%s", &nom_img);
            VerifNomImage(nom_img);
            TableImage[1] = charger(nom_img);
            printf("Donner le fond pour l'image a incruster (exemple.bmp): ");
            scanf("%s", &nom_img2);
            VerifNomImage(nom_img2);
            TableImage[2] = charger(nom_img2);
            TableImage[1] = FondBleu(TableImage[1], TableImage[2]);
            break;
        case 33:
            listeImage();
            printf("Donner l'image a incruster (exemple.bmp): ");
            scanf("%s", &nom_img);
            VerifNomImage(nom_img);
            TableImage[1] = charger(nom_img);
            printf("Donner le fond pour l'image a incruster (exemple.bmp): ");
            scanf("%s", &nom_img2);
            VerifNomImage(nom_img2);
            TableImage[2] = charger(nom_img2);
            TableImage[1] = FondVert(TableImage[1], TableImage[2]);
            break;
        case 34:
            printf("Donner un valeur pour modifier l'image : ");
            scanf("%d", &stock);
            TableImage[1] = Luminosité(TableImage[1], stock);
            break;
        case 35:
            printf("Donner un angle de rotation : ");
            scanf("%d", &stock);
            TableImage[1] = Rotation(TableImage[1], stock);
            break;
        case 36:
            TableImage[1] = FiltreLaplacien(TableImage[1]);
            break;
        case 37:
            TableImage[1] = NivDeGris(TableImage[1]);
            TableImage[1] = binarisation(TableImage[1]);
            if (TableImage[1]->image[0][0].b == 255)
            {
                TableImage[1] = Negative(TableImage[1]);
            }
            etiquettes = (int**)malloc(TableImage[1]->entetebmp.hauteur * sizeof(int*));
            for (int i = 0; i < TableImage[1]->entetebmp.hauteur; i++)
            {
                etiquettes[i] = (int*)malloc(TableImage[1]->entetebmp.largeur * sizeof(int));

            }
            
            Etiquettage(TableImage[1], etiquettes, stock);
            
            printf("il y a %d forme dans l'image\n", stock);
            printf("voulez vouz verifier la compacité d'une forme (oui = 1, non = 0) : ");
            scanf("%d", &stock2);
            while (stock2) {
                printf("il y a %d forme, laquelle choisissez vous : ", stock);
                scanf("%d", &stock2);
                Compacite(etiquettes, stock, stock2, TableImage[1]->entetebmp.hauteur, TableImage[1]->entetebmp.largeur);
            }
            break;
        case 38:
            /*printf("Donner un coefficient pour le seuil bas : ");
            scanf("%f", &Stock);*/
            TableImage[1] = NivDeGris(TableImage[1]);
            TableImage[1] = Hysteresis(TableImage[1], 0.4);
            TableImage[1] = FiltrePrewitt(TableImage[1]);
            break;
        case -1:
            liste();
            break;
        case -2:
            listeImage();
            printf("Donner le nom du ficher (exemple.bmp): ");
            scanf("%s", &nom_img);
            VerifNomImage(nom_img);
            TableImage[1] = charger(nom_img);
            TableImage[0] = TableImage[1];
            break;
        case -3:
            enregistrer("Resultat.bmp", TableImage[1]);
            system("Resultat.bmp");
            break;
        case -4:
            listeImage();
            printf("Ajout d'une image supplementaire (exemple.bmp): ");
            printf("Fonction pas prête");

            break;
        case -5:
            printf("Sous quel nom vouler vous l'enregistrer ? (exemple.bmp): ");
            scanf("%s", nom_res);
            VerifNomImage(nom_res);
            enregistrer(nom_res, TableImage[1]);
            break;
        case -6:
            TableImage[1] = TableImage[0];
            break;
        case -7:
            listeImage();
            break;
        default:
            runWhile = false;
            break;
        }
        printf("Fonction %d effectuée.\n", choix);
    }
}


int main()
{
    int i = 0;
    int j = 0;
    setlocale(LC_ALL, "");

    
    TableImage = (struct fichierimage**)malloc(3 * sizeof(struct fichierimage*));
    if (TableImage == NULL) {
        printf("Faux");
        exit(0);
    }

    TableImage[1] = charger(nom_img);
    TableImage[2] = charger(nom_img2);
    TableImage[0] = TableImage[1];

    Debut_du_programme();

    i = 0;
    while (etiquettes[i] != NULL) {
        free(etiquettes[i]);
        i++;
    }
    free(etiquettes);
    for (i = 0; i < 3; i++) {
        free(TableImage[i]);
        i++;
    }
    free(TableImage);
}

