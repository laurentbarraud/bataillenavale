//*** Jeu de bataille navale, réalisé pour le cours de MA-20 - Application du C, au CPNV. ***
//*** Laurent Barraud - classe SI-CA1a - 30-01-2019 *****************************************
//*** Révisé le 23-02-2025
//*** version 1.1 ***************************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define VALEUR_INIT -1

const char separateur[] = "******************************************************************\n";
// mode debug, caché à l'utilisateur :
// si activé, affiche la deuxième grille où sont encodés les bateaux
int modeDebug = 0;

// plateau de jeu pour l'utilisateur
char tabJeu[10][10];

// plateau où sont encodés les bateaux, affiché seulement en mode debug.
char tabBateaux[10][10];

char prenom[50] = "\0";

// prenom d'un joueur qui a récemment joué, chargé depuis le fichier joueurs.txt
char joueurCharge[16] = "\0";

// score d'un joueur récent, chargé depuis le fichier scores.txt
int scoreCharge = VALEUR_INIT;

// prenom d'un joueur qui a récemment joué, avec un séparateur (:) et son score, chargé depuis le fichier scores.txt
char joueurScoreCharge[20] = "\0";

// horloge
clock_t startTime, endTime;
double tempsEcoule;

char evenement[100] = "\0";

// --- déclaration des fonctions utilisées dans le programme ---
// -------------------------------------------------------------

// nombre de coups joués par l'utilisateur
int nbCoupsJoues = VALEUR_INIT;

// score final de la partie
int scoreFinal = VALEUR_INIT;

// détermine la fin de la partie
int tousBateauxCoules = VALEUR_INIT;

// fonction intégrée à windows.h : déplace le curseur à la position indiquée en coordonnées
// source: https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044844545&id=1043284392
void Gotoxy(int x, int y);

// affiche le menu principal
int menu();

// lance une nouvelle partie
void jouer();

// fonction d'authentification
void login();

// fonction d'authentification avec choix d'un numéro, parmi la liste des derniers joueurs
void loginNumerote();

// charge un joueur depuis le fichier joueurs.txt
void chargerJoueur(int ligne);

// enregistre le joueur sélectionné dans le fichier joueurs.txt
void enregistrerJoueur();

// efface la première ligne dans le fichier joueurs.txt s'il contient 5 lignes
void effacerPremierJoueur();

// remplit la grille de jeu sur lequel l'utilisateur va jouer de "."
void remplirTableauJeu();

// charge à partir d'un fichier grille.txt la position des bateaux et la code sur l'autre grille, cachée au joueur
void chargerTableauBateaux();

// affiche le tableau entrée en argument (adaptation d'un code venant du site Openclassrooms)
void afficherTableau(char tabAffiche[10][10]);

// affiche +-- autant de fois qu'il y a de colonnes
void afficherBarbele(int n);

// vérifie sur la grille où ont été encodés les bateaux s'il y en a un aux coordonnées saisies par l'utilisateur
// et indique lequel a été touché ou coulé
void tirerCoup(int colonneViseeNombre, int ligneVisee);

// choix de la colonne visée au prochain coup
int choixColonne();

// choix de la ligne visée au prochain coup
int choixLigne();

// renvoie le nombre de cases restantes à couler d'un bateau donné,
// dont le type peut être un nombre entier de 1 à 5. Renvoie 0 si le bateau est coulé.
int statutBateau(int typeBateau);

// affiche le score de la partie
void afficherScoreFinal();

// enregistre le score final dans un fichier scores.txt
void enregistrerScoreFinal();

// affiche la liste des meilleurs scores
void afficherScores();

// enregistre le score de l'utilisateur avec son prénom dans un fichier scores.txt
void enregistrerScoreFinal();

// affiche l'aide du jeu
void menuAide();

// enregistre dans un fichier log chaque événement depuis le lancement du programme
void logEvent(char evenement[100]);

// change la couleur du texte (x) et la couleur de fond (y) à l'endroit où on l'appelle
// source : https://openclassrooms.com/forum/sujet/couleur-dans-la-console-en-c-63227
void color(int t,int f);



int main()
{

    //efface la console
    system("cls");

    color(8,0);
    Gotoxy(10,1); printf("%s",separateur);
    color(15,1);
    Gotoxy(10,2); printf(" ____        _        _ _ _                               _       ");
    Gotoxy(10,3); printf("|  _ \\      | |      (_) | |                             | |      ");
    Gotoxy(10,4); printf("| |_) | __ _| |_ __ _ _| | | ___   _ __    __ __   __ __ | | ___  ");
    Gotoxy(10,5); printf("|  _ < / _` | __/ _` | | | |/ _ \\ | '_ \\ / _ `\\ \\ / / _ `| |/ _ \\ ");
    Gotoxy(10,6); printf("| |_) | (_| | |  (_| | | | |  __/ | | | | (_| |\\   / (_| | |  __/ ");
    Gotoxy(10,7); printf("|____/ \\__,_|\\__\\_,_ |_| | |\\__ | |_| |_|\\__,_| \\_/ \\__,_|_|\\____ ");
    Gotoxy(10,8); printf("                                                                  ");
    color(8,0);
    Gotoxy(10,10); printf("%s",separateur);
    color(7,0);

    logEvent("[système] - Page de titre chargée");
    menu();

    return EXIT_SUCCESS;
}



void Gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu()
{
    char choix = '\0';
    int entreeValide = VALEUR_INIT;

    Gotoxy(35,14); printf("Jouer        [j]");
    Gotoxy(35,16); printf("Aide         [a]");
    Gotoxy(35,18); printf("Scores       [s]");
    Gotoxy(35,20); printf("Quitter      [q]");

    logEvent("[système] - Menu chargé");

        do {
            Gotoxy(28,25); printf("Entrez votre choix : ");
            fflush(stdin);
            scanf("%c", &choix);
            entreeValide = 1;

            // effectue le choix du menu principal
            switch(choix)
            {
                case 'j' :
                case 'J' :

                    logEvent("[système] - nouvelle partie démarrée");
                    // efface la console
                    system("cls");
                    // lance une partie
                    jouer();
                break;

                case 'a' :
                case 'A' :
                    logEvent("[système] - écran d'aide démarré");
                    system("cls");
                    // affiche le menu d'aide
                    menuAide();
                break;

                case 's' :
                case 'S' :
                    logEvent("[système] - écran des meilleurs scores démarré");
                    system("cls");
                    // affiche le menu des meilleurs scores
                    afficherScores();
                break;

                case 'q' :
                case 'Q' :
                    logEvent("[système] - programme quitté par l'utilisateur");
                    system("cls");
                    Gotoxy(10,8); printf("Au revoir !");
                    Gotoxy(10,15);
                    exit(EXIT_SUCCESS);
                break;

                case 'd' :
                case 'D' :
                    logEvent("[système] - mode debug activé");
                    modeDebug = 1;
                    Gotoxy(28,28); color(3,0); printf("== Mode debug active =="); color(7,0);
                    entreeValide = 0;
                break;

            default: entreeValide = 0;
         }

        } while (entreeValide == 0);

        return 0;
}

void jouer()
{
    int colonneVisee = VALEUR_INIT;
    int ligneVisee = VALEUR_INIT;
    double tempsEcoule = 0.0;
    int tempsEcouleArrondi = VALEUR_INIT;
    int tempsRestant = VALEUR_INIT;

    system("cls");

    // appelle la fonction d'authentification
    logEvent("[système] - écran d'authentification démarré");
    login();

    // enregistre le prénom, s'il est valide, dans le fichier joueurs.txt
    logEvent("[sauvegarde] - enregistrement du prénom choisi dans joueurs.txt");
    enregistrerJoueur();

    // efface le premier prénom de la liste joueurs.txt, s'il y en a déjà cinq
    logEvent("[sauvegarde] - décalage de la liste des prénoms vers le haut, effacement du premier");
    effacerPremierJoueur();

    system("cls");
    logEvent("[système] - rappel du temps alloué avant de démarrer la partie");
    Gotoxy(10,9); printf("Bienvenue a bord, %s", prenom);
    Gotoxy(10,15); printf("Vous avez "); color(14,0); printf("7 minutes"); color(7,0); printf(" pour couler tous les bateaux.");
    Gotoxy(10,17); printf("Tapez une touche pour commencer. Bonne partie. ");

    // attente d'appui sur une touche
    fflush(stdin);
    getchar();

    // commence à calculer le temps de la partie, s'il arrive à zéro c'est perdu !
    // start est de type prédéfini clock_t (long)
    logEvent("[système] - démarrage du compte à rebours avec 10 minutes");
    startTime = clock();
    scoreFinal = 420;

    logEvent("[système] - remplissage du tableau de jeu de points");
    remplirTableauJeu();

    logEvent("[système] - chargement de la grille de jeu au hasard parmi un pool de 20 grilles");
    chargerTableauBateaux();

    logEvent("[système] - tous les bateaux sont actifs");
    tousBateauxCoules = 0;
    logEvent("[sauvegarde] - le nombre de coups joués est de 0");
    nbCoupsJoues = 0;

        // gameloop : s'arrête quand tous les bateaux auront été coulés où que le temps est écoulé
        do {

            // calcule le temps qui a été écoulé, end est de type prédéfini clock_t (long)
            endTime = clock();
            tempsEcoule = ( (double)(endTime - startTime) ) /CLOCKS_PER_SEC;  // on divise par la constante pour avoir la valeur en secondes
            tempsEcouleArrondi = ceil(tempsEcoule);                           // arrondi à la valeur supérieure
            tempsRestant = 600 - tempsEcouleArrondi;                        // on dispose de 10 minutes au maximum pour finir le jeu

                if (tempsRestant <= 0)
                {
                    // interrompt la partie et affiche le score final
                    logEvent("[système] - Game over : temps écoulé");
                    afficherScoreFinal();
                }

            //efface la console
            system("cls");

            afficherTableau(tabJeu);

                if (modeDebug == 1)
                {
                    afficherTableau(tabBateaux);
                }

            // choix d'une colonne à viser pour le prochain coup
            logEvent("[système] - choix de coordonnées pour le prochain coup");
            colonneVisee = choixColonne();

            // choix d'une ligne à viser pour le prochain coup
            ligneVisee = choixLigne();

            // vérifie sur la grille où ont été encodés les bateaux s'il y en a un aux coordonnées saisies par l'utilisateur
            // et indique lequel a été touché ou coulé
            tirerCoup(colonneVisee,ligneVisee);

                // vérifie si tous les bateaux ont été coulés
                if (statutBateau(1) == 0 && statutBateau(2) == 0 && statutBateau(3) == 0 && statutBateau(4) == 0 && statutBateau(5) == 0)
                {
                  logEvent("[système] - tous les bateaux ont été coulés");
                  tousBateauxCoules = 1;
                }

            // attente d'appui sur une touche
            fflush(stdin);
            getchar();

        } while (tousBateauxCoules == 0);

    system("cls");

    // affiche le score de la partie
    logEvent("[système] - fin de partie, affichage du score final");
    afficherScoreFinal();
}

