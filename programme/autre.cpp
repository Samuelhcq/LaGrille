#include "autre.h"
#include "common.h"

//Pour la génération de grille aléatoire
#include <ctime>
//Lire des fichiers
#include <fstream>

//Génération d'une solution aléatoirement
//Utile pour le débuggage de la fonction calculeScore()
void genereSolutionAlea (solution & s, instance g)
{
    //Création de la variable taille
    int t = g.taille;
    s.taille = t;
    
    //Sélection d'une seed aléatoirement (avec le module 'ctime')
    srand(time(NULL));
    
    //Création de la liste contenant les pions
    char lettres[] = {'J', 'V', 'N', 'B', 'O', 'R'}; 

    //Création deuxième dimension de la matrice grille (vecteur temporaire)
    vector <char> temp;

    //Génaration de la solution
    //Temps que la solution n'est pas valide on en génère
    do
    {
        //Supprésion du vecteur
        s.matrice.clear();
        for (int i = 0; i < t; ++i)
        {
            //Suppréssion des valeurs du vecteur temporaire (nécessaire)
            temp.clear();
            for (int j = 0; j < t; ++j)
            {
                //Assignation du pion aléatoirement parmis la liste des pions
                temp.push_back(lettres[rand() % 6]);
            }
            //Création de la première dimension de la matrice grille (vecteur)
            //Réduction de la taille du vecteur temporaire (optimisation)
            temp.shrink_to_fit();
            s.matrice.push_back(temp);
        }
        //Débuggage
        //cout << "Débuggage fonction genereSolutionAlea() : \t" << "valide=" << (valide(s) == 1 ? true : false) << endl;
    } while (!valide(s));
    //Réduction de la taille du vecteur matrice (optimisation)
    s.matrice.shrink_to_fit();
}

//Saisie d'une solution manuellement
void saisieSolution (solution & s, instance g)
{
    //Assignation de la variable taille
    int t = g.taille;
    s.taille = t;
    
    //Création de la variable temporaire accueillant le caractère
    char lettre;
    //Création deuxième dimension de la matrice grille (vecteur temporaire)
    vector <char> temp;

    //Saisie de la matrice solution
    for (int i = 0; i < t; ++i)
    {
        //Suppréssion des valeurs du vecteur temporaire (nécessaire)
        temp.clear();
        for (int j = 0; j < t; ++j)
        {
            //Saisie assigné à la variable temporaire
            cin >> lettre;
            //Réduction de la taille du vecteur temporaire (optimisation)
            temp.shrink_to_fit();
            //Injection de la saisie dans le vecteur temporaire
            temp.push_back(lettre);
        }
        //Création de la première dimension de la matrice grille (vecteur)
        s.matrice.push_back(temp);
    }
    //Réduction de la taille du vecteur matrice (optimisation)
    s.matrice.shrink_to_fit();
}

//Lecture d'une matrice solution
void lectureSolution (string ficA, solution & s, instance g)
{
    //Création de la variable taille
    int t = g.taille;
    s.taille = t;
    
    //Ouverture du fichier
    ifstream fichier(ficA);

    //Lecture du fichier
    if (fichier)
    {
        //Création de la variable temporaire accueillant le caractère lu
        char caractere;
        //Création deuxième dimension de la matrice grille (vecteur temporaire)
        vector<char> temp;

        //Assignation de la solution
        for (int i = 0; i < t; ++i)
        {
            //Suppréssion des valeurs du vecteur temporaire (nécessaire)
            temp.clear();
            for (int j = 0; j < t; ++j)
            {
                //Lecture du caractère (avec comme séparateur ' ')
                fichier >> caractere;
                //Réduction de la taille du vecteur temporaire (optimisation)
                temp.shrink_to_fit();
                //Assignation du nombre lu dans le vecteur
                temp.push_back(caractere);
            }
            //Création de la première dimension de la matrice grille (vecteur)
            s.matrice.push_back(temp);
        }
        //Réduction de la taille du vecteur matrice (optimisation)
        s.matrice.shrink_to_fit();
    }
    //Message d'erreur
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !" << endl;

    //Débuggage
    //cout << "Débuggage fonction lectureSolution() : \t" << "valide=" << (valide(s) == 1 ? true : false) << endl;
}

