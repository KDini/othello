#include <stdio.h> //Le PROJET
#include <stdlib.h>
//Question 1
#define TAILLE_CH 256 //Nombre de caractere maximal pour un nom
#define NB_CASES 64    // Nombre de case contenu dans un tableau d'entier
#define NB_CASES_PAR_LIGNE 8 // Nombre d'entier par ligne
//Question 2
struct partie
{
    int damier[NB_CASES]; //Damier contenant 64 cases d'entier
    char nomJ1[TAILLE_CH]; //Premier joueur
    char nomJ2[TAILLE_CH];  //2eme joueur
    int premierJoueurJoue;  //premierJoueurJoue = 1 si 1er joueur joue sinon 0
};
//Question 3
int getCase(struct partie *p, int ligne, int colonne)
{
    if ((ligne >= 0 && ligne <= (NB_CASES_PAR_LIGNE-1)) && (colonne >= 0 && colonne <=  (NB_CASES_PAR_LIGNE-1)))
        return (*p).damier[(NB_CASES_PAR_LIGNE * (ligne))+colonne]; // -1 pour pas aller sur la case d'a coter
    else
        printf("SAISIE INCORRECT ");
    return 2;
}
//Question 4
void setCase(struct partie *p, int ligne, int colonne, int val)
{
    if (ligne>=0 && ligne<=NB_CASES_PAR_LIGNE-1 && colonne>=0 && colonne<=NB_CASES_PAR_LIGNE-1 && val>=-1 && val<=1)
        (*p).damier[(NB_CASES_PAR_LIGNE * (ligne))+colonne]=val;
    else
        printf("SAISIE INCORRECT");
}
//Question 5
void changementJoueur(struct partie *p)
{
    if((*p).premierJoueurJoue==1)
        (*p).premierJoueurJoue=0;
    else
        (*p).premierJoueurJoue=1;
}

//Question 6
struct partie* creerPartie ()
{
    struct partie *p;
    p = malloc (sizeof (struct partie));
    if ( p == NULL )
    {
        printf("Allocation impossible ");
        exit(1);
    }
    printf("Joueur 1 = ");
    scanf("%s", (*p).nomJ1 ); //Demande le nom du 1er joueur
    printf("Joueur 2 = ");
    scanf("%s", (*p).nomJ2); //Demande le nom du 2eme joueur
    (*p).premierJoueurJoue = 1; // Le premier joueur commence
    int i;
    for (i=0; i<NB_CASES; i++) //Tout les case sont a 0
        (*p).damier[i]=0;
    setCase(p,3,3,-1); //Initialise la case(3,3) a 1
    setCase(p,3,4,1); //Initialise la case(3,4) a -1
    setCase(p,4,3,1); //Initialise la case(4,3) a -1
    setCase(p,4,4,-1); //Initialise la case(4,4) a 1
    return p;
}
//Question 7
void affichage1(struct partie * p)
{
    int i;
    printf("\n");
    for ( i = 0 ; i < NB_CASES ; i++)
    {
        if((*p).damier[i]==-1) //Si le contenu = -1, on diminu l'epase pour le "-"
            printf("  %d   ",(*p).damier[i]);
        else
            printf("   %d   ",(*p).damier[i]);
        if((i+1)%NB_CASES_PAR_LIGNE==0)
            printf("\n\n");
    }
}