void login()
{
    int entreeValide = VALEUR_INIT;
    int longueurPrenom = VALEUR_INIT;
    int i = VALEUR_INIT;

        // demande d'authentification
        do {
            system("cls");

            Gotoxy(10,9); printf("Veuillez entrer votre prenom");
            Gotoxy(10,11); printf("(uniquement des lettres, maximum 15).");
            Gotoxy(10,14); printf("Tapez une seule lettre pour ouvrir la liste des joueurs recents : ");

            // récupère la saisie de l'utilisateur
            fflush(stdin);
            scanf("%s", prenom);
            longueurPrenom = strlen(prenom);

                // si l'utilisateur a entré un seul caractère
                if (longueurPrenom < 2)
                {
                    entreeValide = 1;

                    // appelle l'authentification avec choix parmi la liste des cinq derniers joueurs
                    logEvent("[système] - écran d'authentification avec choix parmi la liste des derniers joueurs");
                    loginNumerote();

                } else if (longueurPrenom >= 2 && longueurPrenom <= 15)
                {

                    // vérification que l'utilisateur n'a pas entré de chiffres dans son prénom
                    for (i=0; i<longueurPrenom; i++)
                    {
                        if (prenom[i] >= 48 && prenom[i] <= 57)
                        {
                            entreeValide = 0;
                            Gotoxy(10,20); printf("Erreur, vous avez entre des chiffres ! Veuillez resaisir svp.");

                            // attente d'appui sur une touche
                            fflush(stdin);
                            getchar();
                        } else
                        {
                            entreeValide = 1;

                        }
                    }


                } else
                {
                    entreeValide = 0;
                    Gotoxy(10,20); printf("Erreur, prenom trop long ! Veuillez resaisir svp.");

                    // attente d'appui sur une touche
                    fflush(stdin);
                    getchar();
                }

        // répète la demande tant que l'entrée n'est pas valide
        } while (entreeValide == 0);

}

void loginNumerote()
{
    int entreeValide = VALEUR_INIT;
    int choix = VALEUR_INIT;

    system("cls");
    Gotoxy(10,3); printf("Liste des cinq derniers joueurs : ");
    Gotoxy(10,5); printf("%s",separateur);

    // lecture de la première ligne de joueurs.txt
    logEvent("[chargement] - dernier joueur numéro 1");
    chargerJoueur(1);
    Gotoxy(10,7); printf("(1)  %s",joueurCharge);

    // lecture de la deuxième ligne de joueurs.txt
    logEvent("[chargement] - dernier joueur numéro 2");
    chargerJoueur(2);
    Gotoxy(10,9); printf("(2)  %s",joueurCharge);

    logEvent("[chargement] - dernier joueur numéro 3");
    chargerJoueur(3);
    Gotoxy(10,11); printf("(3)  %s",joueurCharge);

    logEvent("[chargement] - dernier joueur numéro 4");
    chargerJoueur(4);
    Gotoxy(10,13); printf("(4)  %s",joueurCharge);

    logEvent("[chargement] - dernier joueur numéro 5");
    chargerJoueur(5);
    Gotoxy(10,15); printf("(5)  %s",joueurCharge);

    Gotoxy(10,19);
    printf("(0)  <annuler>");

    Gotoxy(10,21);
    printf("Veuillez taper un numero : ");

        // choix de l'utilisateur
        do {

            fflush(stdin);
            scanf("%i", &choix);

            switch (choix)
            {
                case 0:
                    entreeValide = 1;

                    logEvent("[système] - Page de titre chargée");
                    // retourne au menu principal
                    main();
                break;

                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    entreeValide = 1;

                    logEvent("[chargement] - un des derniers joueurs a été choisi");
                    // recharge le joueur choisi en mémoire
                    chargerJoueur(choix);

                    // copie le joueur chargé dans la variable globale prénom
                    strcpy(prenom, joueurCharge);
                break;

                default:
                    entreeValide = 0;

                    Gotoxy(10,23); printf("Erreur, numero non-reconnu. Veuillez resaisir svp : ");
                break;
            }

        } while (entreeValide == 0);

}

