#include <stdio.h>
#include <stdlib.h>
#define TAILLE_CH 256
#define NB_CASES 64
#define NB_CASES_PAR_LIGNE 8


//struct de la partie qui contient le damier (64 cases), le nom des deux joueurs, et une valeur pour savoir quel joueur commence
struct partie
{
    int damier[NB_CASES];
    char nomJ1 [TAILLE_CH];
    char nomJ2 [TAILLE_CH];
    int premierJoueurJoue;
};

//Fonction qui retourne la valeur d'une case du damier
int getCase(struct partie *p, int ligne, int colonne)
{
    if (ligne <= (NB_CASES_PAR_LIGNE -1) && colonne <= (NB_CASES_PAR_LIGNE -1) && ligne >= 0 && colonne >= 0)
    {
        int num= (NB_CASES_PAR_LIGNE*ligne) + colonne ; // calcul pour trouver le numero de la case
        int val= (*p).damier[num]; // val est la valeur contenu par la case
        return val; //retourne la valeur de la case
    }
    else
    {
        return -2;
    }
}

//Fonction qui permet de modifier la valeur d'une case du damier
void setCase(struct partie *p, int ligne, int colonne, int val)
{
    if (ligne <= (NB_CASES_PAR_LIGNE -1) && colonne <= (NB_CASES_PAR_LIGNE -1) && ligne >= 0 && colonne >= 0 && val<= 1 && val >= (-1))
    {
        int num= (NB_CASES_PAR_LIGNE*ligne) + colonne ; // calcul pour trouver le numero de la case
        (*p).damier[num]=val; // affecte la val a la case
    }
    else
    {
        printf("ERREUR setCase\n");
    }
}

//Fonction qui permet de modifier la valeur de l'attribut premierJoueurJoue du struct partie pour le changement de tour
void changementJoueur(struct partie *p)
{
    if ((*p).premierJoueurJoue == 0) //si c'est au tour du J2
        (*p).premierJoueurJoue =1; //tour passe au J1
    else
        (*p).premierJoueurJoue =0;
}

//Fonction qui crée une partie
struct partie* creerPartie ()
{
    struct partie *p;
    p=malloc(sizeof(struct partie)); // alloue dynamiquement la memoire de la taille d'un struct partie

    if (p==NULL)
        exit(1);

    printf("Entrez le nom du J1: ");
    scanf("%s",(*p).nomJ1);
    printf("Entrez le nom du J2: ");
    scanf("%s",(*p).nomJ2);
    (*p).premierJoueurJoue=1; // noir qui commence

    int i;
    for (i=0;i<NB_CASES;i++) // boucle pour mettre toutes les cases du damier Ã  0
    {
        (*p).damier[i]=0;
    }

     setCase(p,3,3,-1);//place les pions au milieu du champ damier
     setCase(p,3,4,1);
     setCase(p,4,3,1);
    setCase(p,4,4,-1);

    return p;
}

//Fonction d'affichage d'une partie
void affichage( struct partie * p)
{
    int j;
    int ligne =0;
    int colonne ;
    for (ligne=0;ligne<NB_CASES_PAR_LIGNE;ligne++)
    {
        printf("*************************************************\n"); // premiere ligne
        for (j=0;j<2;j++)
        {
            printf("*     *     *     *     *     *     *     *     *\n"); // 2/3lignes
        }
        for (colonne=0;colonne<NB_CASES_PAR_LIGNE;colonne++)    // 4 lignes avec les valeurs
        {
            if (getCase(p,ligne,colonne)==1)
                printf("*  N  ");
            else if (getCase(p,ligne,colonne)==-1)
                printf("*  B  ");
            else
                printf("*     ");
        }
        printf("*\n");
        for (j=0;j<2;j++)   // 5/6 lignes
        {
            printf("*     *     *     *     *     *     *     *     *\n");

        }
    }
    printf("*************************************************\n");
}

