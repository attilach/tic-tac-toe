/************************************************
 * Nom : Estalella
 * Kevin : Kevin
 * Date: 20.11.2014
 * Version: 1.0
 * Titre: Morpion
 * Description: Jeux du morpion en mode console
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //permet d'utiliser le type boolean

/*
 * Titre: grilleValide
 *
 * Description: Regarde si la taille de la grille est valide
 *
 * Retour: Boolean. True si la taille est valide, false autrement
 */
bool grilleValide(int taille)
{
    const int min = 3;
    const int max = 25;

    // test que la taille soit comprise entre min et max
    if (taille >= min && taille <= max)
    {
        return true;
    }
    else
    {
        printf("\n\n!!! La taille de la grille doit etre comprise entre %d et %d", min, max);
        return false;
    }
}

/*
 * Titre: initialiserGrille
 *
 * Description: Initialise la grille du morpion
 * avec le symbole passé en paramètre
 *
 * Retour: Aucun
 */
void initialiserGrille(int taille, char grille[taille][taille], char symboleVide)
{
    int i, j;

    //rempli toute la grille avec le symbole vide
    for (i=0; i<taille; i++)
        for (j=0; j<taille; j++)
            grille[i][j] = symboleVide;
}

/*
 * Titre: affichageGrille
 *
 * Description: Affiche la grille du morpion
 *
 * Retour: Aucun
 */
void afficherGrille(int taille, char grille[taille][taille])
{
    printf("\n\n");

    int i, j;

    //affiche haut du cadre
    for (i=0; i<taille*3; i++)
        printf("-");

    putchar('\n');

    //affiche la grille du morpion
    for (i=0; i<taille; i++)
    {
        for (j=0; j<taille; j++)
        {
            printf(" %c ", grille[i][j]);
        }
        putchar('\n');
    }

    //affiche bas du cadre
    for (i=0; i<taille*3; i++)
        printf("-");
}

/*
 * Titre: estPleine
 *
 * Description: Parcours la grille pour voir si elle est pleine
 *
 * Retour: Boolean. True si la grille est pleine, false autrement
 */
bool estPleine(int taille, char grille[taille][taille], char symboleVide)
{
    int colonne, ligne = 0;

    // test toutes les cases de la grille pour savoir si elle est pleine
    for (ligne = 0; ligne < taille; ligne++)
    {
        for (colonne = 0; colonne < taille; colonne++)
        {
            // si une case est vide, le tableau n'est pas plein
            if (grille[ligne][colonne] == symboleVide)
            {
                return false;
            }
        }
    }

    // si aucune case est vide, le tableau est plein
    return true;
}

/*
 * Titre: occurLigne
 *
 * Description: Regarde le nombre d'occurence d'un symbole sur une ligne
 *
 * Retour: Entier (nombre d'occurence)
 */
int occurLigne(int taille, char grille[taille][taille], int ligne, int colonne)
{
    char symbole = grille[ligne][colonne];
    int compteur = 0;

    int j=0;
    for (j=0; j<taille; j++)
    {
        //test la ligne où le coup a été joué
        if (grille[ligne][j] == symbole)
        {
            compteur += 1;
        }
    }

    return compteur;
}

/*
 * Titre: occurColonne
 *
 * Description: Regarde le nombre d'occurence d'un symbole sur une colonne
 *
 * Retour: Entier (nombre d'occurence)
 */
int occurColonne(int taille, char grille[taille][taille], int ligne, int colonne)
{
    char symbole = grille[ligne][colonne];
    int compteur = 0;

    int i=0;
    for (i=0; i<taille; i++)
    {
        //test la colonne où le coup a été joué
        if (grille[i][colonne] == symbole)
        {
            compteur += 1;
        }
    }

    return compteur;
}

/*
 * Titre: occurDiagonaleA
 *
 * Description: Regarde le nombre d'occurence d'un symbole dans la premiere diagonale
 *
 * Retour: Entier (nombre d'occurence)
 */