void chargerJoueur(int ligne)
{
    char listeVide[16] = "Liste vide.";

    // numéro de ligne du fichier
    int nbLignes = 0;

    // pointeur sur le fichier
    FILE *fichier = NULL;

    // ouverture du fichier en mode lecture seule
    fichier = fopen("joueurs.txt", "r");

        // si le fichier n'existe pas
        if(fichier == NULL)
        {
            // copie la valeur de la chaîne vide dans celle du joueur chargé
            strcpy(joueurCharge, listeVide);

        } else
        {

            // lecture de chaque ligne
            do {
                fgets(joueurCharge, 16, fichier);
                nbLignes++;
            } while(nbLignes < ligne);

        }

    // fermeture du fichier
    fclose (fichier);

}

void enregistrerJoueur()
{

    // pointeur sur le fichier
    FILE *fichier = NULL;

    // ouverture du premier fichier en mode lecture et écriture depuis le début
    fichier = fopen("joueurs.txt ", "a+");

    // appende une ligne supplémentaire, contenant le joueur sélectionné pour jouer
    fprintf(fichier, "\n%s", prenom);

    // fermeture du fichier
    fclose (fichier);

}

void effacerPremierJoueur()
{
    // numéro de ligne du fichier
    int nbLignes = VALEUR_INIT;

    // pointeurs sur les fichiers
    FILE *fichier = NULL;
    FILE *fichier2 = NULL;

    // ouverture du premier fichier en lecture et écriture par le début.
    fichier = fopen("joueurs.txt", "a+");

    // ouverture du deuxième fichier en lecture et écriture par le début.
    fichier2 = fopen("joueurs2.txt", "a+");

    nbLignes = 1;

        // copie toutes les lignes de joueurs.txt, sauf la première, dans joueurs2.txt
        do {

            // lecture de 16 caractères maximum sur chaque ligne de joueurs.txt et stockage dans joueurCharge
            fgets(joueurCharge, 16, fichier);

                // pour chaque ligne, après la première
                if (nbLignes > 1)
                {
                    // écriture du joueur dans joueurs2.txt
                    fprintf(fichier2, "%s", joueurCharge);
                }

            nbLignes++;

            // le fichier ne fait pas plus que 6 lignes
        } while(nbLignes < 7);



    // fermeture des deux fichiers
    fclose(fichier);
    fclose(fichier2);


    // ouverture du fichier joueur2.txt en mode lecture seule
    fichier2 = fopen("joueurs2.txt", "r");

    // ouverture du fichier joueurs.txt en mode lecture et écriture, avec effacement préalable du contenu.
    fichier = fopen("joueurs.txt", "w");

    nbLignes = 1;

        do {

            // lecture de 16 caractères maximum sur chaque ligne de joueurs2.txt et copie dans joueurCharge
            fgets(joueurCharge, 16, fichier2);

            // écriture du joueur dans joueurs.txt
            fprintf(fichier, "%s", joueurCharge);

            nbLignes++;

        // le fichier ne fait pas plus que 5 lignes
        } while(nbLignes < 6);



    // fermeture du fichier
    fclose (fichier);

}


void remplirTableauJeu()
{
    int i, j;
       for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                tabJeu[i][j] = '.';
            }
        }
}