int priseDansDirectionPossible (struct partie *p, int ligne, int colonne, int horizontal, int vertical )
{
    int pion;
    if ((*p).premierJoueurJoue == 1)
        pion = 1;
    else
        pion = -1;
    //pion = -1;
    int i = ligne + vertical;
    int j = colonne + horizontal;

    while (i >= 0 && j >= 0 && i<=NB_CASES_PAR_LIGNE && j<=NB_CASES_PAR_LIGNE)
    {
        int x = getCase(p,i,j);
        if ( x == 0)
        {
            return 0;
        }
        else if ( x == pion )
        {
            return 0;
            /*i=i+vertical;
            j=j+horizontal;*/
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


int coupValide(struct partie *p, int ligne, int colonne)
{
    int horizontal;
    int vertical;
    int x=getCase(p,ligne,colonne);
    int val;
    if (x==0) // si c'est une case vide
    {
        for (horizontal=-1;horizontal<2;horizontal++) // pour le parcours de -1 à 1
        {
            for (vertical=-1;vertical<2;vertical++) // pour le parcours de -1 à 1
            {
                if (horizontal!=0 || vertical!=0)
                {
                    val=priseDansDirectionPossible (p,ligne,colonne,horizontal, vertical);
                    if (val==1)
                        return 1;
                }
            }
        }
        return 0;
    }
    else
        return 0;
}

void mouvementDansDirection(struct partie *p, int ligne, int colonne, int horizontal, int vertical)
{
    int x;
    int res=priseDansDirectionPossible (p,ligne,colonne,horizontal,vertical );
    if (res==1) // si la  prise est possible c'est egale à 1
    {

        if ((*p).premierJoueurJoue==1) // si c'est le premier joueur (pion noir)
        {

            do
            {
                setCase(p,ligne,colonne,1);
                colonne=colonne+horizontal;
                ligne=ligne+vertical;
                x=getCase(p,ligne,colonne);
            }
            while (x!=1);
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
            while (x!=-1); // tant que getcase ne rencontre pas une case blanche... il y a la boucle pour manger les pions noirs
        }
    }
    else
    {
        printf("mouvement pas possible\n");
    }// erreur
}

void mouvement(struct partie *p, int ligne, int colonne)
{

    int horizontal;
    int vertical;
    int x;

    for (horizontal=-1;horizontal<2;horizontal++) // pour le parcours de -1 à 1
    {
        for (vertical=-1;vertical<2;vertical++) // pour le parcours de -1 à 1
        {
            if (horizontal!=0 || vertical!=0)
            {
                x=priseDansDirectionPossible (p,ligne,colonne,horizontal, vertical);
                if (x==1)
                    mouvementDansDirection(p,ligne,colonne,horizontal,vertical);

            }
        }

    }
}

int joueurPeutJouer(struct partie *p)
{
    int ligne;
    int colonne;
    int x;
    for (ligne=0;ligne<NB_CASES_PAR_LIGNE;ligne++)
    {
        for (colonne=0;colonne<NB_CASES_PAR_LIGNE; colonne++)
        {
            x=coupValide(p,ligne,colonne);
            if (x==1)
            {
                return 1;
            }
        }
    }
    return 0;
}



//DEBUT PARTIE 3
int saisieJoueur(int *ligne,int *colonne)
{
    char saisie[20];
    printf("Veuillez saisir A pour abondonner , M pour retourner au menu principal , ou une case valide (num de la ligne entre a et h et num de colonne entre 1 et 8) : ");
    scanf("%s",saisie);

    int carac;
    for (carac=0;saisie[carac]!='\0';carac++)//compte le nb de caractere
    {
    }

    if (saisie[0]=='A' && carac ==1)
        return -2;
    else if (saisie[0]=='M'&& carac==1)
        return -1;
    else if (carac==2)
    {
        char i,j;
        int l=0;
        int c=0;

        for (i='a';i<='h';i++)//boucle de 'a' à 'h' pour le premier caratcere
        {
            if (saisie[0]== i )
            {
                for (j='1';j<='8';j++)//boucle de '1' à '8' pour le 2eme caracteres
                {
                    if (saisie[1]== j)
                    {
                        (*ligne)=l;//passage par adresse
                        (*colonne)=c;//passage par adresse
                        return 1;
                    }
                    c++;
                }
            }
            l++;
        }
    }
    else
        return 0;
    return 0;
}

int tourJoueur(struct partie *p)
{
    affichage(p);
    if ((*p).premierJoueurJoue==1)
        printf("A %s de jouer:\n",(*p).nomJ1);
    else
        printf("A %s de jouer:\n",(*p).nomJ2);

    if (joueurPeutJouer(p)==0)
    {
        changementJoueur(p);
        return 0;
    }

    int ligne=-1;
    int colonne=-1;
    int saisie;
    do
    {
        saisie=saisieJoueur(&ligne,&colonne);
        printf("ligne:%d\n",ligne);
        printf("colonne:%d\n",colonne);
    }
    while ((saisie==0) || (saisie==1 && (coupValide(p,ligne,colonne)==0)));//tant que saisie n'est pas 0 ou tant que les valeurs rentrées correspondent a un coup valide

    if (saisie==1)
    {
        mouvement(p,ligne,colonne);
        changementJoueur(p);
    }

    return saisie;
}

int gagnant(struct partie *p)
{
    int p_blanc=0;
    int p_noir=0;
    int i;
    for (i=0;i<NB_CASES;i++)//boucle sur tout le damier pour compter le nb de pion blanc/noir
    {
        if ((*p).damier[i]==1)
            p_noir++;
        else if ((*p).damier[i]==-1)
            p_blanc++;
    }
    if (p_noir>p_blanc)
        return 1;
    else if (p_noir<p_blanc)
        return -1;
    else
        return 0;

}

int FinPartie(struct partie *p)
{
    if (joueurPeutJouer(p)==0)//si le joueur courant ne peut pas jouer
    {
        changementJoueur(p);
        if (joueurPeutJouer(p)==0)//si le 2eme joueur aussi ne peut pas jouer donc aucun des 2 peut jouer
            return 1;
    }
    else
        return 0;
    return 0;
}

int jouerPartie(struct partie *p)
{
    int tour_J;
    do
    {
        tour_J=tourJoueur(p);

    }
    while ((FinPartie(p)==0) && tour_J!=-1 && tour_J!=-2);//tant que la partie n'est pas finie et tant que le joueur rentrer des cases

    if (tour_J==-1)
    {
        printf("Le joueur souhaite acceder au Menu Principal\n");
        return 0;
    }
    else
    {
        printf("La partie est terminee\n");
        return 1;
    }

}

int main()
{
    struct partie *p ;
    p=creerPartie ();

    /* PREMIER BLOC POUR TEST FONCTION Finpartie + gagnant
    setCase(p,3,3,0);
    setCase(p,3,4,0);
    setCase(p,4,3,0);
    affichage(p);
    printf("Aucun des 2 joueurs ne peut jouer donc FinParite=%d\n",FinPartie(p));
    setCase(p,3,3,-1);
    setCase(p,3,4,1);
    setCase(p,4,3,1);
    affichage(p);
    printf("Les joueurs sont a egalites d'ou gagnant=%d\n",gagnant(p));
    printf("Les joueurs peuvent jouer donc FinPartie=%d\n",FinPartie(p));
    setCase(p,0,0,1);
    affichage(p);
    printf("Le joueur 1 gagne d'ou gagnant=%d\n",gagnant(p));
    setCase(p,0,1,-1);
    setCase(p,0,2,-1);
    affichage(p);
    printf("Le joueur 2 gagne d'ou gagnant=%d\n",gagnant(p));
    */

    /* SECOND BLOC POUR TEST la fonction saisieJoueur
    int ligne,colonne,saisieJ;
    saisieJ=saisieJoueur(ligne,colonne);
    if(saisieJ==-2)
    printf("le joueur Abandonne\n");
    else if(saisieJ==-1)
    printf("le joueur souhaite retourner au Menu Principal\n");
    else if(saisieJ==1)
    printf("Le joueur a saisi une case Valide\n");
    else
    printf("le joueur a saisi n'importe quoi\n");*/

    /* TROISIEME BLOC POUR TEST la fonction tourJoueur
    int tourJ=tourJoueur(p);
    if(tourJ==-2)
    printf("le joueur Abandonne\n");
    else if(tourJ==-1)
    printf("le joueur souhaite retourner au Menu Principal\n");
    else if(tourJ==0)
    printf("Le joueur ne peut pas joueur");
    else{
    printf("Le joueur a saisi une case Valide\n");
    affichage(p);
    }*/

    // TEST LA FONCTION joueurPartie
    int test=jouerPartie(p);


    return 0;
}
