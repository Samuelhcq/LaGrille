#include "structure.h"
#include "common.h"

//Lire des fichiers
#include <fstream>
#include <string>
#include <vector>

//Initialisation du fichier d'entrée
void initialisationInstance (string ficA, instance & g)
{
    //Ouverture du fichier
    ifstream fichier(ficA);
    
    //Lecture du fichier
    if (fichier)
    {
        //Assignation de la taille de la grille et de la valeur des pénalités
        int t;
        fichier >> t; g.taille = t;
        fichier >> g.penalite;

        //Création de la variable temporaire accueillant le nombre lu
        int nombre;
        //Création deuxième dimension de la matrice grille (vecteur temporaire)
        vector <int> temp;
        //Assignation de la grille
        for (int i = 0; i < t; ++i)
        {
            //Suppréssion des valeurs du vecteur temporaire (nécessaire)
            temp.clear();
            for (int j = 0; j < t; ++j)
            {
                //Lecture du nombre (avec comme séparateur ' ')
                fichier >> nombre;
                //Assignation du nombre lu dans le vecteur
                temp.push_back(nombre);
            }
            //Création de la première dimension de la matrice grille (vecteur)
            //Réduction de la taille du vecteur temporaire (optimisation)
            temp.shrink_to_fit();
            g.matrice.push_back(temp);
        }
    }
    //Message d'erreur
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !" << endl;
    //Réduction de la taille du vecteur matrice (optimisation)
    g.matrice.shrink_to_fit();
}

//Afichage de la grille (fichier d'entrée)
void affichageInstance (instance g)
{
    //Création de la variable taille
    int t = g.taille;
    
    //Affichage de la taille de la grille
    cout << t << ' ' << g.penalite;

    //Affichage de la grille
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

//Afichage de la solution (fichier de sortie)
void affichageSolution (solution s)
{
    //Création de la variable taille
    int t = s.taille;
    
    //Affichage de la solution
    for (int i = 0; i < t; ++i)
    {
        cout << endl;
        for (int j = 0; j < t; ++j)
        {
            cout << s.matrice[i][j] << "\t";
        }
    }
    cout << endl;

    //Affichage du score de la solution
    cout << endl << "Score final : " << s.score << endl;
}

void ecriture (string ficA, solution s)
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
        fichier.close();
    }
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être ouvert pour l'écriture !" << endl;
}