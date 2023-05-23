#include "score.h"
#include "algo.h"
#include "structure.h"
#include "autre.h"
#include "common.h"

#include <string>
//Effacer le terminal sous windows
#include <cstdlib>

//Nettoyage du terminal
void clear()
{
#ifdef _WIN32
    //Sous windows
    system("cls");
#else
    //Autre OS (Linux ...)
    system ("clear");
#endif
}

int main ()
{
    //Nettoyage du termnial (affichage propre)
    clear();

    //Chemin d'accès des fichiers d'entrées
    //Chemin de l'instance ('repInstance') et d'une solution ('repSolution')
    //Chemin d'une solution utile pour la fonction lectureSolution()
    string repInstance = "../instances/probleme_6_a.txt", repSolution = "../solutions/solution_6_a.txt", repSortie = "../sortie.txt";

    //Création de la variable grille (fichier d'entrée)
    instance a;
    //Création de la variable solution (fichier de sortie)
    solution b;

    //Initialisation de la grille
    initialisationInstance(repInstance, a);
    //Affichage de la grille
    affichageInstance(a);

    //Initialisation de la solution (selectionner le moyen de l'initialisation)
    //Initialisation aléatoire
    // genereSolutionAlea(b, a);
    //Initialisation d'un fichier
    lectureSolution(repSolution, b, a);
    //Initialisation par la saisie
    // saisieSolution(b, a);
    //Initialisation par algorithme

    //Calcule du score de la solution
    calculeScore(b, a);

    //Affichage de la solution avec le score
    // affichageSolution(b);
    cout << b.score << endl << endl;

    // ecriture(repSortie, b);
    //Débuggage
    // cout << endl << "Fin exécution." << endl;

    vector <vector <char>> r = placement_orange(a);

    for (int i = 0; i < a.taille; ++i)
    {
        for (int j = 0; j < a.taille; ++j)
        {
            cout << r[i][j] << "\t";
        }
        cout << endl;
    }

    // calques c;
    // calquesNV cNV;
    // genereCalques(c, a);
    // genereCalquesNV(cNV, a);
    // afficheCalque(c, cNV, a);

    return 0;
}