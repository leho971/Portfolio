#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include "ZOZO_Pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


float FlMasque3x3[3][3];
pixels PixMasque3x3[3][3];

float fact[3] = { 0 };
float ffact[9] = { 0 };
pixels masque[9] = { 0 };

int index[9] = { 0 };


float Gradient[3][3] = { {-1,-1,-1},
                        { -1,8,-1 },
                        { -1,-1,-1 } };

float PrewittX[3][3] = { {-1,0,1},
                        {-1,0,1},
                        {-1,0,1} };

float PrewittY[3][3] = { {-1,-1,-1},
                            {0,0,0},
                            {1,1,1} };

float KernelLap9[3] = { -4,1,0 };
float KernelLap6[3] = { -3,1,0 };
float KernelLap4[3] = { -2,1,0 };

float HistogrammBlue[255] = { 0 };
float HistogrammGreen[255] = { 0 };
float HistogrammRed[255] = { 0 };

float Histogramm_Normaliser[255] = { 0 };
float C_de_I[255] = { 0 };

// structure d'entete du fichier
struct entete_fichier
{
    char idformat[2];
    int taille_fichier;
    int reserve;
    int debut;
};

// structure d'entete de l'image
struct entete_bmp
{
    int taille_image;
    int largeur;
    int alignement;
    int hauteur;
    short plans;
    short profondeur;
    int compression;
    int taille_image_totale;
    int resolutionh;
    int resolutionv;
    int nbrcouleur;
    int nbrcouleuri;
};

// structure d'un pixel en RGB
struct pixels
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

// structure d'un pixel en TSL
struct hsb {
    float h;
    float s;
    float b;
};

// A supprimer
// masque appliquer sur les image
typedef struct Matrice3x3{
    struct pixels Window[9];
    int mult[9];
}Matrice3x3;

//A supprimer
Matrice3x3 Mat;

// structure du fichier (RGB)
struct fichierimage
{
    struct entete_fichier entetefichier;
    struct entete_bmp entetebmp;
    struct pixels image[5000][5000];
};

// structure du fichier (HSB)
struct fichierimage_tsl
{
    struct entete_fichier entetefichier;
    struct entete_bmp entetebmp;
    struct hsb image[5000][5000];
};

// -2 //charger une image dans une variable
struct fichierimage* charger(const char* nom)
{
    FILE* f;
    int i, j, k;
    unsigned char zero;
    unsigned char* buffer;
    int position = 0;
    int longueur = 0;
    struct fichierimage* fichier = (struct fichierimage*)malloc(sizeof(struct fichierimage));

    f = fopen(nom, "rb");
    fseek(f, 0, SEEK_END);
    longueur = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (unsigned char*)malloc(longueur * sizeof(unsigned char));
    fread((unsigned char*)buffer, 1, longueur, f);
    fclose(f);

    // lecture de l'entete du fichier

    memcpy(&fichier->entetefichier.idformat, (buffer + position), 2);
    position += 2;
    memcpy(&fichier->entetefichier.taille_fichier, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetefichier.reserve, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetefichier.debut, (buffer + position), 4);
    position += 4;

    /*
    printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
    printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
    printf("reserve                  :%d\n",fichier->entetefichier.reserve);
    printf("debut                    :%d\n",fichier->entetefichier.debut);
    */

    // lecture de l'entete de l'image

    memcpy(&fichier->entetebmp.taille_image, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.largeur, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.hauteur, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.plans, (buffer + position), 2);
    position += 2;
    memcpy(&fichier->entetebmp.profondeur, (buffer + position), 2);
    position += 2;
    memcpy(&fichier->entetebmp.compression, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.taille_image_totale, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.resolutionh, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.resolutionv, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.nbrcouleur, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.nbrcouleuri, (buffer + position), 4);
    position += 4;

    /*
    printf("taille image             :%d\n",fichier->entetebmp.taille_image);
    printf("largeur                  :%d\n",fichier->entetebmp.largeur);
    printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
    printf("plans                    :%d\n",fichier->entetebmp.plans);
    printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
    printf("compression              :%d\n",fichier->entetebmp.compression);
    printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
    printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
    printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
    printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
    printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
    */

    if (fichier->entetebmp.plans != 1 || fichier->entetebmp.profondeur != 24 || fichier->entetebmp.compression != 0 || fichier->entetebmp.nbrcouleur != 0 || fichier->entetebmp.nbrcouleuri != 0)
    {
        printf("Impossible de charger l'image\n");
        free(fichier);
        free(buffer);
        return 0;
    }

    // mise de l'image en memoire

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--)
    {
        for (j = 0; j < fichier->entetebmp.largeur; j++)
        {
            memcpy(&fichier->image[i][j].b, (buffer + position), 1);
            position += 1;
            memcpy(&fichier->image[i][j].g, (buffer + position), 1);
            position += 1;
            memcpy(&fichier->image[i][j].r, (buffer + position), 1);
            position += 1;
        }
        for (k = 0; k < fichier->entetebmp.largeur % 4; k++)
        {
            memcpy(&zero, (buffer + position), 1);
            position += 1;
        }
    }

    free(buffer);
    return fichier;
}

// -3 //enregistrer l'image en format .cmp
int enregistrer(const char* nom, struct fichierimage* fichier)
{
    FILE* f;
    int i, j, k;
    unsigned char zero = (unsigned char)0;
    unsigned char* buffer;
    int position = 0;
    int longueur = 14 + fichier->entetefichier.taille_fichier;
    buffer = (unsigned char*)malloc(longueur * sizeof(unsigned char));

    // ecriture de l'entete du fichier

    /*
    printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
    printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
    printf("reserve                  :%d\n",fichier->entetefichier.reserve);
    printf("debut                    :%d\n",fichier->entetefichier.debut);
    */

    memcpy((buffer + position), &fichier->entetefichier.idformat, 2);
    position += 2;
    memcpy((buffer + position), &fichier->entetefichier.taille_fichier, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetefichier.reserve, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetefichier.debut, 4);
    position += 4;

    // ecriture de l'entete de l'image

    /*
    printf("taille image             :%d\n",fichier->entetebmp.taille_image);
    printf("largeur                  :%d\n",fichier->entetebmp.largeur);
    printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
    printf("plans                    :%d\n",fichier->entetebmp.plans);
    printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
    printf("compression              :%d\n",fichier->entetebmp.compression);
    printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
    printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
    printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
    printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
    printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
    */

    memcpy((buffer + position), &fichier->entetebmp.taille_image, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.largeur, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.hauteur, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.plans, 2);
    position += 2;
    memcpy((buffer + position), &fichier->entetebmp.profondeur, 2);
    position += 2;
    memcpy((buffer + position), &fichier->entetebmp.compression, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.taille_image_totale, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.resolutionh, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.resolutionv, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.nbrcouleur, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.nbrcouleuri, 4);
    position += 4;

    if (fichier->entetebmp.plans != 1 || fichier->entetebmp.profondeur != 24 || fichier->entetebmp.compression != 0 || fichier->entetebmp.nbrcouleur != 0 || fichier->entetebmp.nbrcouleuri != 0)
    {
        printf("Impossible d'enregistrer l'image\n");
        free(buffer);
        return 0;
    }

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--)
    {
        for (j = 0; j < fichier->entetebmp.largeur; j++)
        {
            memcpy((buffer + position), &fichier->image[i][j].b, 1);
            position += 1;
            memcpy((buffer + position), &fichier->image[i][j].g, 1);
            position += 1;
            memcpy((buffer + position), &fichier->image[i][j].r, 1);
            position += 1;
        }
        for (k = 0; k < fichier->entetebmp.largeur % 4; k++)
        {
            memcpy((buffer + position), &zero, 1);
            position += 1;
        }
    }

    f = fopen(nom, "wb");
    fwrite((unsigned char*)buffer, 1, longueur, f);
    fclose(f);
    free(buffer);
    return 1;
}

