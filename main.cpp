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
    int score;
    char ** matrice;
};

void initialisation (string ficA, instance & g)
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

void suppressionSolution (instance g)
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

void affichageSolution (solution s, int t)
{
    for (int i = 0; i < t; ++i)
    {
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
    if (r == 1) return true;
    return false;
}

void genereSolution (solution & s, int t)
{
    srand(time(NULL));
    char lettres[] = {'J', 'V', 'N', 'B', 'O', 'R'}; 

    s.matrice = new char * [t];
    for (int i = 0; i < t; ++i) s.matrice[i] = new char [t]; 
    
    // do
    // {
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < t; ++j)
            {
                s.matrice[i][j] = lettres[rand() % 6];
            }
        }
    // } while (!valide(s, t));
}

int main ()
{
    string repertoire = "instances hors-compétition (15)/probleme_4_a.txt";
    instance a;
    solution b;

    initialisation(repertoire, a);
    affichageInstance(a);
    genereSolution(b, a.taille);
    affichageSolution(b, a.taille);
    cout << endl << valide(b, a.taille) << endl;

    return 0;
}