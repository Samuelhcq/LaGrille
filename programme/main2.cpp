#include "score.h"
#include "algo2.h"
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

    string repInstance = "../instances/competition_01.txt", repSortie = "../sortie.txt";
    instance a;
    //Création de la variable solution (fichier de sortie)
    solution b, b2;

    //Initialisation de la grille
    initialisationInstance(repInstance, a);
    affichageInstance(a);
    b = GenereSolution1(a);
    b2 = genere_voisin(b,a);
    calculeScore(b2, a);
    affichageSolution(b2);
    //ecriture(repSortie, b);
    return 0;
}