//creation d'une image "vide" tout en noir
struct fichierimage* nouveau(int largeur, int hauteur)
{
    int i, j;
    struct fichierimage* fichier;
    int longueur;

    if (largeur > 5000 || hauteur > 5000 || largeur <= 0 || hauteur <= 0)
    {
        return(NULL);
    }

    longueur = 14 + 40 + 3 * largeur * hauteur + (largeur % 4) * hauteur;
    fichier = (struct fichierimage*)malloc(sizeof(struct fichierimage));

    // ecriture de l'entete du fichier

    fichier->entetefichier.idformat[0] = 'B';
    fichier->entetefichier.idformat[1] = 'M';
    fichier->entetefichier.taille_fichier = 40 + 3 * largeur * hauteur + (largeur % 4) * hauteur;
    fichier->entetefichier.reserve = 0;
    fichier->entetefichier.debut = 54;

    // ecriture de l'entete de l'image

    fichier->entetebmp.taille_image = 40;
    fichier->entetebmp.largeur = largeur;
    fichier->entetebmp.hauteur = hauteur;
    fichier->entetebmp.plans = 1;
    fichier->entetebmp.profondeur = 24;
    fichier->entetebmp.compression = 0;
    fichier->entetebmp.taille_image_totale = 40 + 3 * largeur * hauteur + (largeur % 4) * hauteur;
    fichier->entetebmp.resolutionh = 1;
    fichier->entetebmp.resolutionv = 1;
    fichier->entetebmp.nbrcouleur = 0;
    fichier->entetebmp.nbrcouleuri = 0;

    // lecture de l'ente du fichier

    /*
    printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
    printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
    printf("reserve                  :%d\n",fichier->entetefichier.reserve);
    printf("debut                    :%d\n",fichier->entetefichier.debut);
    */

    // lecture de l'ente de l'image

    /*
    printf("taille image             :%d\n",fichier->entetebmp.taille_image);
    printf("largeur                  :%d\n",fichier->entetebmp.largeur);
    printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
    printf("plans                    :%d\n",fichier->entetebmp.plans);
    printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
    printf("compression              :%d\n",fichier->entetebmp.compression);
    printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
    printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
    printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
    printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
    printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
    */

    // mise de l'image en memoire

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--)
    {
        for (j = 0; j < fichier->entetebmp.largeur; j++)
        {
            fichier->image[i][j].b = 0;
            fichier->image[i][j].g = 0;
            fichier->image[i][j].r = 0;
        }
    }

    return fichier;
}

//Donne la moyenne ( luminance de chaque pixel )
float Moyenne(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    float luminanceCumul = 0;
    
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            luminanceCumul += (base->image[i][j].b + base->image[i][j].r + base->image[i][j].g) / 3;
        }
    }
    return luminanceCumul / (x*y) ;
}

//Trie le tableau donner en parametre dans l'ordre croissant
void Trie(pixels* a, int n) {
    int trou;
    int j;
    for (int i = 0; i < n; i++) {
        if (a[i + 1].r && a[i].r > a[i + 1].r) {
            trou = a[i].r;
            a[i].r = a[i + 1].r;
            a[i + 1].r = trou;
        }
        j = i;
        while (a[j].r < a[j - 1].r && a[j - 1].r) {
            trou = a[j].r;
            a[j].r = a[j - 1].r;
            a[j - 1].r = trou;
            j--;
        }
    }
}

//Trie le tableau donner en parametre dans l'ordre decroissant
void InversTrie(pixels* a) {
    int trou;
    int nb = 9;
    int j;
    for (int i = 0; i < 9; i++) {
        if (a[i + 1].r && a[i].r < a[i + 1].r) {
            trou = a[i].r;
            a[i].r = a[i + 1].r;
            a[i + 1].r = trou;
        }
        j = i;
        while (a[j].r > a[j - 1].r && a[j - 1].r) {
            trou = a[j].r;
            a[j].r = a[j - 1].r;
            a[j - 1].r = trou;
            j--;
        }
    }
}

//Retourne la valeur medianne
struct pixels Median(struct pixels* a, int n) {
    struct pixels res;
    int nb = 9;
    
    Trie(a, n);

    if (n % 2 == 0) {
        res = a[n / 2 + 1];
    }
    else{
        res = a[(n + 1) / 2];
    }
    return res;
}

//Retourne la valeur moyenne du tableau (le masque) selon un coeficient commun
struct pixels Moyenneur(struct pixels* a, int nb) {
    struct pixels res;
    float resul;
   
    resul = 0;
    for (int i = 0; i < nb; i++){
        resul += (float)a[i].r;
    }
    res.r = (int)(resul / nb);

    resul = 0;
    for (int i = 0; i < nb; i++) {
        resul += (float)a[i].g;
    }
    res.g = (int)(resul / nb);

    resul = 0;
    for (int i = 0; i < nb; i++) {
        resul += (float)a[i].b;
    }
    res.b = (int)(resul / nb);
 
    return res;
}

//Retourne la valeur d'un pixel selon un tableau et selon un coeficient different pour chaque valeur du tableau
struct pixels Convolu(pixels* a, int* b, int nb) {
    struct pixels res;
    float resul;
    if (nb == 4)
    {
        fact[0] = 3,5;
        fact[1] = -1;
        fact[2] = -0,5;
    }
    if (nb == 6)
    {
        fact[0] = 5;
        fact[1] = -1;
        fact[2] = -0, 5;
    }
    if (nb == 9)
    {
        fact[0] = 7;
        fact[1] = -1;
        fact[2] = -0, 5;
    }

    resul = 0;
    for (int i = 0; i < nb; i++) {
        resul += (float)a[i].r * fact[b[i]];
    }
    res.r = (int)resul;

    resul = 0;
    for (int i = 0; i < nb; i++) {
        resul += (float)a[i].g * fact[b[i]];
    }
    res.g = (int)resul;

    resul = 0;
    for (int i = 0; i < nb; i++) {
        resul += (float)a[i].b * fact[b[i]];
    }
    res.b = (int)resul;

    return res;
}

// Retourne la valeur d'un pixel selon le filtre Sobel
struct pixels Sobel(pixels* a, int nb) {
    struct pixels res;
    float resulR = 0;
    float resulG = 0;
    float resulB = 0;
    if (nb == 9)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) // Sobel X
            {
                ffact[0] = -1;
                ffact[1] = 0;
                ffact[2] = 1;
                ffact[3] = -2;
                ffact[4] = 0;
                ffact[5] = 2;
                ffact[6] = -1;
                ffact[7] = 0;
                ffact[8] = 1;
            }
            else // Sobel Y
            {
                ffact[0] = -1;
                ffact[1] = -2;
                ffact[2] = -1;
                ffact[3] = 0;
                ffact[4] = 0;
                ffact[5] = 0;
                ffact[6] = 1;
                ffact[7] = 2;
                ffact[8] = 1;
            }

            for (int i = 0; i < nb; i++) {
                resulR += (float)a[i].r * ffact[i];
            }

            for (int i = 0; i < nb; i++) {
                resulG += (float)a[i].g * ffact[i];
            }

            for (int i = 0; i < nb; i++) {
                resulB += (float)a[i].b * ffact[i];
            }

        }

        res.r = (int)resulR / 2;
        res.g = (int)resulG / 2;
        res.b = (int)resulB / 2;
    }

    if (nb != 9)
    {
        res = a[4];
    }

    return res;
}