void affichage2 (struct partie * p)
{
    int i,j=0;
    char N ='N';
    char B ='B';
    char RIEN = ' ';
    printf ("\n");
    for (i=0; i<NB_CASES_PAR_LIGNE; i++)
        printf ("    %d   ", i);
    printf("\n*****************************************************************\n");
    printf("*       *       *       *       *       *       *       *       *\n");
    for ( i = 0 ; i < NB_CASES ; i++)
    {
        if ((*p).damier[i] == (1))
            printf ("*   \033[31m%c\033[0m   ", N);
        else if ((*p).damier[i] == -1)
            printf ("*   \033[34m%c\033[0m   ", B);
        else if ((*p).damier[i] == 0)
            printf ("*   %c   ",RIEN);
        if((i+1)%NB_CASES_PAR_LIGNE==0)
        {
            printf("*  %d\n*       *       *       *       *       *       *       *       *",j); //Le dernier point du tableau
            printf("\n*****************************************************************\n");       // et afficher la ligne
            if ( j < 7) //pour ne pas afficher la derniere ligne
            {
                printf("*       *       *       *       *       *       *       *       *\n");
                j++;
            }
        }
    }
}
//Question 8 PARTIE 2
int priseDansDirectionPossible (struct partie *p, int ligne, int colonne, int horizontal, int vertical )
{
    int pion;
    if ((*p).premierJoueurJoue == 1)
        pion = 1;
    else
        pion = -1;
    //pion = 1;
    int i = ligne + vertical ;
    int j = colonne + horizontal;

    while (i >= 0 && j >= 0)
    {
        int x = getCase(p,i,j);
        if ( x == 0)
        {
            return 0;
        }
        else if ( x == pion )
        {
            i=i+vertical;
            j=j+horizontal;
        }
        else if ( x != pion )
        {
            i=i+vertical;
            j=j+horizontal;
            x = getCase(p,i,j);
            if ( x == 0)
                return 0;
            else if ( x == pion )
                return 1;
        }
    }
    return 0;
}
//Question 9
int coupValide(struct partie *p, int ligne, int colonne)
{
    int pion;
    if ((*p).premierJoueurJoue == 1)
        pion = 1;
    else
        pion = -1;
    int horizontal;
    int vertical;
    int x=getCase(p,ligne,colonne);
    int val;
    if(x==0) // si c'est une case vide
    {
        for(horizontal=-1; horizontal<=1; horizontal++) // pour le parcours de -1 à 1
        {
            for(vertical=-1; vertical<=1; vertical++) // pour le parcours de -1 à 1
            {
                val=priseDansDirectionPossible (p,ligne,colonne,horizontal, vertical);
                if(val==pion)
                    return 1;
            }
        }
        return 0;
    }
    else
        return 0;
}
//Question 10
void mouvementDansDirection(struct partie *p, int ligne, int colonne, int horizontal, int vertical)
{
    int x;
    int res=priseDansDirectionPossible (p,ligne,colonne,horizontal,vertical );
    if(res==1) // si la  prise est possible c'est egale à 1
    {
        if((*p).premierJoueurJoue==1) // si c'est le premier joueur (pion noir)
        {

            do
            {
                setCase(p,ligne,colonne,1);
                colonne=colonne+horizontal;
                ligne=ligne+vertical;
                x=getCase(p,ligne,colonne);
            }
            while(x!=1);
        }
        else
        {
            do
            {
                setCase(p,ligne,colonne,-1);
                colonne=colonne+horizontal;
                ligne=ligne+vertical;
                x=getCase(p,ligne,colonne);
            }
            while(x!=-1);  // tant que getcase ne rencontre pas une case blanche... il y a la boucle pour manger les pions noirs
        }
    }
    else
    {
        printf("mouvement pas possible\n");
    }// erreur
}
//Question 11
void mouvement(struct partie *p, int ligne, int colonne)
{
    int horizontal;
    int vertical;
    int x;

    for(horizontal=-1; horizontal<2; horizontal++) // pour le parcours de -1 à 1
    {
        for(vertical=-1; vertical<2; vertical++) // pour le parcours de -1 à 1
        {
            x=priseDansDirectionPossible (p,ligne,colonne,horizontal, vertical);
            if(x==1)
                mouvementDansDirection(p,ligne,colonne,horizontal,vertical);
        }
    }
}
//Question 12
int joueurPeutJouer(struct partie *p)
{
    int ligne,colonne;
    int x;
    for(ligne=0; ligne<NB_CASES_PAR_LIGNE-1 ; ligne++)
    {
        for(colonne=0; colonne<NB_CASES_PAR_LIGNE-1; colonne++)
        {
            x=coupValide(p,ligne,colonne);
            if(x==1)
                return 1;
        }
    }
    return 0;
}

int main()
{
    struct partie *p;
    p = creerPartie();
    //printf ("Valeur sur la case (0,5) : %d\n", getCase(p,0,5));
   //printf ("Valeur sur la case (0,6) : %d\n", getCase(p,0,6));
    //printf ("Valeur sur la case (5,3) : %d\n", getCase(p,5,3));
    printf("\n");
    //setCase(p,0,6,0);
    //setCase(p,0,0,1);
    //setCase(p,7,7,-1);
    /*setCase(p,4,3,1); //Initialise la case(4,3) a 1
    setCase(p,4,2,1);
    setCase(p,4,5,1);
    setCase(p,4,6,1);
    setCase(p,4,7,1);
    setCase(p,4,1,-1);
    setCase(p,4,4,1);*/


    setCase(p,2,2,1);// pour mouvementdansdirection ou mouvement
    setCase(p,4,5,-1);// pour mouvement
    setCase(p,3,5,1);// pour mouvement

    affichage2(p);
    printf("\n");
    mouvement(p,5,5);// pour mouvement
    //printf(" %d ",priseDansDirectionPossible(p,4,2,1,0));
    //printf(" %d ",priseDansDirectionPossible(p,2,5,-1,1));
    //printf(" %d ",priseDansDirectionPossible(p,4,0,1,0));

    int x=joueurPeutJouer(p);
    printf("\n joueur peut jouer: %d",x);
    /*
    int x = 0;
    while(x == 0) // une boucle infini pour ne pas liberé p
    {};
    free(p);*/
    return 0;
}
