#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <cmath>

using namespace std;

struct instance
{
    int taille, penalite;
    int ** matrice;
};

struct solution {

    int taille, score;
    char ** matrice;
};

void initialisationInstance (string ficA, instance & g) // Initialise l'instance g avec ficA son adresse
{
    ifstream fichier(ficA);
    if(fichier)
    {
        int t;
        fichier >> t; g.taille = t;
        fichier >> g.penalite;

        g.matrice = new int * [t];

        for (int i = 0; i < t; ++i)
        {
            g.matrice[i] = new int [t];
            for (int j = 0; j < t; ++j)
            {
                fichier >> g.matrice[i][j];
            }
        }
    }
    else cerr << "Erreur : le fichier ne peut pas être lu !";
}

void suppressionInstance (instance & g)
{
    for (int i = 0; i < g.taille; ++i)
        delete[] g.matrice[i];
    delete[] g.matrice;
}

void affichageInstance (instance g)
{
    int t = g.taille;
    cout << t << ' ' << g.penalite;

    for (int i = 0; i < t; ++i)
    {
        cout << endl;
        for (int j = 0; j < t; ++j)
            cout << g.matrice[i][j] << ' ';
    }
    cout << endl;
}

bool valide (solution s)
{
    int t = s.taille;
    int r = 0;
    int i = 0, j = 0;

    while (r < 2 and i < t)
    {
        do
        {
            if (s.matrice[i][j++] == 'R') r++;
        }
        while (r < 2 and j < t);

        if (r < 2) //On peut s'en passer si la grilles est grande
        {
            j = 0;
            ++i;
        }
    }
    // cout << endl << r << ' ' << i << ' ' << j << endl;
    return r == 1;
}

void genereSolutionAlea (solution & s, instance g)
{
    int t = g.taille;
    s.taille = t;
    
    srand(time(NULL));
    
    char lettres[] = {'J', 'V', 'N', 'B', 'O', 'R'}; 

    s.matrice = new char * [t];
    for (int i = 0; i < t; ++i) s.matrice[i] = new char [t]; 
    
    do
    {
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < t; ++j)
            {
                s.matrice[i][j] = lettres[rand() % 6];
            }
        }
    } while (!valide(s));
}

void affichageSolution (solution s)
{
    int t = s.taille;

    for (int i = 0; i < t; ++i)
    {
        cout << endl;
        for (int j = 0; j < t; ++j)
            cout << s.matrice[i][j] << ' ';
    }
    cout << endl;
    cout << endl << s.score << endl;
}

void suppressionSolution (solution & s)
{
    for (int i = 0; i < s.taille; ++i)
        delete[] s.matrice[i];
    delete[] s.matrice;
}

//void saisieSolution(solution & s, instance g)
//{
//    int t = g.taille;
//    s.taille = t;
//    
//    s.matrice = new char * [t];
//    for (int i = 0; i < t; ++i) s.matrice[i] = new char [t];
//
//    for (int i = 0; i < t; ++i)
//    {
//        for (int j = 0; j < t; ++j)
//        {
//            cin >> s.matrice[i][j];
//        }
//    }
//}

bool pion_orthogonal(solution s,char l,int i,int j)
{
    if (i==0 and j==0) return (s.matrice[i+1][j]==l or s.matrice[i][j+1]==l);
    if(i==0 and j==s.taille-1) return (s.matrice[i][j-1]==l or s.matrice[i+1][j]==l);
    if(i==s.taille-1 and j==0) return(s.matrice[i-1][j]==l or s.matrice[i][j+1]==l);
    if(i==s.taille-1 and j==s.taille-1)return (s.matrice[i][j-1]==l or s.matrice[i-1][j]==l);

    /*   
    if (i>0 and i<s.taille) //Test bord de ligne
    {
        cout<<"test";
        if (j>0 and j <s.taille) //Test bord de colonne
        {
            return (s.matrice[i-1][j]==l or s.matrice[i+1][j]==l or s.matrice[i][j-1]==l or s.matrice[i][j+1]==l);
        }
    }
    if (j-1==-1) //Première colonne
    {
        if(i-1==-1) //Première ligne
        {
            return (s.matrice[i][j+1]==l or s.matrice[i+1][j]==l);
        }
        if(i+1>=s.taille)//Dernière ligne
        {
            return (s.matrice[i-1][j]==l or s.matrice[i][j+1]==l);
        }
        return (s.matrice[i-1][j]==l or s.matrice[i+1][j] or s.matrice[i][j+1]==l);
    }
    if (j+1>s.taille) //Dernière colonne
    {
        cout<<"test";   
        if(i-1==-1) //Première ligne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i+1][j]==l);
        }
        if(i+1>=s.taille) //Dernière ligne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i-1][j]==l);
        }
        return(s.matrice[i-1][j]==l or s.matrice[i+1][j]==l or s.matrice[i][j-1]==l);
    }
    if (i-1==-1) //Première ligne
    {
        if (j-1==-1) //Première colonne
        {
            return (s.matrice[i][j+1]==l or s.matrice[i+1][j]==l);
        }
        if (j+1>=s.taille) //Dernière colonne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i+1][j]==l);
        }
    }
    if (i+1>=s.taille) //Dernière ligne
    {
        if (j-1==-1) // Première colonne
        {
            return (s.matrice[i-1][j]==l or s.matrice[i][j+1]==l);
        }
        if (j+1>=s.taille) // Dernière colonne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i-1][j]==l);
        }
    }
    */
    return 0;
}

