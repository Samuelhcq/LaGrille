#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct instance
{
    int taille, penalite;
    int ** matrice;
};

struct solution
{
    int taille,score;
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

void suppressionInstance (instance g)
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
}

bool valideSolution(solution s)
{
    int compteur_r=0,i=0,j=0;
    while(i< s.taille and compteur_r<=1)
    {
<<<<<<< Updated upstream
        cout << endl;
        for (int j = 0; j < t; ++j)
            cout << s.matrice[i][j] << ' ';
    }
    // cout << endl << s.score << endl;
}

bool valide (solution s, int t)
{
    int r = 0;
    int i = 0, j = 0;

    while (r < 2 and i < t)
    {
        while (j < t)
        {
            if (s.matrice[i][j] == 'R') r++;
            ++j;
        }
        j = 0;
        ++i;
    }
    if (r != 1) return false;
    return true;
=======
        if (s.matrice[i][j]== 'R')compteur_r++;
        j++;
        if (j==s.taille)
        {
            j=0;
            ++i;
        }
    }
    return compteur_r==1;
>>>>>>> Stashed changes
}

void genereSolution (solution & s,int t)
{
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
    } while (!valideSolution(s));
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
    // cout << endl << s.score << endl;
}

void suppressionSolution (solution g)
{
    for (int i = 0; i < g.taille; ++i)
        delete[] g.matrice[i];
    delete[] g.matrice;
}

void SaisieSolution(solution & s)
{
    cout<<"Quelle est la taille de la matrice solution ? ";
    cin>>s.taille;
    s.matrice = new char * [s.taille];
    for (int i = 0; i < s.taille; ++i) s.matrice[i] = new char [s.taille];

    for (int i = 0; i < s.taille; ++i)
    {
        for (int j = 0; j < s.taille; ++j)
        {
            cin>>s.matrice[i][j];
        }
    }
}

int calculpoint(instance g,solution s)
{
    int scoreTotal=0;

    for (int i=0;i<s.taille;++i)
    {
        for (int i j=0;j<s.taille;++j)
        {
            val_case=g.matrice[i][j];
            car_case=s.matrice[i][j];

            if (car_case='J') //Jaune
            {
                
            }
        }
    }
}
int main ()
{
<<<<<<< Updated upstream
    string repertoire = "instances hors-compétition (15)/probleme_4_a.txt";
    instance a;
    solution b;

    initialisation(repertoire, a);
    affichageInstance(a);
    genereSolution(b, a.taille);
    affichageSolution(b, a.taille);
    cout << endl << valide(b, a.taille) << endl;

=======
    //string repertoire = "problemes/probleme_4_a.txt";
    //instance a;
    solution s;
    SaisieSolution(s);
    affichageSolution(s);
    cout<<"Solution valide ?"<<valideSolution(s);
>>>>>>> Stashed changes
    return 0;
}