struct pixels Laplacian(Matrice3x3 a, int nb) {
    struct pixels res;
    float resul;

    if (nb == 4) {
        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].r * KernelLap4[a.mult[i]];
        }
        res.r = (int)resul;


        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].g * KernelLap4[a.mult[i]];
        }
        res.g = (int)resul;


        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].b * KernelLap4[a.mult[i]];
        }
        res.b = (int)resul;
    }

    if (nb == 6) {
        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].r * KernelLap6[a.mult[i]];
        }
        res.r = (int)resul;


        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].g * KernelLap6[a.mult[i]];
        }
        res.g = (int)resul;


        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].b * KernelLap6[a.mult[i]];
        }
        res.b = (int)resul;
    }

    if (nb == 9) {
        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].r * KernelLap9[a.mult[i]];
        }
        res.r = (int)resul;


        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].g * KernelLap9[a.mult[i]];
        }
        res.g = (int)resul;


        resul = 0;
        for (int i = 0; i < nb; i++) {
            resul += (float)a.Window[i].b * KernelLap9[a.mult[i]];
        }
        res.b = (int)resul;
    }

    return res;
}

//Vide le flux d'entrer des donnée indesirable
void clear(){
    while (getchar() != '\n');
}

// copie l'image en parametre
struct fichierimage* Copie(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = base->image[i][j].b;
            res->image[i][j].g = base->image[i][j].g;
            res->image[i][j].r = base->image[i][j].r;
        }
    }
    return res;
}

//Verifier et ajoute ".bmp" si necessaire
void VerifNomImage(char a[20]) {
    char bmp[5] = {".bmp"};
    int i = 0;
    while (a[i] != 0 ){
        i++;
    }
    if (a[i - 4] != '.' || a[i - 3] != 'b' || a[i - 2] != 'm' || a[i - 1] != 'p'){
        for (int j = i; j < i + 4; j++) {
            a[j] = bmp[j - i];
        }
    }
    printf("%s a bien été charger\n", a);
}

//Verifie si l'image est en niveau de gris
bool NivDeGris_Verif(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    bool a = true;
    int i = 0;
    int j = 0;

    while (base->image[i][j].b == base->image[i][j].g == base->image[i][j].r || i < x) {
        while (base->image[i][j].b == base->image[i][j].g == base->image[i][j].r || j < y) {
            j++;
        }
        i++;
    }
    if (!(base->image[i][j].b == base->image[i][j].g == base->image[i][j].r)) {
        a = false;
    }
    return a;
}

//Verifie si un element est deja dans la list
bool InsideList(int* list, int &a, int &t) {
    bool b = false;
    int i = 0;
    while ( i < t  && list[i] != a) {
        i++;
    }
    if (list[i] == a)
    {
        b = true;
    }
    return b;
}

// 2 // met l'image passer en parametre en niveau de gris
struct fichierimage* NivDeGris(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    int som;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            som = base->image[i][j].b + base->image[i][j].g + base->image[i][j].r;
            res->image[i][j].b = som / 3;
            res->image[i][j].g = som / 3;
            res->image[i][j].r = som / 3;
        }
    }
    return res;
}

// donne la variance de l'image donner en parametre
double Variance(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    float moy = Moyenne(base);

    double somres = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            somres += pow( (  (base->image[i][j].b + base->image[i][j].g + base->image[i][j].r)/ 3) - moy, 2);
        }
    }

    return somres /= x * y;;
}

//donne l'ecart-type de l'image donner en parametre
double Ecart_type(struct fichierimage* base) {
    return sqrt(Variance(base));
}

//donne la variation de niveau de gris de l'image donner en parametre 
float VariationNivDeDris(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);

    res = Copie(base);
    if (!NivDeGris_Verif(res)) {
        printf("Mise de l'image en niveau de gris ...\n");
        res = NivDeGris(res);
    }

    float max = 0;
    float min = 255;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (base->image[i][j].b > max) {
                max = base->image[i][j].b;
            }
            if (base->image[i][j].b < min){
                min = base->image[i][j].b;
            }
        }
    }
    float var = (max - min) / (max + min);
    
    return var;
}

//Creer l'histogramme Bleu de l'image donnée en parametre
void HistogrammeBlue(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            HistogrammBlue[base->image[i][j].b]++;
        }
    }
}

//Creer l'histogramme Vert de l'image donnée en parametre
void HistogrammeGreen(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            HistogrammGreen[base->image[i][j].g]++;
        }
    }
}

//Creer l'histogramme Rouge de l'image donnée en parametre
void HistogrammeRed(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            HistogrammRed[base->image[i][j].r]++;
        }
    }
}

//Normaliser l'histogramme
void Normalisation(struct fichierimage* base,float histo[255]) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;

    for (int i = 0; i < 255; i++)
    {
        Histogramm_Normaliser[i] = histo[i] / (x * y);
    }
}

// Donne la densité de probabilité normalisée
void DensitéDeProbaNorm() {
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < i; j++) {
            C_de_I[i] += Histogramm_Normaliser[j];
        }
    }
}

// Transformation des niveau de gris de l'image
void TransformNivDeGris(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            base->image[i][j].b = (int)(C_de_I[base->image[i][j].b] * 255);
            base->image[i][j].g = (int)(C_de_I[base->image[i][j].g] * 255);
            base->image[i][j].r = (int)(C_de_I[base->image[i][j].r] * 255);
        }
    }
}

// Transformation des niveau de bleu de l'image
void TransformBlue(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            base->image[i][j].b = (int)(C_de_I[base->image[i][j].b] * 255);
        }
    }
}

// Transformation des niveau de vert de l'image
void TransformGreen(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            base->image[i][j].g = (int)(C_de_I[base->image[i][j].g] * 255);
        }
    }
}

// Transformation des niveau de rouge de l'image
void TransformRed(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            base->image[i][j].r = (int)(C_de_I[base->image[i][j].r] * 255);
        }
    }
}

//convertie l'image rgb en tsl (fonction pas pres)
struct fichierimage* ConversionRgbHsb(struct fichierimage* base, int deg) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {

        }
    }
    return res;
}

//Change les etiquettes a supprimer avec des pixels deja present
void etiq2(int** mat, int etiq_del, int etiq_add, int y, int x) {
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (mat[i][j] == etiq_del)
            {
                mat[i][j] = etiq_add;
            }
        }
    }
}

// Compare une forme a un cercle(pas pres)
void Compacite(int** mat, int nb, int num, int y, int x) {
    int aire = 0;
    int perim = 0;
    int comp = 0;
    int* list = (int*)malloc(nb * sizeof(int));

    
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (mat[i][j] != 0 && !InsideList(list, mat[i][j],nb))
            {
                list[comp] = mat[i][j];
                comp++;
            }

        }
    }
}

