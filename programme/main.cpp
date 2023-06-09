#include "score.h"
#include "scorematrice.h"
#include "algo.h"
#include "structure.h"
#include "autre.h"
#include "common.h"

#include <string>
//Effacer le terminal sous windows
#include <cstdlib>
#include <ctime>

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

int main (int argc, char ** argv)
{
    clock_t depart = clock();
    cout << depart << endl;
    //Nettoyage du termnial (affichage propre)
    clear();

    //Chemins d'accès au fichier d'entrée
    string cheminInstance, cheminSortie;
    cheminInstance = argv[1], cheminSortie = argv[2];

    //Création de l'instance (fichier d'entrée)
    instance a;
    //Création de la solution (fichier de sortie)
    solution b;

    //Initialisation de la grille de l'instance
    initialisationInstance(cheminInstance, a);
    //Achiffage du chemin d'accès de l'instance
    cout << cheminInstance << endl;
    //Affichage de la instance dans le terminal
    affichageInstance(a);

    //Initialisation de la solution via l'algorithme
    b.taille = a.taille;
    //Calcule de la grille solution
    b.matrice = Boptimal(a);
    //Calcule du score de la solution
    calculeScore(b, a);
    //Achiffage du chemin d'accès de la solution
    cout << cheminSortie << endl;
    //Affichage de la solution dans le terminal
    affichageSolution(b);

    clock_t fin = clock();
    cout << endl << "Temps d'exécution : "<< fin/CLOCKS_PER_SEC << " secondes." << endl;
    
    //Ecriture dans un fichier de la solution
    ecriture(cheminSortie, b);

    return 0;
}