// charge une des grilles de jeu, si elles se trouvent dans le même répertoire
void chargerTableauBateaux()
{
    char caractere = ' ';
    int i = VALEUR_INIT;
    int j = VALEUR_INIT;
    char ligneChargee[12] = " ";                // ligne chargée depuis le fichier de grille
    int aleatoire = VALEUR_INIT;
    char aleatoireCharTemp[12] = " ";            // variable temporaire, stocke la valeur de aleatoire convertie en tableau de char
    char aleatoireChar[12] = " ";              // valeur de type tableau de char, récupérant le nombre aleatoire
    char pathGrille[23] = " ";                 // contient le chemin d'accès vers le fichier de grille

    // copie la chaîne "grille" dans toute la chaîne pathGrille
    strcpy(pathGrille, "./grilles/grille");

    // initialise le générateur de nombre aléatoire, puis génère un nombre au hasard, compris entre 1 et 20.
    srand(time(NULL));
    aleatoire = rand()%20 + 1;
    logEvent("[système] - une grille a été choisie au hasard parmi celles disponibles");

    // conversion de la valeur int aleatoire en char et écriture dans toute la chaîne aleatoireChar
    snprintf(aleatoireChar, 12, "%i", aleatoire);

        if (aleatoire >= 1 && aleatoire <= 9)
        {
            // copie tout le contenu de la chaîne dans une deuxième
            strcpy(aleatoireCharTemp, aleatoireChar);

            // remplace la valeur de aleatoireChar par zéro, pour avoir grille01, grille02, etc...
            strcpy(aleatoireChar, "0");

            // append du contenu de la deuxième chaîne dans la première
            strcat(aleatoireChar, aleatoireCharTemp);
        }

    // append la valeur de chaîne de aleatoireChar à la fin de la chaîne pathGrille.
    // pathGrille vaut maintenant "grille(+un nombre à 2 chiffres)"
    strcat(pathGrille, aleatoireChar);

    // append l'extension à la fin de la chaîne pathGrille
    strcat(pathGrille, ".txt");

        // contrôle que la lecture se fait correctement, uniquement affiché en mode debug.
        if (modeDebug == 1)
        {
            logEvent("[debug] - une grille a été choisie");
            printf("\n\n\nVous jouez avec : %s", pathGrille);

            printf("\n\n\nTapez une touche pour continuer. ");
            fflush(stdin);
            getchar();
        }

    // pointeur sur le fichier
    FILE *fichierGrille = NULL;

    //ouverture du fichier en mode lecture seule
    fichierGrille = fopen(pathGrille, "r");

        // teste si le fichier existe
        if(fichierGrille == NULL)
        {
            logEvent("[système] - aucune grille n'a pu être chargée");
            printf("\n\nDésolé, aucune grille n'a pu être chargée !\n");

        } else
        {

            // parcours de tabBateaux, on commence à la première ligne
            for (i=0; i<10; i++)
            {
                // lit chaque ligne de la grille jusqu'à douze caractères ou un retour à la ligne
                fgets(ligneChargee, 12, fichierGrille);

                        for (j=0; j<10; j++)
                        {
                            // lecture d'un caractere i de ligneChargee
                            caractere = ligneChargee[j];
                            tabBateaux[i][j] = caractere;

                        }

            }

        // fermeture du fichier
        fclose (fichierGrille);
        }
}


void afficherTableau(char tabAffiche[10][10])
{
  int i, j;
  printf("\n");

  // affiche les lettres des colonnes, précédées de 7 espaces et séparées chacune de 3.
  printf("       A   B   C   D   E   F   G   H   I   J\n\n");

    for (i = 0; i < 10; i++)
    {
        // décale de 5 espaces
        printf("     ");

        // affiche +-- autant de fois qu'il y a de colonnes
        afficherBarbele(10);

            // s'il s'agit des lignes 1 à 9
            if (i < 10-1)
            {
                // affiche les numéros de ligne avec 2 espaces avant et 2 espaces après, incrémentés de 1
                printf("  %i  ",i+1);

            // à partir de la 10ème ligne
            } else {

                // affiche le numéro de ligne avec 2 espace avant et seulement 1 espace après, incrémenté de 1
                printf("  %i ",i+1);
            }

                for (j = 0; j < 10; j++)
                {
                    // affiche la valeur du tableau, précédée du caractère "|" et de 2 espaces
                    if (tabAffiche[i][j] == 'X')
                    {
                        // blanc sur fond rouge
                        color(15,12);
                        printf("|%2c ", tabAffiche[i][j]);
                        color(7,0);

                    } else if (tabAffiche[i][j] == 'O')
                    {
                        // blanc sur fond bleu foncéew
                        color(15,3);
                        printf("|%2c ", tabAffiche[i][j]);
                        color(7,0);

                    } else if (tabAffiche[i][j] == '.')
                    {
                        // blanc sur fond bleu foncéew
                        color(15,3);
                        printf("|%2c ", tabAffiche[i][j]);
                        color(7,0);

                    } else if (tabAffiche[i][j] == '1' || tabAffiche[i][j] == '2' || tabAffiche[i][j] == '3' || tabAffiche[i][j] == '4' || tabAffiche[i][j] == '5')
                    {
                        // blanc sur fond bleu foncéew
                        color(14,0);
                        printf("|%2c ", tabAffiche[i][j]);
                        color(7,0);

                    } else
                    {
                        printf("|%2c ", tabAffiche[i][j]);
                    }


                }

        // ferme la ligne par un "|", puis passe à la ligne suivante
        printf("|\n");

    }

    // décale de 5 espaces
    printf("     ");

    // affiche +-- autant de fois qu'il y a de colonnes
    afficherBarbele(10);
}

void afficherBarbele(int n)
{
    int i;


        for (i = 0; i < n; i++)
        {
            printf("+---");
        }

    printf("+\n");
}