// utilisation de la methode Otsu pour trouver le seuil
float Otsu(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;

    int histo[256] = { 0 };
    float his_norm[256] = { 0 };
    
    int nb_pix = x * y;
    float VB = 0.0;
    float VH = 0.0;
    float moyB = 0.0;
    float moyH = 0.0;
    float somB = 0.0;
    float somH = 0.0;
    int moy;
    float max = 0;
    int Smax = 0;
    int nb_intens = 0;
    float VarInter;
    float VarIntra;

    // creation de l'histogramme et comptage des differente intensité
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++) {
            histo[base->image[i][j].b]++;
            if (histo[base->image[i][j].b] == 1)
            {
                nb_intens++;
            }
        }
    }

    // normalisation de l'histogramme
    for (int i = 0; i < 256; i++)
    {
        his_norm[i] = (float)histo[i] / (float)nb_pix;
    }

    //Calcule de la moyenne des intensité
    moy = 0;
    for (int i = 0; i < 255; i++)
    {
        moy += i * histo[i];
    }
    moy /= nb_pix;
    

    //Calcule du seuil 
    for (int k = 0; k <= 255; k++) {

        VB = 0;
        for (int i = 0; i <= k; i++) {
            VB += his_norm[i]; // Proba de la classe "bas"
        }
        VH = 1.0 - VB; // Proba de la classe "haut"

        // Éviter division par zéro
        somB = 0;
        if (VB > 0.0) {
            for (int i = 0; i <= k; i++) {
                somB += (float)i * his_norm[i];
            }
            moyB = somB / VB; // Moyenne de la classe "bas"
        }

        somH = 0;
        if (VH > 0.0) {
            for (int i = k + 1; i <= 255; i++) {
                somH += (float)i * his_norm[i];
            }
            moyH = somH / VH; // Moyenne de la classe "haut"
        }

        // Variance intraclasse
        VarIntra = pow(k*(moyB - moy),2) + pow((255 - k) * (moyH - moy), 2);

        // Variance interclasse
        VarInter = VB * VH * pow((moyB - moyH),2);

        // Trouver le seuil optimal
        if (VarInter > max) {
            max = VarInter;
            Smax = k;
        }
    }
    printf("%f\n", max);
    printf("%d\n", Smax);
    return Smax;
}

// 1 // met l'image passer en parametre en noir et blanc
struct fichierimage* binarisation(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    int som;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            som = base->image[i][j].b + base->image[i][j].g + base->image[i][j].r;
            if (som < 383) {
                res->image[i][j].b = 0;
                res->image[i][j].g = 0;
                res->image[i][j].r = 0;
            }
            else {
                res->image[i][j].b = 255;
                res->image[i][j].g = 255;
                res->image[i][j].r = 255;
            }
        }
    }
    return res;
}

// 3 // met l'image passer en parametre a 180°
struct fichierimage* Renvers(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = base->image[y - i][x - j].b;
            res->image[i][j].g = base->image[y - i][x - j].g;
            res->image[i][j].r = base->image[y - i][x - j].r;
        }
    }
    return res;
}

// 4 // met l'image passer en parametre en miroir par rapport a l'axe "X"
struct fichierimage* MiroirX(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = base->image[i][x - j].b;
            res->image[i][j].g = base->image[i][x - j].g;
            res->image[i][j].r = base->image[i][x - j].r;
        }
    }
    return res;
}

// 5 // met l'image passer en parametre en miroir par rapport a l'axe "Y"
struct fichierimage* MiroirY(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = base->image[y - i][j].b;
            res->image[i][j].g = base->image[y - i][j].g;
            res->image[i][j].r = base->image[y - i][j].r;
        }
    }
    return res;
}

// 6 // met l'image passer en parametre en symetrie par rapport a l'axe "Y" (la premier partie de l'image separé par la mediane horizontale) 
struct fichierimage* SymetrieY(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (i <= (y/2) ){
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
            else{
                res->image[i][j].b = base->image[y - i][j].b;
                res->image[i][j].g = base->image[y - i][j].g;
                res->image[i][j].r = base->image[y - i][j].r;
            }
        }
    }
    return res;
}

// 7 // met l'image passer en parametre en symetrie par rapport a l'axe "Y" (la deuxieme partie de l'image separé par la mediane horizontale)
struct fichierimage* InversSymetrieY(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (i <= (y / 2)) {
                res->image[i][j].b = base->image[y - i][j].b;
                res->image[i][j].g = base->image[y - i][j].g;
                res->image[i][j].r = base->image[y - i][j].r;
            }
            else {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
        }
    }
    return res;
}

// 8 // met l'image passer en parametre en symetrie par rapport a l'axe "X" (la premier partie de l'image separé par la mediane vertical) 
struct fichierimage* SymetrieX(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j <= (x / 2)) {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
            else {
                res->image[i][j].b = base->image[i][x - j].b;
                res->image[i][j].g = base->image[i][x - j].g;
                res->image[i][j].r = base->image[i][x - j].r;
            }
        }
    }
    return res;
}

// 9 // met l'image passer en parametre en symetrie par rapport a l'axe "X" (la deuxieme partie de l'image separé par la mediane vertical) 
struct fichierimage* InversSymetrieX(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j <= (x / 2)) {
                res->image[i][j].b = base->image[i][x - j].b;
                res->image[i][j].g = base->image[i][x - j].g;
                res->image[i][j].r = base->image[i][x - j].r;
            }
            else {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
        }
    }
    return res;
}

// 10 // met l'image passer en parametre en symetrie par rapport aux axes "X" et "Y" (premiere partie)
struct fichierimage* SymetrieXY1(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j <= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
            if (j >= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[i][x - j].b;
                res->image[i][j].g = base->image[i][x - j].g;
                res->image[i][j].r = base->image[i][x - j].r;
            }
            if (j <= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[y - i][j].b;
                res->image[i][j].g = base->image[y - i][j].g;
                res->image[i][j].r = base->image[y - i][j].r;
            }
            if (j >= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[y - i][x - j].b;
                res->image[i][j].g = base->image[y - i][x - j].g;
                res->image[i][j].r = base->image[y - i][x - j].r;
            }
        }
    }
    return res;
}

// 11 // met l'image passer en parametre en symetrie par rapport aux axes "X" et "Y" (deuxieme partie)
struct fichierimage* SymetrieXY2(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j <= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[i][x - j].b;
                res->image[i][j].g = base->image[i][x - j].g;
                res->image[i][j].r = base->image[i][x - j].r;
            }
            if (j >= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
            if (j <= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[y - i][x - j].b;
                res->image[i][j].g = base->image[y - i][x - j].g;
                res->image[i][j].r = base->image[y - i][x - j].r;
            }
            if (j >= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[y - i][j].b;
                res->image[i][j].g = base->image[y - i][j].g;
                res->image[i][j].r = base->image[y - i][j].r;
            }
        }
    }
    return res;
}

// 12// met l'image passer en parametre en symetrie par rapport aux axes "X" et "Y" (troisieme partie)
struct fichierimage* SymetrieXY3(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j <= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[y - i][j].b;
                res->image[i][j].g = base->image[y - i][j].g;
                res->image[i][j].r = base->image[y - i][j].r;
            }
            if (j >= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[y - i][x - j].b;
                res->image[i][j].g = base->image[y - i][x - j].g;
                res->image[i][j].r = base->image[y - i][x - j].r;
            }
            if (j <= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
            if (j >= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[i][x - j].b;
                res->image[i][j].g = base->image[i][x - j].g;
                res->image[i][j].r = base->image[i][x - j].r;
            }
        }
    }
    return res;
}

// 13 // met l'image passer en parametre en symetrie par rapport aux axes "X" et "Y" (quatrieme partie)
struct fichierimage* SymetrieXY4(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j <= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[y - i][x - j].b;
                res->image[i][j].g = base->image[y - i][x - j].g;
                res->image[i][j].r = base->image[y - i][x - j].r;
            }
            if (j >= (x / 2) && i <= (y / 2)) {
                res->image[i][j].b = base->image[y - i][j].b;
                res->image[i][j].g = base->image[y - i][j].g;
                res->image[i][j].r = base->image[y - i][j].r;
            }
            if (j <= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[i][x - j].b;
                res->image[i][j].g = base->image[i][x - j].g;
                res->image[i][j].r = base->image[i][x - j].r;
            }
            if (j >= (x / 2) && i >= (y / 2)) {
                res->image[i][j].b = base->image[i][j].b;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].r = base->image[i][j].r;
            }
        }
    }
    return res;
}