int occurDiagonaleA(int taille, char grille[taille][taille], int ligne, int colonne)
{
    char symbole = grille[ligne][colonne];
    int compteur = 0;

    //test si le coup joué se trouve sur la première diagonale
    if (ligne == colonne)
    {
        int i=0;
        for (i=0; i<taille; i++)
        {
            //test la première diagonale où le coup a été joué
            if (grille[i][i] == symbole)
            {
                compteur += 1;
            }
        }
    }

    return compteur;
}

/*
 * Titre: occurDiagonaleB
 *
 * Description: Regarde le nombre d'occurence d'un symbole dans la deuxieme diagonale
 *
 * Retour: Entier (nombre d'occurence)
 */
int occurDiagonaleB(int taille, char grille[taille][taille], int ligne, int colonne)
{
    char symbole = grille[ligne][colonne];
    int compteur = 0;

    //test si le coup joué se trouve sur la deuxième diagonale
    if ((ligne + colonne) == taille-1)
    {
        int j=0;
        for (j=0; j<taille; j++)
        {
            //test la deuxième diagonale où le coup a été joué
            if (grille[taille-1-j][j] == symbole)
            {
                compteur += 1;
            }
        }
    }

    return compteur;
}

/*
 * Titre: gainPartie
 *
 * Description: Parcours la grille pour voir si il y a un gagnant
 *
 * Retour: Boolean. True si il y a un gagnant, false autrement
 */
bool gainPartie(int taille, char grille[taille][taille], int ligne, int colonne)
{
    // test la ligne pour voir si il y a un gagnant
    if (occurLigne(taille, grille, ligne, colonne) == taille)
        return true;

    // test la colonne pour voir si il y a un gagnant
    if (occurColonne(taille, grille, ligne, colonne) == taille)
        return true;

    // test la première diagonale pour voir si il y a un gagnant
    if (occurDiagonaleA(taille, grille, ligne, colonne) == taille)
        return true;

    // test la deuxième diagonale pour voir si il y a un gagnant
    if (occurDiagonaleB(taille, grille, ligne, colonne) == taille)
        return true;

    return false;
}

/*
 * Titre: coupValide
 *
 * Description: Test que les coordonnees fournies par l'utilisateur soient valide
 *
 * Retour: Boolean. True si les coordonnees sont valides, false autrement
 */
bool coupValide(int taille, char grille[taille][taille], int ligne, int colonne, char symboleVide)
{
    if (ligne>0 && ligne<=taille && colonne>0 && colonne<=taille && grille[ligne-1][colonne-1] == symboleVide)
    {
        return true;
    }
    else
    {
        printf("\n\n!!! Les coordonnees saisies doivent etre comprise entre 1 et %d et ne pas indiquer une case deja occupee", taille);
        return false;
    }
}


/*
 * Titre: coupOrdi
 *
 * Description: Parcours le tableau afin de voir où l'ordinateur peut jouer et empêcher le joueur de gagner de manière evidente
 *
 * Retour: Aucun
 */