void afficheCalque (calques c, calquesNV cNV, instance g)
{
    int t = g.taille;

    for (int h = 0; h < 1; ++h)
    {
        cout << "Calque des pions : " << get<0>(cNV.matrice[h]) << endl;
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < t; ++j)
            {
                for (unsigned int k = 0; k < get<1>(cNV.matrice[h])[i][j].size(); ++k)
                {
                    cout << get<1>(cNV.matrice[h])[i][j][k] << (k == get<1>(cNV.matrice[h])[i][j].size()-1 ? "" : " ");
                }
                cout << "\t\t";
            }
            cout << endl;
        }
    }

    for (int h = 0; h < 5; ++h)
    {
        cout << "Calque des pions : " << get<0>(c.matrice[h]) << endl;
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < t; ++j)
            {
                for (unsigned int k = 0; k < get<1>(c.matrice[h])[i][j].size(); ++k)
                {
                    cout << get<1>(c.matrice[h])[i][j][k] << (k == get<1>(c.matrice[h])[i][j].size()-1 ? "" : " ");
                }
                cout << "\t\t";
            }
            cout << endl;
        }
    }
}

int adjacentVert (int i, int j, instance g)
{
    int somme = g.matrice[i][j];

    if (i > 0) somme += g.matrice[i-1][j];
    if (i < g.taille-1) somme += g.matrice[i+1][j];
    if (j > 0) somme += g.matrice[i][j-1];
    if (j < g.taille-1) somme += g.matrice[i][j+1];
     
    return somme;
}

void genereCalquesNV (calquesNV & c, instance g)
{
    int t = g.taille;

    vector <vector <float>> temp;
    vector <vector <vector <float>>> valeur;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (g.matrice[i][j]-1 >= 0 and adjacentVert(i, j, g) >= 0) temp.push_back({((float)adjacentVert(i, j, g) + (g.matrice[i][j]-1)*2)/2});
            else if (g.matrice[i][j]-1 >= 0) temp.push_back({(float)(((g.matrice[i][j]-1)*2) + 0)/2});
            else if (adjacentVert(i, j, g) >= 0) temp.push_back({(float)(adjacentVert(i, j, g) + 0)/2});
            else temp.push_back({});
        }
        valeur.push_back(temp);
        temp.clear();
    }

    c.matrice.push_back(make_tuple("NV", valeur));
    valeur.clear();
}

void genereCalques (calques & c, instance g)
{
    int t = g.taille;

    vector <vector <int>> temp;
    vector <vector <vector <int>>> valeur;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            g.matrice[i][j]-1 >= 0 ? temp.push_back({g.matrice[i][j]-1, (g.matrice[i][j]-1)*2}) : temp.push_back({});
        }
        valeur.push_back(temp);
        temp.clear();
    }

    c.matrice.push_back(make_tuple('N', valeur));
    valeur.clear();

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            adjacentVert(i, j, g) >= 0 ? temp.push_back({adjacentVert(i, j, g)}) : temp.push_back({});;
        }
        valeur.push_back(temp);
        temp.clear();
    }

    c.matrice.push_back(make_tuple('V', valeur));
    valeur.clear();

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            -g.matrice[i][j] > 0 ? temp.push_back({-g.matrice[i][j]}) : temp.push_back({});
        }
        valeur.push_back(temp);
        temp.clear();
    }

    c.matrice.push_back(make_tuple('R', valeur));
    valeur.clear();

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            temp.push_back({g.matrice[i][j], g.matrice[i][j]-g.penalite});
        }
        valeur.push_back(temp);
        temp.clear();
    }

    c.matrice.push_back(make_tuple('J', valeur));
    valeur.clear();

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            g.matrice[i][j] < 0 ? temp.push_back({g.matrice[i][j]}) : temp.push_back({});
        }
        valeur.push_back(temp);
        temp.clear();
    }

    c.matrice.push_back(make_tuple('O', valeur));
    valeur.clear();
}