// 14 // met l'image passer en parametre en symetrie par rapport a la diagonal "\" (la premier partie) 
struct fichierimage* SymetrieDiag(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    float ratio;
    float Jper;
    float Iper;
    struct fichierimage* res = nouveau(x, y);
    if (x >= y) { // cas Largeur plus grand
        ratio = (float)x / (float)y;
        // (float)j/(float)x*y
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if ((float)j/(float)i <= ratio) {
                    res->image[i][j].b = base->image[i][j].b;
                    res->image[i][j].g = base->image[i][j].g;
                    res->image[i][j].r = base->image[i][j].r;
                }
                else{
                    Jper = (float)j / (float)x;
                    Iper = (float)i / (float)y;
                    res->image[i][j].b = base->image[(int)(Jper * y)][(int)(Iper * x)].b;
                    res->image[i][j].g = base->image[(int)(Jper * y)][(int)(Iper * x)].g;
                    res->image[i][j].r = base->image[(int)(Jper * y)][(int)(Iper * x)].r;
                }
            }
        }

    }
    if (x < y) { // cas Hauteur plus grand
        ratio = (float)y / (float)x;
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if ((float)i / (float)j <= ratio) {
                    res->image[i][j].b = base->image[i][j].b;
                    res->image[i][j].g = base->image[i][j].g;
                    res->image[i][j].r = base->image[i][j].r;
                }
                else {
                    Jper = (float)j / (float)x;
                    Iper = (float)i / (float)y;
                    res->image[i][j].b = base->image[(int)(Jper * y)][(int)(Iper * x)].b;
                    res->image[i][j].g = base->image[(int)(Jper * y)][(int)(Iper * x)].g;
                    res->image[i][j].r = base->image[(int)(Jper * y)][(int)(Iper * x)].r;
                }
            }
        }
    }
    return res;
}

// 15 // met l'image passer en parametre en symetrie par rapport a la diagonal "\" (la deuxieme partie)
struct fichierimage* InversSymetrieDiag(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    float ratio;
    float Jper;
    float Iper;
    struct fichierimage* res = nouveau(x, y);
    if (x >= y) { // cas Largeur plus grand
        ratio = (float)x / (float)y;
        // (float)j/(float)x*y
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if ((float)j / (float)i <= ratio) {
                
                    Jper = (float)j / (float)x;
                    Iper = (float)i / (float)y;
                    res->image[i][j].b = base->image[(int)(Jper * y)][(int)(Iper * x)].b;
                    res->image[i][j].g = base->image[(int)(Jper * y)][(int)(Iper * x)].g;
                    res->image[i][j].r = base->image[(int)(Jper * y)][(int)(Iper * x)].r;
                }
                else {
                    res->image[i][j].b = base->image[i][j].b;
                    res->image[i][j].g = base->image[i][j].g;
                    res->image[i][j].r = base->image[i][j].r;
                }
            }
        }

    }
    if (x < y) { // cas Hauteur plus grand
        ratio = (float)y / (float)x;
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if ((float)i / (float)j <= ratio) {
                    Jper = (float)j / (float)x;
                    Iper = (float)i / (float)y;
                    res->image[i][j].b = base->image[(int)(Jper * y)][(int)(Iper * x)].b;
                    res->image[i][j].g = base->image[(int)(Jper * y)][(int)(Iper * x)].g;
                    res->image[i][j].r = base->image[(int)(Jper * y)][(int)(Iper * x)].r;
                }
                else {
                    res->image[i][j].b = base->image[i][j].b;
                    res->image[i][j].g = base->image[i][j].g;
                    res->image[i][j].r = base->image[i][j].r;
                }
            }
        }
    }
    return res;
}

// 16 // met l'image passer en parametre en symetrie par rapport a la diagonal "/" (la premier partie) 
struct fichierimage* SymetrieDiag2(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    int compt = 0;
    float ratio;
    float diff;
    float dif2;
    float halfDiff;
    float tour;
    float Jper;
    float Iper;
    struct fichierimage* res = nouveau(x, y);
    if (x >= y) { // cas Largeur plus grand
        ratio = ((float)x + (float)y) / 2;
        diff = ((float)x - (float)y );
        halfDiff = diff / 2;
        tour = (float)x * (float)y;
        dif2 = diff / tour;
        // (float)j/(float)x*y
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (compt <= tour / 2) {
                    halfDiff -= dif2;
                    if (((float)j + (float)i) <= ratio + halfDiff) {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                    else {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                }
                else{
                    halfDiff += dif2;
                    if (((float)j + (float)i) <= ratio - halfDiff) {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                    else {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                }
                compt++;
            }
        }
    }
    if (x < y) { // cas Hauteur plus grand
        ratio = ((float)x + (float)y) / 2;
        diff = ((float)y - (float)x);
        halfDiff = diff / 2;
        tour = (float)x * (float)y;
        dif2 = diff / tour;
        // (float)j/(float)x*y
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (compt <= tour / 2) {
                    halfDiff -= dif2;
                    if (((float)j + (float)i) <= ratio + halfDiff) {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                    else {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                }
                else {
                    halfDiff += dif2;
                    if (((float)j + (float)i) <= ratio - halfDiff) {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                    else {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                }
                compt++;
            }
        }
    }
    return res;
}

// 17 // met l'image passer en parametre en symetrie par rapport a la diagonal "/" (la deuxieme partie) 
struct fichierimage* InversSymetrieDiag2(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    int compt = 0;
    float ratio;
    float diff;
    float dif2;
    float halfDiff;
    float tour;
    float Jper;
    float Iper;
    struct fichierimage* res = nouveau(x, y);
    if (x >= y) { // cas Largeur plus grand
        ratio = ((float)x + (float)y) / 2;
        diff = ((float)x - (float)y);
        halfDiff = diff / 2;
        tour = (float)x * (float)y;
        dif2 = diff / tour;
        // (float)j/(float)x*y
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (compt <= tour / 2) {
                    halfDiff -= dif2;
                    if (((float)j + (float)i) <= ratio + halfDiff) {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                    else {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                }
                else {
                    halfDiff += dif2;
                    if (((float)j + (float)i) <= ratio - halfDiff) {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                    else {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                }
                compt++;
            }
        }
    }
    if (x < y) { // cas Hauteur plus grand
        ratio = ((float)x + (float)y) / 2;
        diff = ((float)y - (float)x);
        halfDiff = diff / 2;
        tour = (float)x * (float)y;
        dif2 = diff / tour;
        // (float)j/(float)x*y
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (compt <= tour / 2) {
                    halfDiff -= dif2;
                    if (((float)j + (float)i) <= ratio + halfDiff) {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                    else {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                }
                else {
                    halfDiff += dif2;
                    if (((float)j + (float)i) <= ratio - halfDiff) {
                        Jper = (float)j / (float)x;
                        Iper = (float)i / (float)y;
                        res->image[i][j].b = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].b;
                        res->image[i][j].g = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].g;
                        res->image[i][j].r = base->image[y - (int)(Jper * y)][x - (int)(Iper * x)].r;
                    }
                    else {
                        res->image[i][j].b = base->image[i][j].b;
                        res->image[i][j].g = base->image[i][j].g;
                        res->image[i][j].r = base->image[i][j].r;
                    }
                }
                compt++;
            }
        }
    }
    return res;
}

// 18 // pivot l'image passer en parametre a 90° vers la gauche
struct fichierimage* PivotG(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(y, x);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            res->image[i][j].b = base->image[(y - 1) - j][i].b;
            res->image[i][j].g = base->image[(y - 1) - j][i].g;
            res->image[i][j].r = base->image[(y - 1) - j][i].r;
        }
    }
    return res;
}

// 19 // pivot l'image passer en parametre a 90° vers la droite
struct fichierimage* PivotD(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(y, x);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            res->image[i][j].b = base->image[j][(x - 1) - i].b;
            res->image[i][j].g = base->image[j][(x - 1) - i].g;
            res->image[i][j].r = base->image[j][(x - 1) - i].r;
        }
    }
    return res;
}