void tirerCoup(int colonneViseeNombre, int ligneVisee)
{
    int nbCasesBateauIntactes = VALEUR_INIT;
    char colonneVisee = ' ';

        // conversion de int en char pour l'affichage de la coordonnée visée
        switch (colonneViseeNombre)
        {
            case 0:
                colonneVisee = 'A';
            break;

            case 1:
                colonneVisee = 'B';
            break;

            case 2:
                colonneVisee = 'C';
            break;

            case 3:
                colonneVisee = 'D';
            break;

            case 4:
                colonneVisee = 'E';
            break;

            case 5:
                colonneVisee = 'F';
            break;

            case 6:
                colonneVisee = 'G';
            break;

            case 7:
                colonneVisee = 'H';
            break;

            case 8:
                colonneVisee = 'I';
            break;

            case 9:
                colonneVisee = 'J';
            break;

        }

    printf("\nEnvoi d'un missile en %c%i ................. ",colonneVisee, ligneVisee + 1);

        nbCoupsJoues++;

        switch (tabBateaux[ligneVisee][colonneViseeNombre])
        {

            case '1':

                    // marque d'une croix les coordonnées visées sur les deux grilles de jeu
                    tabBateaux[ligneVisee][colonneViseeNombre] = 'X';
                    tabJeu[ligneVisee][colonneViseeNombre] = 'X';


                    // calcule le nombre de cases du bateau restant à couler
                    nbCasesBateauIntactes = statutBateau(1);

                        if (nbCasesBateauIntactes >= 1)
                        {
                            logEvent("[système] - Porte-avion touché");
                            color(15,12);
                            printf("Porte-avion touche !");
                            color(7,0);
                        } else
                        {
                            logEvent("[système] - Porte-avion coulé");
                            color(15,12);
                            printf("Porte-avion coule !");
                            color(7,0);
                        }

            break;

            case '2':


                    tabBateaux[ligneVisee][colonneViseeNombre] = 'X';
                    tabJeu[ligneVisee][colonneViseeNombre] = 'X';


                    nbCasesBateauIntactes = statutBateau(2);

                        if (nbCasesBateauIntactes >= 1)
                        {
                            logEvent("[système] - Croiseur touché");
                            color(15,12);
                            printf("Croiseur touche !");
                            color(7,0);
                        } else
                        {
                            logEvent("[système] - Croiseur coulé");
                            color(15,12);
                            printf("Croiseur coule !");
                            color(7,0);
                        }

            break;

            case '3':

                    tabBateaux[ligneVisee][colonneViseeNombre] = 'X';
                    tabJeu[ligneVisee][colonneViseeNombre] = 'X';


                    nbCasesBateauIntactes = statutBateau(3);

                        if (nbCasesBateauIntactes >= 1)
                        {
                            logEvent("[système] - Contre-torpilleur touché");
                            color(15,12);
                            printf("Contre-torpilleur touche !");
                            color(7,0);
                        } else
                        {
                            logEvent("[système] - Contre-torpilleur coulé");
                            color(15,12);
                            printf("Contre-torpilleur coule !");
                            color(7,0);
                        }

            break;

            case '4':

                    tabBateaux[ligneVisee][colonneViseeNombre] = 'X';
                    tabJeu[ligneVisee][colonneViseeNombre] = 'X';


                    nbCasesBateauIntactes = statutBateau(4);

                        if (nbCasesBateauIntactes >= 1)
                        {
                            logEvent("[système] - Sous-marin touché");
                            color(15,12);
                            printf("Sous-marin touche !");
                            color(7,0);
                        } else
                        {
                            logEvent("[système] - Sous-marin coulé");
                            color(15,12);
                            printf("Sous-marin coule !");
                            color(7,0);
                        }

            break;

            case '5':

                    tabBateaux[ligneVisee][colonneViseeNombre] = 'X';
                    tabJeu[ligneVisee][colonneViseeNombre] = 'X';


                    nbCasesBateauIntactes = statutBateau(5);

                        if (nbCasesBateauIntactes >= 1)
                        {
                            logEvent("[système] - Torpilleur touché");
                            color(15,12);
                            printf("Torpilleur touche !");
                            color(7,0);
                        } else
                        {
                            logEvent("[système] - Torpilleur coulé");
                            color(15,12);
                            printf("Torpilleur coule !");
                            color(7,0);
                        }
            break;

            case 'X':
            case 'O':
                printf("Vous avez deja tire dans cette case !");
            break;

            default :

                // marque d'un rond les coordonnées visées sur les deux grilles de jeu
                tabBateaux[ligneVisee][colonneViseeNombre] = 'O';
                tabJeu[ligneVisee][colonneViseeNombre] = 'O';

                color(15,3);
                printf("Coup dans l'eau.");
                color(7,0);
        }
}

