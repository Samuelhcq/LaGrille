#include "structure.h"
#include "common.h"

//Lire des fichiers
#include <fstream>
#include <string>
#include <vector>

void initialisationInstance (string ficA, instance & g) //Initialisation du fichier d'entrée
{
    ifstream fichier(ficA);
    if (fichier)
    {
        int t;
        fichier >> t; g.taille = t;
        fichier >> g.penalite;
        int nombre;
        vector <int> temp;
        for (int i = 0; i < t; ++i)
        {
            temp.clear();
            for (int j = 0; j < t; ++j)
            {
                fichier >> nombre;
                temp.push_back(nombre);
            }
            temp.shrink_to_fit();
            g.matrice.push_back(temp);
        }
    }
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !" << endl;
    g.matrice.shrink_to_fit();
}

void affichageInstance (instance g) //Afichage de la grille (fichier d'entrée)
{
    int t = g.taille;
    cout << t << ' ' << g.penalite;
    for (int i = 0; i < t; ++i)
    {
        cout << endl;
        for (int j = 0; j < t; ++j)
        {
            cout << g.matrice[i][j] << "\t";
        }
    }
    cout << endl;
}

void affichageSolution (solution s) //Afichage de la solution (fichier de sortie)
{
    int t = s.taille;
    for (int i = 0; i < t; ++i)
    {
        cout << endl;
        for (int j = 0; j < t; ++j)
        {
            cout << s.matrice[i][j] << "\t";
        }
    }
    cout << endl << s.score << endl;
}

bool valide (solution s) //Vérification de la validitée de la solution
{
    int nbPionRouge = 0, i = 0, j = 0, t = s.taille;
    while (nbPionRouge < 2 and i < t)
    {
        do
        {
            if (s.matrice[i][j++] == 'R') nbPionRouge++;
        }
        while (nbPionRouge < 2 and j < t);
        j = 0;
        i++;
    }
    return nbPionRouge == 1;
}

void ecriture (string ficA, solution s) //Écrit la solution dans un fichier
{
    ofstream fichier(ficA);

    int t = s.taille;

    if (fichier)
    {
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < t; ++j)
            {
                fichier << s.matrice[i][j];
            }
            fichier << endl;
        }
        fichier<<s.score;
        fichier.close();
    }
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être ouvert pour l'écriture !" << endl;
}