// 20 // met l'image passer en parametre en negative
struct fichierimage* Negative(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    int som;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            som = base->image[i][j].b + base->image[i][j].g + base->image[i][j].r;
            res->image[i][j].b = 255 - base->image[i][j].b;
            res->image[i][j].g = 255 - base->image[i][j].g;
            res->image[i][j].r = 255 - base->image[i][j].r;
        }
    }
    return res;
}

// 21 // met l'image passer en parametre en monochrome rouge
struct fichierimage* MonochromeRed(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = 0;
            res->image[i][j].g = 0;
            res->image[i][j].r = base->image[i][j].r;
        }
    }
    return res;
}

// 22 // met l'image passer en parametre en monochrome bleu
struct fichierimage* MonochromeBlue(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = base->image[i][j].b;
            res->image[i][j].g = 0;
            res->image[i][j].r = 0;
        }
    }
    return res;
}

// 23 // met l'image passer en parametre en monochrome vert
struct fichierimage* MonochromeGreen(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            res->image[i][j].b = 0;
            res->image[i][j].g = base->image[i][j].g;
            res->image[i][j].r = 0;
        }
    }
    return res;
}

// 24 // met l'image passer en parametre en monochrome magenta
struct fichierimage* MonochromeMagenta(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    int som;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            som = (base->image[i][j].r + base->image[i][j].b) / 2;
            res->image[i][j].b = som;
            res->image[i][j].g = 0;
            res->image[i][j].r = som;
        }
    }
    return res;
}

// 25 // met l'image passer en parametre en monochrome cyan
struct fichierimage* MonochromeCyan(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    int som;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            som = (base->image[i][j].g + base->image[i][j].b) / 2;
            res->image[i][j].b = som;
            res->image[i][j].g = som;
            res->image[i][j].r = 0;
        }
    }
    return res;
}

// 26 // met l'image passer en parametre en monochrome jaune
struct fichierimage* MonochromeYellow(struct fichierimage* base)
{
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    int som;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            som = (base->image[i][j].g + base->image[i][j].r) / 2;
            res->image[i][j].b = 0;
            res->image[i][j].g = som;
            res->image[i][j].r = som;
        }
    }
    return res;
}

// 27 // Agrandit l'image par rapport a l'echelle donner en parametre
struct fichierimage* Agrandissement(struct fichierimage* base, int Echelle) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x*Echelle, y*Echelle);
    
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            for (int k = i*Echelle; k < i * Echelle  + Echelle; k++){
                for (int l = j*Echelle; l < j * Echelle + Echelle; l++){
                    res->image[k][l].b = base->image[i][j].b;
                    res->image[k][l].g = base->image[i][j].g;
                    res->image[k][l].r = base->image[i][j].r;
                }

            }

            
        }
    }
    return res;
}

// 28 // Reduit l'image par rapport a l'echelle donner en parametre
struct fichierimage* Reduction(struct fichierimage* base, int Echelle) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    float r;
    float g;
    float b;
    struct fichierimage* res = nouveau(x / Echelle, y / Echelle);

    for (int i = 0; i < y / Echelle; i++) {
        for (int j = 0; j < x / Echelle; j++) {
            for (int k = i * Echelle; k < i * Echelle + Echelle; k++) {
                r = 0;
                g = 0;
                b = 0;
                for (int l = j * Echelle; l < j * Echelle + Echelle; l++) {
                    b += base->image[k][l].b;
                    g += base->image[k][l].g;
                    r += base->image[k][l].r;
                }
            }
            res->image[i][j].b = (int)(b / Echelle);
            res->image[i][j].g = (int)(g / Echelle);
            res->image[i][j].r = (int)(r / Echelle);
        }
    }
    return res;
}

// 29 //fait l'egalisation en niveau de gris de l'image passer en parametre
struct fichierimage* EgalisationGray(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    bool a;

    res = Copie(base);
    a = NivDeGris_Verif(res);
    if (!a) {
        printf("Mise de l'image en niveau de gris ...\n");
        res = NivDeGris(res);
    }

    HistogrammeBlue(res);
    Normalisation(res, HistogrammBlue);
    DensitéDeProbaNorm();
    TransformNivDeGris(res);

    return res;
}

// 29 bis // fait l'egalisation en couleur de l'image passer en parametre ( fonction pas pres )
struct fichierimage* EgalisationColor(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);
    res = Copie(base);
    
    HistogrammeBlue(res);
    HistogrammeGreen(res);
    HistogrammeRed(res);

    Normalisation(res, HistogrammBlue);
    DensitéDeProbaNorm();
    TransformBlue(res);

    Normalisation(res, HistogrammGreen);
    DensitéDeProbaNorm();
    TransformGreen(res);

    Normalisation(res, HistogrammRed);
    DensitéDeProbaNorm();
    TransformRed(res);

    return res;
}

// 30 //Utilise le filtre median sur l'image donner en parametre
struct fichierimage* FiltreMedian(struct fichierimage* base){
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    pixels masque[9] = { 0 };
    int comp;
    int vide;
    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            comp = 0;
            for (int k = i - 1;k < i + 2; k++) {
                for (int l = j - 1; l < j + 2; l++){
                    if ( k >= 0 && l >= 0 && k <= y && l <= x){
                        masque[comp].b = base->image[k][l].b;
                        masque[comp].r = base->image[k][l].r;
                        masque[comp].g = base->image[k][l].g;
                        comp++;
                    }
                }
            }
            res->image[i][j] = Median(masque, comp);
        }
    }
    return res;
}

// 31 //Utilise la convolution sur l'image donner en parametre("Blurry")
struct fichierimage* FiltreMoyenneur(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    pixels masque[9] = { 0 };
    int comp;
    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            comp = 0;
            for (int k = i - 1;k < i + 2;k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    if (k >= 0 && l >= 0 && k <= y && l <= x) {
                        masque[comp].b = base->image[k][l].b;
                        masque[comp].r = base->image[k][l].r;
                        masque[comp].g = base->image[k][l].g;
                        comp++;
                    }
                }
            }
            res->image[i][j] = Moyenneur(Mat.Window,comp);
        }
    }
    return res;
}

// 31 Bis //Utilise la convolution sur l'image donner en parametre("Egde") ( fonction pas pres )
struct fichierimage* Convolution(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    int comp;
    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            comp = 0;
            for (int k = i - 1;k < i + 2;k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    if (k >= 0 && l >= 0 && k <= y && l <= x) {
                        masque[comp].b = base->image[k][l].b;
                        masque[comp].r = base->image[k][l].r;
                        masque[comp].g = base->image[k][l].g;
                        index[comp] = abs(k - i) + abs(l - j);
                        comp++;
                    }
                }
            }
            res->image[i][j] = Convolu(masque, index, comp);
        }
    }
    return res;
}