int choixColonne()
{

    int entreeValide = VALEUR_INIT;
    char colonneVisee = ' ';
    int colonneViseeNombre = VALEUR_INIT;

        do {
            printf("\n Veuillez entrer la lettre de la colonne visee : ");
            fflush(stdin);
            scanf("%c", &colonneVisee);

                switch (colonneVisee){
                    case 'A':
                    case 'a':
                        entreeValide = 1;
                        colonneViseeNombre = 0;
                    break;

                    case 'B':
                    case 'b':
                        entreeValide = 1;
                        colonneViseeNombre = 1;
                    break;

                    case 'C':
                    case 'c':
                        entreeValide = 1;
                        colonneViseeNombre = 2;
                    break;

                    case 'D':
                    case 'd':
                        entreeValide = 1;
                        colonneViseeNombre = 3;
                    break;

                    case 'E':
                    case 'e':
                        entreeValide = 1;
                        colonneViseeNombre = 4;
                    break;

                    case 'F':
                    case 'f':
                        entreeValide = 1;
                        colonneViseeNombre = 5;
                    break;

                    case 'G':
                    case 'g':
                        entreeValide = 1;
                        colonneViseeNombre = 6;
                    break;

                    case 'H':
                    case 'h':
                        entreeValide = 1;
                        colonneViseeNombre = 7;
                    break;

                    case 'I':
                    case 'i':
                        entreeValide = 1;
                        colonneViseeNombre = 8;
                    break;

                    case 'J':
                    case 'j':
                        entreeValide = 1;
                        colonneViseeNombre = 9;
                    break;

                    default: entreeValide = 0;
                        printf("\nLettre incorrecte, veuillez reessayer.\n");
                    }

            } while (entreeValide == 0);


    return colonneViseeNombre;

}

int choixLigne()
{

    int entreeValide = 0;
    int ligneVisee = VALEUR_INIT;

        do {
            printf("\n Veuillez entrer le chiffre de la ligne visee : ");
            fflush(stdin);
            scanf("%i", &ligneVisee);

            if (ligneVisee >= 1 && ligneVisee <= 10) {
                entreeValide = 1;
                ligneVisee--;
            } else {
                entreeValide = 0;
                printf("\nChiffre incorrect, veuillez reessayer.\n");
            }

        } while (entreeValide == 0);

    return ligneVisee;

}

int statutBateau(int typeBateau)
{
    int nbCasesBateauIntactes = 0;
    int valeurTableau = 0;
    int i, j;

        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                // convertit en assignant la valeur char de tabBateaux à une variable int
                valeurTableau = tabBateaux[i][j];

                     // si la valeur du tableau est égale au type de bateau entré en argument (1 à 5)
                    if (valeurTableau == (typeBateau))
                    {
                        // on ajoute un à la variable qui compte les cases restantes du bateau
                        nbCasesBateauIntactes++;
                    }
            }
        }


    return nbCasesBateauIntactes;
}

void afficherScoreFinal()
{
    double tempsEcoule = 0.0;
    int tempsEcouleArrondi = VALEUR_INIT;
    int tempsRestant = VALEUR_INIT;


    // calcule le temps qui a été nécessaire pour terminer la partie, end est de type prédéfini clock_t (long)
    endTime = clock();
    tempsEcoule = ( (double)(endTime - startTime) ) /CLOCKS_PER_SEC;  // on divise par la constante pour avoir la valeur en secondes
    tempsEcouleArrondi = ceil(tempsEcoule);                            // arrondi à la valeur supérieure
    tempsRestant = 420 - tempsEcouleArrondi;
    scoreFinal = tempsRestant - (2*nbCoupsJoues);
    logEvent("[système] - Calcul du score final");

        // si l'utilisateur a dépassé le temps et qu'il reste des bateaux entiers
        if (tousBateauxCoules == 0)
        {
            Gotoxy(10,3); printf("Game over !\n");
            Gotoxy(10,5); printf("%s",separateur);
            Gotoxy(10,10); printf("Désolé, vous avez perdu au temps.");
            Gotoxy(10,12); printf("Vous n'aviez que 7 minutes pour finir le jeu.");
            Gotoxy(24,16); printf("**************************************");
            Gotoxy(37,18); printf("Pas de score marqué pour cette partie");
            Gotoxy(24,20); printf("**************************************");

        } else
        {
            // enregistre le score et le nom du joueurs dans un fichier scores.txt
            logEvent("[sauvegarde] - score final et prénom du joueur");
            enregistrerScoreFinal();

            Gotoxy(10,3); printf("Score final\n");
            Gotoxy(10,5); printf("%s",separateur);
            Gotoxy(10,10); printf("Temps necessaire pour terminer la partie (- 1 point par seconde) : %i secondes", tempsEcouleArrondi);
            Gotoxy(10,12); printf("Nombre de missiles tires (- 5 points par coup) : %i coups", nbCoupsJoues);
            Gotoxy(36,16); printf("*************");
            Gotoxy(37,18); color(15,3); printf("Score : %i", scoreFinal); color(7,0);
            Gotoxy(36,20); printf("*************");
        }


    Gotoxy(10,25); printf("Tapez une touche pour retourner au menu principal. ");

    fflush(stdin);
    getchar();
    system("cls");
    main();
}