void coupOrdi(int taille, char grille[taille][taille], int ligne, int colonne, char symboleVide, char symboleOrdinateur, int coordOrdi[2])
{
    ligne=ligne-1;
    colonne=colonne-1;

    if (occurLigne(taille, grille, ligne, colonne) == taille-1)
    {
        //bloque ligne pour empêcher joueur de gagner
        int j=0;
        for (j=0; j<taille; j++)
        {
            if (grille[ligne][j] == symboleVide)
            {
                grille[ligne][j] = symboleOrdinateur;
                printf("\n\nOrdinateur a joue");
                coordOrdi[0] = ligne;
                coordOrdi[1] = j;
                return 0;
            }
        }
    }

    if (occurColonne(taille, grille, ligne, colonne) == taille-1)
    {
        //bloque colonne pour empêcher joueur de gagner
        int i=0;
        for (i=0; i<taille; i++)
        {
            if (grille[i][colonne] == symboleVide)
            {
                grille[i][colonne] = symboleOrdinateur;
                printf("\n\nOrdinateur a joue");
                coordOrdi[0] = i;
                coordOrdi[1] = colonne;
                return 0;
            }
        }
    }

    if (occurDiagonaleA(taille, grille, ligne, colonne) == taille-1)
    {
        //test si le coup joué se trouve sur la première diagonale
        if (ligne == colonne)
        {
            //bloque la première diagonale où le coup a été joué
            int i=0;
            for (i=0; i<taille; i++)
            {
                if (grille[i][i] == symboleVide)
                {
                    grille[i][i] = symboleOrdinateur;
                    printf("\n\nOrdinateur a joue");
                    coordOrdi[0] = i;
                    coordOrdi[1] = i;
                    return 0;
                }
            }
        }
    }

    if (occurDiagonaleB(taille, grille, ligne, colonne) == taille-1)
    {
        //test si le coup joué se trouve sur la deuxième diagonale
        if ((ligne + colonne) == taille-1)
        {
            //bloque la deuxième diagonale où le coup a été joué
            int j=0;
            for (j=0; j<taille; j++)
            {
                if (grille[taille-1-j][j] == symboleVide)
                {
                    grille[taille-1-j][j] = symboleOrdinateur;
                    printf("\n\nOrdinateur a joue");
                    coordOrdi[0] = taille-1-j;
                    coordOrdi[1] = j;
                    return 0;
                }
            }
        }
    }

    // On test toutes les cases de la grille pour trouver une case vide
    int i=0;
    for (i = 0; i < taille; i++) {
        int j=0;
        for (j = 0; j < taille; j++) {
            if (grille[i][j] == symboleVide) {
                grille[i][j] = symboleOrdinateur;
                printf("\n\nOrdinateur a joue");
                coordOrdi[0] = i;
                coordOrdi[1] = j;
                return 0;
            }
        }
    }
}

int main()
{
    // initialise les différents symbole utilisés
    const char symboleJoueur = 'X';
    const char symboleOrdinateur = 'O';

    const char symboleVide = '-';

    int taille, ligne, colonne;

    // Coordonnées où l'ordinateur joue
    int coordOrdi[2];

    printf("JEUX DU MORPION");
    printf("\n---------------");


    do {
        printf("\n\nChoisissez la taille de la grille: ");

        scanf("%d", &taille);

    } while(grilleValide(taille) != true);  //test que la grille soit valide


    char grille[taille][taille];

    //rempli la grille avec le symbole vide
    initialiserGrille(taille, grille, symboleVide);

    printf("\n\nVous etes le symbole %c", symboleJoueur);

    afficherGrille(taille, grille);

    do {
        do {
            printf("\n\n\n\nA vous de jouer!");

            printf("\n\n\nChoisissez une ligne: ");
            scanf("%d", &ligne);

            printf("\nChoisissez une colonne: ");
            scanf("%d", &colonne);

        } while(coupValide(taille, grille, ligne, colonne, symboleVide) != true); // test si le joueur a joué une position valide

        //place le symbole du joueur dans la grille
        grille[ligne-1][colonne-1] = symboleJoueur;

        afficherGrille(taille, grille);

        //test si le joueur a gagné la partie
        if (gainPartie(taille, grille, ligne-1, colonne-1))
        {
            printf("\n\nJoueur gagne!\n\n");
            return 0;
        }

        // l'ordinateur joue son coup
        coupOrdi(taille, grille, ligne, colonne, symboleVide, symboleOrdinateur, coordOrdi);

        afficherGrille(taille, grille);

        // test si l'ordinateur a gagné la partie
        if (gainPartie(taille, grille, coordOrdi[0], coordOrdi[1]))
        {
            printf("\n\nOrdinateur gagne!\n\n");
            return 0;
        }

    } while (estPleine(taille, grille, symboleVide) == false); // tant que la grille n'est pas pleine on ne sort pas de la boucle

    printf("\n\nJoueur et Ordinateur sont egalite!\n\n");

    return 0;
}