// 32 // la fonction incruste la 1ere image (qui a un fond bleu) donner en parametre sur la 2nd 
// pour se faire la fonction calcule la distance entre un pixel de l'image a incruster et un pixel bleu
//
//la fonction fonctionne
struct fichierimage* FondBleu(struct fichierimage* base, struct fichierimage* fond) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;

    int xf = fond->entetebmp.largeur;
    int yf = fond->entetebmp.hauteur;

    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (sqrt(pow(base->image[i][j].b - 255,2) + pow(base->image[i][j].g,2) + pow(base->image[i][j].g, 2)) < 195) {
                res->image[i][j].r = fond->image[i][j].r;
                res->image[i][j].g = fond->image[i][j].g;
                res->image[i][j].b = fond->image[i][j].b;
            }
            else {
                res->image[i][j].r = base->image[i][j].r;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].b = base->image[i][j].b;
            }
        }
    }
    return res;
}

// 33 // la fonction incruste la 1ere image (qui a un fond vert) donner en parametre sur la 2nd 
// pour se faire la fonction calcule la distance entre un pixel de l'image a incruster et un pixel vert
//
//la fonction fonctionne
struct fichierimage* FondVert(struct fichierimage* base, struct fichierimage* fond) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;

    int xf = fond->entetebmp.largeur;
    int yf = fond->entetebmp.hauteur;

    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (sqrt(pow(base->image[i][j].g - 255, 2) + pow(base->image[i][j].b, 2) + pow(base->image[i][j].g, 2)) < 195) {
                res->image[i][j].r = fond->image[i][j].r;
                res->image[i][j].g = fond->image[i][j].g;
                res->image[i][j].b = fond->image[i][j].b;
            }
            else {
                res->image[i][j].r = base->image[i][j].r;
                res->image[i][j].g = base->image[i][j].g;
                res->image[i][j].b = base->image[i][j].b;
            }
        }
    }
    return res;
}

// 34 // la fonction modifie la luminosité de l'image donner en parametre
struct fichierimage* Luminosité(struct fichierimage* base, int modif) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (base->image[i][j].b + modif < 0) {
                res->image[i][j].b = 0;
            }
            if (base->image[i][j].b + modif > 255) {
                res->image[i][j].b = 255;
            }
            if (base->image[i][j].b + modif > 0 && base->image[i][j].b + modif < 255) {
                res->image[i][j].b = base->image[i][j].b + modif;
            }

            if (base->image[i][j].g + modif < 0) {
                res->image[i][j].g = 0;
            }
            if (base->image[i][j].g + modif > 255) {
                res->image[i][j].g = 255;
            }
            if (base->image[i][j].g + modif > 0 && base->image[i][j].g + modif < 255) {
                res->image[i][j].g = base->image[i][j].g + modif;
            }

            if (base->image[i][j].r + modif < 0) {
                res->image[i][j].r = 0;
            }
            if (base->image[i][j].r + modif > 255) {
                res->image[i][j].r = 255;
            }
            if (base->image[i][j].r + modif > 0 && base->image[i][j].r + modif < 255) {
                res->image[i][j].r = base->image[i][j].r + modif;
            }
        }
    }
    return res;
}

// 35 // effectue une rotation de image avec un certain degres ( fonction pas pres)
struct fichierimage* Rotation(struct fichierimage* base, int deg) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    int x1;
    int y1;
    int rad = deg * 180/M_PI;
    struct fichierimage* res = nouveau(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            x1 = (int)(cos(deg) *  (j - (x / 2)) + sin(deg) * (i - (y / 2)) + (x / 2));
            y1 = (int)(cos(deg) * (i - (y / 2)) - sin(deg) * (j - (x / 2)) + (y / 2));
            if ( x1 < x && x1 >= 0 && y1 < y && y1 >= 0 ) {
                res->image[y1][x1] = base->image[i][j];
            }
        }
    }
    return res;
}

// 36 // Utilise le filtre Laplacien sur l'image donner en parametre
struct fichierimage* FiltreSobel(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    int comp;
    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            comp = 0;
            for (int k = i - 1;k < i + 2;k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    if (k >= 0 && l >= 0 && k <= y && l <= x) {
                        masque[comp].b = base->image[k][l].b;
                        masque[comp].r = base->image[k][l].r;
                        masque[comp].g = base->image[k][l].g;
                        comp++;
                    }
                }
            }
            res->image[i][j] = Sobel(masque, comp);
        }
    }
    return res;
}

// 36 //Utilise le filtre Laplacien sur l'image donner en parametre
struct fichierimage* FiltreLaplacien(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    int comp;
    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            comp = 0;
            for (int k = i - 1;k < i + 2;k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    if (k >= 0 && l >= 0 && k <= y && l <= x) {
                        masque[comp].b = base->image[k][l].b;
                        masque[comp].r = base->image[k][l].r;
                        masque[comp].g = base->image[k][l].g;
                        ffact[comp] = abs(k - i) + abs(l - j);
                        comp++;
                    }
                }
            }
            res->image[i][j] = Laplacian(Mat, comp);
        }
    }
    return res;
}

// 37 // Etiquettage des forme dans une image binaire(ligne par ligne)
void Etiquettage(struct fichierimage* base, int** etiq, int& nb) {
    int y = base->entetebmp.hauteur;
    int x = base->entetebmp.largeur;
    int* etiqList;
    int nb_etiq = 1;
    bool flag;
    int k;

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            etiq[i][j] = 0;
        }
    }

    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++) {
            if (etiq[i][j] == 0 && base->image[i][j].b == 255)
            {
                flag = false;
                for (int k = i - 1; k < i + 1; k++)
                {
                    for (int l = j - 1; l < j + 1; l++)
                    {
                        if (k >= 0 && k < x && l >= 0 && l < y)
                        {
                            if (etiq[k][l] > 0) {
                                etiq[i][j] = etiq[k][l];
                                flag = true;
                            }
                        }
                    }
                }

                if (flag == false)
                {
                    etiq[i][j] = nb_etiq;
                    nb_etiq++;
                }

                for (int k = i - 1; k < i + 1; k++)
                {
                    for (int l = j - 1; l < j + 1; l++)
                    {
                        if (k >= 0 && k < x && l >= 0 && l < y)
                        {
                            if (etiq[k][l] == 0 && base->image[k][l].b == 255) {
                                etiq[k][l] = etiq[i][j];
                            }
                        }
                    }
                }
            }
        }
    }

    //unification des etiquettes N°3
    for (int i = y - 1; i > 1; i--) {
        for (int j = x - 1; j > 1; j--) {
            if (etiq[i][j] != 0)
            {
                if (etiq[i - 1][j] > 0 && etiq[i - 1][j] != etiq[i][j])
                {
                    etiq2(etiq, etiq[i - 1][j], etiq[i][j], y, x);
                }
                if (etiq[i][j - 1] > 0 && etiq[i][j - 1] != etiq[i][j])
                {
                    etiq2(etiq, etiq[i][j - 1], etiq[i][j], y, x);
                }
            }
        }
    }

    nb_etiq = 0;
    etiqList = (int*)malloc(sizeof(int));
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++) {
            if (!InsideList(etiqList, etiq[i][j], nb_etiq) && etiq[i][j] != 0)
            {
                nb_etiq++;
                etiqList = (int*)realloc(etiqList, nb_etiq * sizeof(int));
                etiqList[nb_etiq - 1] = etiq[i][j];
            }
        }
    }
    printf("\n\n");
    
    nb = nb_etiq;
}