void afficherScores()
{
    // commence à afficher les scores 6 pixels plus bas que le haut de l'écran
    int yPosScore = 7;

    // numéro de ligne du fichier
    int nbLignes = VALEUR_INIT;

    Gotoxy(10,3); printf("Scores des parties precedentes");
    Gotoxy(10,5); printf("%s",separateur);
    Gotoxy(10,yPosScore);

    // pointeur sur le fichier
    FILE *fichierScores = NULL;

    // ouverture du fichier en mode lecture seule
    fichierScores = fopen("scores.txt", "r");

        // lecture de chaque ligne du fichier
        do {

            // lit le nom du joueur et son score ensemble
            fgets(joueurScoreCharge, 20, fichierScores);

            // scanne la chaîne jusqu'au caractère séparateur ":" et en extrait une partie
            // qu'on stocke dans joueurCharge
            sscanf (joueurScoreCharge, "%[^:]", joueurCharge);

            // scanne une deuxième fois la même chaine pour en extraire le score,
            // qu'on stocke dans scoreCharge
            sscanf (joueurScoreCharge, "%*[^0-9]%i", &scoreCharge);

            // affichage du nom du joueur et du score qu'il a obtenu, 2 pixels plus bas
            yPosScore+=2;
            Gotoxy(10,yPosScore); printf("%s - %i", joueurCharge, scoreCharge);

            nbLignes++;

        // tant qu'on n'est pas au bout du fichier
        } while(feof(fichierScores) == 0);

    // fermeture du fichier
    fclose (fichierScores);

    color(14,0);
    Gotoxy(10,32); printf("Tapez une touche pour retourner au menu precedent.");
    color(7,0);

    // attente d'appui sur une touche
    fflush(stdin);
    getchar();

    system("cls");
    logEvent("[système] - Page de titre chargée");
    main();
}

void enregistrerScoreFinal()
{
    // pointeur sur le fichier
    FILE *fichierScores = NULL;

    // ouverture du premier fichier en mode lecture et écriture depuis le début
    fichierScores = fopen("scores.txt", "a+");

    // ajoute une ligne supplémentaire, contenant le nom du joueur sélectionné, un séparateur (:) et son score final
    fprintf(fichierScores, "\n%s:%i", prenom, scoreFinal);

    // fermeture du fichier
    fclose (fichierScores);

}

void menuAide()
{
    Gotoxy(10,3); printf("Regles du jeu");
    Gotoxy(10,5); printf("%s",separateur);

    Gotoxy(10,8); printf("Vous allez jouer sur une grille de %i colonnes fois %i lignes.",10,10);

    Gotoxy(10,10); printf("Une flotte est composee de 5 bateaux :");
    Gotoxy(10,12); printf("- Le porte avion "); color(14,0); printf("(5 cases)"); color(7,0);
    Gotoxy(10,14); printf("- le croiseur "); color(14,0); printf("(4 cases)"); color(7,0);
    Gotoxy(10,16); printf("- le contre-torpilleur "); color(14,0); printf("(3 cases)"); color(7,0);
    Gotoxy(10,18); printf("- le sous-marin "); color(14,0); printf("(3 cases)"); color(7,0);
    Gotoxy(10,20); printf("- le torpilleur "); color(14,0); printf("(2 cases)"); color(7,0);

    Gotoxy(10,23); printf("L'ordinateur place horizontalement ou verticalement ses bateaux, sans se chevaucher.");
    Gotoxy(10,25); printf("A chaque coup, vous entrez les coordonnees ou vous souhaitez tirer un missile.");

    Gotoxy(10,27);printf("La partie s'acheve quand vous avez coule tous les bateaux de l'ordinateur.");

    color(14,0);
    Gotoxy(10,32);printf("Tapez une touche pour retourner au menu precedent.");
    color(7,0);

    // attente d'appui sur une touche
    fflush(stdin);
    getchar();

    system("cls");
    logEvent("[système] - Page de titre chargée");
    main();
}

void logEvent(char evenement[100])
{
    time_t actTime;
    struct tm *timeComp;
    char timestamp[25];

    time(&actTime);
    timeComp = localtime(&actTime);

    // pointeur sur le fichier
    FILE *fichierLog = NULL;

    // ouverture du premier fichier en mode lecture et écriture depuis le début
    fichierLog = fopen("log.txt", "a+");

    // ajoute une ligne supplémentaire, puis un crochet ouvrant dans le fichier
    fprintf(fichierLog, "\n[");

    // copie la date et l'heure formattées dans la chaîne timestamp
    sprintf(timestamp, "%d-%02d-%02d %02d:%02d:%02d", timeComp->tm_year + 1900,
                                                    timeComp->tm_mon + 1,
                                                    timeComp->tm_mday,
                                                    timeComp->tm_hour,
                                                    timeComp->tm_min,
                                                    timeComp->tm_sec);

    // écrit la chaîne formatée de type aaaa-mm-jj hh:mm:ss
    fprintf(fichierLog, "%s", timestamp);
    fprintf(fichierLog, "] - ");

    // écrit l'événement
    fprintf(fichierLog, "%s", evenement);

    // fermeture du fichier
    fclose (fichierLog);
}

void color(int t,int f)
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,f*16+t);
}