bool pion_diagonal(solution s,char l,int i,int j)
{
    return false;
}

int compteur_pion(solution s,char l)
{
    return false;
}

int pionsBleus (solution s, instance g)
{
    //Pour debug suivre les indication en commentaire
    // int nbNegatif = 0, nbPositif = 0; 

    int d = 0; //Différence entre le nombre le nombre de case strictement négatif et le nombre de case strictement positif
    int t = s.taille; //Taille de la solution
    
    //Optimiser si petit différence (d)
    for (int i = 0; i < t; ++i)
        for (int j = 0; j < t; ++j)
        {
            int val = g.matrice[i][j];
            if (s.matrice[i][j] == 'B')
            {
                //Decommenter pour debug
                // if (val > 0) nbPositif++;
                // if (val < 0) nbNegatif++;
                //Commenter pour debug
                if (val > 0) --d; //Comptage d'une valeur strictement positive
                if (val < 0) ++d; //Comptage d'une valeur strictement négative
            }
        }

    //Decommenter pour debug
    // int d2 = nbNegatif - nbPositif;
    // nbNegatif = 0, nbPositif = 0;
    
    //Optimiser si grande différence (d)
    /*
    int i = 0, j = 0, c = t*t+1, val; //Nombre de case à parcourir
    while (!(abs(d) > c) and i < t)
    {
        do
        {
            val = g.matrice[i][j];
            if (s.matrice[i][j++] == 'B')
            {
                //Decommenter pour debug
                // if (val > 0) nbPositif++;
                // if (val < 0) nbNegatif++;
                // d = nbNegatif - nbPositif;
                //Commenter pour debug
                if (val > 0) --d; //Comptage d'une valeur strictement positive
                if (val < 0) ++d; //Comptage d'une valeur strictement négative
            }
            c--;
        }
        while (!(abs(d) > c) and j < t);

        if (!(abs(d) > c))
        {
            j = 0;
            ++i;
        }
    }*/

    //Decommenter pour debug
    // cout << endl << "Debug pions bleus : " << "nombre de valeurs negatifs = " << nbNegatif << ' ' << "nombre de valeurs positives = " << nbPositif << ' ' << "position du dernier pion observé = "<< i << ' ' << j << " (Indexation pour l'agorithme n°2)" << ' '<< "difference algo n°1 = " << d2 << ' ' << "difference algo n°2 = " << d << ' ' << "valeur des pénalités = " << g.penalite << ' '; d > 0 ? cout << "pénalité pion bleu = " << -d * g.penalite  << endl : cout << "pénalité pion bleu = " << 0  << endl;
    if (d > 0) return d;
    return 0;
}

int pionRouge (solution s, instance g)
{
    int i = 0, j = 0, t = s.taille;
    bool pionRouge = false;

    while (!pionRouge and i < t)
    {
        do
        {
            if (s.matrice[i][j++] == 'R') pionRouge = true;
        }
        while (!pionRouge and j < t);

        if (!pionRouge)
        {
            j = 0;
            ++i;
        }
    }

    int valPion = g.matrice[i][j-1];

    // cout << "debug pionRouge : " << "position pion rouge = [" << i << "][" << j << "] " << "(indexation éronée) " << "valeur= " << valPion << ' ' << "pénalité pion rouge = " << -valPion << endl;
    return -valPion;
}

void calculeScore (solution & s, instance g)
{
    int score = 0;
    int nbPenalite = 0;

    nbPenalite += pionsBleus(s, g); //Pion bleus = pénalité seulement, score = 0
    score += pionRouge(s, g); //Pion rouge = score seulement, aucune pénalité

    // cout << "debug calculeScore : " << "nombre de pénalités = " << nbPenalite << ' ' << "valeur des pénalités = " << g.penalite << endl;
    s.score = score - nbPenalite * g.penalite;
}

int main ()
{
    string repertoire = "Instances/probleme_4_a.txt";
    instance a ;
    solution b;

    initialisationInstance(repertoire, a);
    affichageInstance(a);
    genereSolutionAlea(b, a);
    calculeScore(b, a);
    affichageSolution(b);
    valide(b) == 1 ? cout << endl << "Solution valide." << endl : cout << endl << "Solution invalide." << endl;
    
    
    suppressionInstance(a);
    suppressionSolution(b);
}