// 37 // Etiquettage des forme dans une image binaire(forme par forme)(pas pres)
void Etiquettage2(struct fichierimage* base, int** etiq, int& nb) {
    int y = base->entetebmp.hauteur;
    int x = base->entetebmp.largeur;
    int nb_etiq = 1;

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            etiq[i][j] = 0;
        }
    }

    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++)
        {
            if (etiq[i][j] == 0 && base->image[i][j].b == 255) {
                //initStack(pil);
                //push(pil, etiq[i][j]);
            }
        }
    }
}

// 38 // Faite le seuillage par histérésis avec la mathode Otsu
struct fichierimage* Hysteresis(struct fichierimage* base, float scal) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    float S_haut = Otsu(base);
    float S_bas = S_haut * scal;
    int fil[max2][2] = {0};
    int* temp;

    cree_f(fil);

    struct fichierimage* res = nouveau(x, y);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++) {
            if (base->image[i][j].b > S_haut && res->image[i][j].b == 0)
            {
                ajouter_f(fil, i, j);

                while (!vide_f(fil))
                {
                    temp = afffile_f(fil);
                    supp(fil);

                    res->image[temp[0]][temp[1]].b = 255;
                    res->image[temp[0]][temp[1]].r = 255;
                    res->image[temp[0]][temp[1]].g = 255;

                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = j - 1; l < j + 1; l++)
                        {
                            if (k >= 0 && k < x && l >= 0 && l < y)
                            {
                                if (base->image[k][l].b > S_bas && base->image[k][l].b <= S_haut && res->image[k][l].b == 0)
                                {
                                    ajouter_f(fil, k, l);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

// 39 // Application du filtre Prewitt
struct fichierimage* FiltrePrewitt(struct fichierimage* base) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);

    int sum;
    int sum2;

    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++) {
            sum = 0;
            for (int k = i - 1; k < i + 1; k++)
            {
                for (int l = j - 1; l < j + 1; l++)
                {
                    sum += base->image[k][l].b * PrewittX[k - i + 1][l - j + 1];
                }
            }
            sum2 = 0;
            for (int k = i - 1; k < i + 1; k++)
            {
                for (int l = j - 1; l < j + 1; l++)
                {
                    sum2 += base->image[k][l].b * PrewittY[k - i + 1][l - j + 1];
                }
            }/*
            res->image[i][j].b = sqrt(pow(sum, 2) + pow(sum2, 2));
            res->image[i][j].r = sqrt(pow(sum, 2) + pow(sum2, 2));
            res->image[i][j].g = sqrt(pow(sum, 2) + pow(sum2, 2));*/
            res->image[i][j].b = (sum + sum2) / 2;
            res->image[i][j].r = (sum + sum2) / 2;
            res->image[i][j].g = (sum + sum2) / 2;
        }
    }
    return res;
}

// 40 // Application du LaplacienBon
struct fichierimage* FiltreLaplacienBon(struct fichierimage* base ) {
    int x = base->entetebmp.largeur;
    int y = base->entetebmp.hauteur;
    struct fichierimage* res = nouveau(x, y);

    int sum;

    for (int i = 1; i < y - 1 ; i++) {
        for (int j = 1; j < x - 1 ; j++) {
            sum = 0;
            for (int k = i - 1; k < i + 1; k++)
            {
                for (int  l = j - 1; l < j + 1; l++)
                {
                    sum += base->image[k][l].b * Gradient[k - i + 1][l - j + 1];
                }
            }
            res->image[i][j].b = sum;
            res->image[i][j].g = sum;
            res->image[i][j].r = sum;
        }
    }
    return res;
}

// -1 // Affiche la liste de choix utilisable par l'utilisateur
void liste() {
    printf("\n");
    printf("Choix 1 : Mettre l'image en noir et blanc,\n");
    printf("Choix 2 : Mettre l'image en niveau de gris,\n");
    printf("Choix 3 : Reverser l'image (à 180°),\n");
    printf("Choix 4 : Mettre l'image en miroir par rapport à l'axe X,\n");
    printf("Choix 5 : Mettre l'image en miroir par rapport à l'axe Y,\n");
    printf("Choix 6 : Mettre l'image en symétrie par rapport à l'axe Y (Premier partie),\n");
    printf("Choix 7 : Mettre l'image en symétrie par rapport à l'axe Y (Deuxième partie),\n");
    printf("Choix 8 : Mettre l'image en symétrie par rapport à l'axe X (Premier partie),\n");
    printf("Choix 9 : Mettre l'image en symétrie par rapport à l'axe X (Deuxième partie),\n");
    printf("Choix 10 : Mettre l'image en symétrie par rapport aux axes X et Y (Premiere partie),\n");
    printf("Choix 11 : Mettre l'image en symétrie par rapport aux axes X et Y (Deuxieme partie),\n");
    printf("Choix 12 : Mettre l'image en symétrie par rapport aux axes X et Y (Troisieme partie),\n");
    printf("Choix 13 : Mettre l'image en symétrie par rapport aux axes X et Y (Quatrieme partie),\n");
    printf("Choix 14 : Mettre l'image en symétrie par rapport à la diagonal '\\' (Premier partie),\n");
    printf("Choix 15 : Mettre l'image en symétrie par rapport à la diagonal '\\' (Deuxième partie),\n");
    printf("Choix 16 : Mettre l'image en symétrie par rapport à la diagonal '/' (Premier partie),\n");
    printf("Choix 17 : Mettre l'image en symétrie par rapport à la diagonal '/' (Deuxième partie),\n");
    printf("Choix 18 : Pivoter l'image a 90° vers la gauche,\n");
    printf("Choix 19 : Pivoter l'image a 90° vers la droite,\n");
    printf("Choix 20 : Mettre l'image en négative,\n");
    printf("Choix 21 : Mettre l'image en monochrome rouge,\n");
    printf("Choix 22 : Mettre l'image en monochrome bleu,\n");
    printf("Choix 23 : Mettre l'image en monochrome vert,\n");
    printf("Choix 24 : Mettre l'image en monochrome magenta,\n");
    printf("Choix 25 : Mettre l'image en monochrome cyan,\n");
    printf("Choix 26 : Mettre l'image en monochrome jaune,\n");
    printf("Choix 27 : Agrandir l'image,\n");
    printf("Choix 28 : Reduire l'image,\n");
    printf("Choix 29 : Egaliser l'image,\n");
    printf("Choix 30 : Utiliser le filtre median,\n");
    printf("Choix 31 : Utiliser la convolution,\n");
    printf("Choix 32 : Incruster une image sur fond bleu dans un decor,\n");
    printf("Choix 33 : Incruster une image sur fond vert dans un decor,\n");
    printf("Choix 34 : Modifier la luminosité,\n");
    printf("Choix 35 : Faire la rotation avec un certain degres,\n");
    printf("Choix 36 : Utiliser le filtre laplacien,\n");
    printf("Choix 37 : Compter le nombre de forme et voir leurs compacité dans une image,\n");
    printf("Choix 38 : Seuillage par Histérésis,\n");
    printf("Choix 0 : Arréter le programme,\n");
    printf("Choix -1 : Afficher la liste,\n");
    printf("Choix -2 : Charger une image,\n");
    printf("Choix -3 : Afficher le resultat,\n");
    printf("Choix -4 : Ajouter une image,\n");
    printf("Choix -5 : Enregistrer sous ...,\n");
    printf("Choix -6 : Restaurer l'image original,\n");
    printf("Choix -7 : Liste des image chargeable,\n");
    printf("\n");
}

 // -7 // Afficher les image dans le ficher
void listeImage() {
    system("dir *.bmp | findstr /v resultat.bmp");
}