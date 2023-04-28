#include <iostream>
#include <fstream>
#include <string>
//??
#include <cstdlib>
//Pour la génération de grille aléatoire
#include <ctime>
//Pour clear le terminal
#include <stdlib.h>
//Pour renvoyer des tuples
#include <tuple>

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

void initialisationInstance (string ficA, instance & g)
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
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !";
}

void suppressionInstance(instance & g)
{
    for (int i = 0; i < g.taille; ++i)
    for (int i = 0; i < g.taille; ++i)
        delete[] g.matrice[i];
    delete[] g.matrice;

    g.taille = 0;
    g.penalite = 0;
    g.matrice = nullptr;

    g.taille = 0;
    g.penalite = 0;
    g.matrice = nullptr;
}

void affichageInstance (instance g)
{
    int t = g.taille;
    cout << t << ' ' << g.penalite;

    for (int i = 0; i < t; ++i)
    {
        cout << endl;
        for (int j = 0; j < t; ++j)
            cout << g.matrice[i][j] << "\t";
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

void initialisationSolution (string ficA, solution & s, instance g)
{
    s.taille = g.taille;
    int t = s.taille;
    
    ifstream fichier(ficA);

    if(fichier)
    {
        s.matrice = new char * [t];

        for (int i = 0; i < t; ++i)
        {
            s.matrice[i] = new char [t];
            for (int j = 0; j < t; ++j)
            {
                fichier >> s.matrice[i][j];
            }
        }
    }
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !";
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
    //cout << endl << s.score << endl;
}

void suppressionSolution (solution & s)
{
    for (int i = 0; i <s.taille; ++i)
    for (int i = 0; i <s.taille; ++i)
        delete[] s.matrice[i];
    delete[] s.matrice;

    s.taille=0;
    s.score=0;
    s.matrice=nullptr;

    s.taille=0;
    s.score=0;
    s.matrice=nullptr;
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

bool pionOrthogonal (solution s, char l, int i, int j)
{
    // à gauche
    if (j > 0 && s.matrice[i][j-1] == l) return true;
    //à droite
    if (j < s.taille-1 && s.matrice[i][j+1] == l) return true;
    // au dessus
    if (i > 0 && s.matrice[i-1][j] == l) return true;
    //en dessous
    if (i < s.taille-1 && s.matrice[i+1][j] == l) return true;

    return false;
}

bool pionDiagonal (solution s, char l, int i, int j)
{
    //haut à gauche
    if (i > 0 && j > 0 && s.matrice[i-1][j-1] == l) return true;

    //haut à droite
    if (i > 0 && j < s.taille-1 && s.matrice[i-1][j+1] == l) return true;

    // bas à gauche
    if (i < s.taille-1 && j > 0 && s.matrice[i+1][j-1] == l) return true;

    //bas à droite
    if (i < s.taille-1 && j < s.taille-1 && s.matrice[i+1][j+1] == l) return true;

    return false;
}

int compteurPions (solution s, char l)
{
    int compteur = 0;

    for (int i = 0; i < s.taille; ++i)
    {
        for (int j = 0; j < s.taille; ++j)
        {
            if (s.matrice[i][j%s.taille] == l) ++compteur;
        }
    }

    return compteur;
}

//Decommenter si pionBleus utilise abs
/*int abs (int x)
{
    if(x >= 0) return x;
    return -x;
}*/

int pionsBleus (solution s, instance g)
{
    int d = 0; //Différence entre le nombre le nombre de case strictement négatif et le nombre de case strictement positif
    int t = s.taille; //Taille de la solution
    int nbNegatif = 0, nbPositif = 0; //Debug

    //Optimiser si petit différence (d)
    for (int i = 0; i < t; ++i)
        for (int j = 0; j < t; ++j)
        {
            int val = g.matrice[i][j];
            if (s.matrice[i][j] == 'B')
            {
                if (val > 0) --d, ++nbPositif; //Comptage d'une valeur strictement positive
                if (val < 0) ++d, ++nbNegatif; //Comptage d'une valeur strictement négative
            }
        }

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
                if (val > 0) --d, ++nbPositif; //Comptage d'une valeur strictement positive
                if (val < 0) ++d, ++nbNegatif; //Comptage d'une valeur strictement négative
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

    //cout << "Score pions bleus : " << (d > 0 ? -d*g.penalite : 0) << "\tParamètres : " << "nombres positifs=" << nbPositif << "\t, nombre négatifs=" << nbNegatif << "\t, difference (négatifs-positifs)=" << d << endl;
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
            j++;
            if (s.matrice[i][j] == 'R') pionRouge = true;
        }
        while (!pionRouge and j < t);

        if (!pionRouge)
        {
            j = 0;
            ++i;
        }
    }

    int valPion = g.matrice[i][j];

    //cout << "Score pion rouge : " << -valPion << ' ' << "\tParamètres : " << "pion trouvé à S[" << i << "][" << j << "] " << "\t, valeur du pion rouge=" << valPion << endl;
    return -valPion;
}

int pionsNoirs (solution s, instance g)
{
    int nbPionsNoirs = 0, score = 0;
    int t = g.taille;

    //Algorithme 1
    for (int i = 0; i < t; ++i)
        for (int j = 0; j < t; ++j)
        {
            if (s.matrice[i][j] == 'N')
            {
                score += g.matrice[i][j];
                ++nbPionsNoirs;
            }
            
        }

    //cout << "Score pions noirs : " << (nbPionsNoirs <= t ? 2*(score-nbPionsNoirs) : score-nbPionsNoirs) << "\tParamètres : " << "somme des pions (-1 compté)=" << score-nbPionsNoirs << "\t, doublé=" <<(nbPionsNoirs <= t ? true : false) << endl;
    if (nbPionsNoirs <= t) return 2*(score-nbPionsNoirs);
    return score-nbPionsNoirs;

    //Algorithme 2
    /*for (int i = 0; i < t; ++i)
        for (int j = 0; j < t; ++j)
        {
            if (s.matrice[i][j] == 'N') score += g.matrice[i][j] - 1;
        }

    int i = 0, j = 0;
    while (!(nbPionsNoirs > t) and i < t)
    {
        do
        {
            if (s.matrice[i][j++] == 'N') ++nbPionsNoirs;
        }
        while (!(nbPionsNoirs > t) and j < t);

        if(!(nbPionsNoirs > t))
        {
            ++i;
            j = 0;
        }
    }

    cout << "Score pions noirs : " << (nbPionsNoirs <= t ? 2*score : score) << "\tParamètres : " << "somme des pions (-1 compté)=" << score << "\t, recherche interrompu=" << (i == t and j == 0 ? false : true); !(i == t and j == 0) ? cout << " à S[" << i << "][" << j << "] " : cout << ""; cout << "\t, doublé=" <<(nbPionsNoirs <= t ? true : false) << endl;
    if (nbPionsNoirs <= t) return 2*score;
    return score;*/
}

//int si on return le score avec les penalités
tuple<int, int> pionsJaunes (solution s, instance g)
{
    int t = s.taille, nbPions = compteurPions(s, 'J'), score = 0, nbPionsIsoles = 0;

    int i = 0, j = 0;
    //Algorithme 1, calcule score et penalité en meme temps, pas de 2 en colonne, 1 en ligne
    while (!(nbPions == 0) and i < t)
    {
        while (!(nbPions == 0) and j < t)
        {
            //Si la case est jaune
            if (s.matrice[i][j] == 'J')
            {
                //Ajout du score
                score += g.matrice[i][j];
                //Verification des cases adjacentes orthogonalement ou (inclusif) en diagonale
                //Si true on ajoute un pion isolé et on passe 1 case, sinon on passe 2 cases (pas de jaune autour)
                if (!(pionOrthogonal(s, 'J', i, j) or pionDiagonal(s, 'J', i, j)))
                {
                    //Ajout d'un pion isolé
                    nbPionsIsoles++;
                    //Sinon on passe 0 case (+1, en dehors de la condition)
                }
                //Sinon on passe 1 case (+1, en dehors de la condition)
                else ++j;
                --nbPions;
            }
            //On passe 1 case
            j++;
        }
        ++i;
        j = 0;
    }

    //Algorithme 2, calcule du score et calcule du nombre de pion isolé séparés, pas de 2 en colonne et ligne
    /*while (!(nbPions == 0) and i < t)
    {
        while (!(nbPions == 0) and j < t)
        {
            //Si la case est jaune
            if (s.matrice[i][j] == 'J')
            {
                cout << "Jaune ! " << i << ' ' << j << ' ' << g.matrice[i][j] << endl;
                //Ajout du score
                score += g.matrice[i][j];
                --nbPions;
            }
            j++;
        }

        if (!(nbPions == 0))
        {
            i++;
            j = 0;
        }
    }

    cout << i << ' ' << j <<endl;

    nbPions = compteurPions(s, 'J'), i = 0, j = 0;
    
    while (!(nbPions == 0) and i < t)
    {
        // cout << "ligne " << i << endl;
        while (!(nbPions == 0) and j < t)
        {
            // cout << "-colonne " << j <<endl;
            //Si la case est jaune
            if (s.matrice[i][j] == 'J')
            {
                // cout << "--trouvé ! " << i <<' ' << endl;
                //Verification des cases adjacentes orthogonalement ou (inclusif) en diagonale
                //Si true on ajoute un pion isolé puis on passe 2 cases (on ignore les scores)
                if (!(pionOrthogonal(s, 'J', i, j) or pionDiagonal(s, 'J', i, j)))
                {
                    // cout << "---isolé" << " pion adjacent ortho=" << pionOrthogonal(s, 'J', i, j) << ' ' << " pion adjacent diago=" << pionDiagonal(s, 'J', i, j) << endl;
                    //Ajout d'un pion isolé
                    nbPionsIsoles++;
                    //Sinon on passe 2 case (+1, en dehors de la condition)
                    j++;
                }
                --nbPions;
            }
            j++;
        }
        i++;
        j = 0;
    }*/

    //Renvoie du score avec les pénalités appliqués
    // cout << "Score pions jaunes : " << score - nbPionsIsoles * g.penalite << "\tParamètres : " << "somme des pions=" << score << "\t, nombre de pion isolé=" << nbPionsIsoles << endl;
    // return score - nbPionsIsoles * g.penalite;

    //Revoie d'un tuple avec le score et le nombre de pénalité
    //cout << "Projection du score pions jaunes : " << score - nbPionsIsoles * g.penalite << "\tParamètres : " << "somme des pions=" << score << "\t, nombre de pion isolé(nombre de pénalité)=" << nbPionsIsoles << endl;
    return make_tuple(score, nbPionsIsoles);
}

tuple<int, int> pionsVerts (solution s, instance g)
{
    int score=0,penalite =0;

    int taille=g.taille;

    for (int i=0;i<taille;++i)
    {
        for (int j=0;j<taille;++j)
        {
            if (s.matrice[i][j]=='V')
            {
                score+=g.matrice[i][j]; //Ajout au score de la valeur de la case
                //Ajout au score des valeurs des cases adjacentes (orthogonales)
                if (j > 0) score+=g.matrice[i][j-1];
                if (j < s.taille-1) score+=g.matrice[i][j+1];
                if (i > 0) score+=g.matrice[i-1][j];
                if (i < s.taille-1) score+=g.matrice[i+1][j];

                //Incrémentation de la pénalité pour les cases orthogonales
                if (j > 0 && s.matrice[i][j-1] == 'V') penalite+=1;
                if (j < s.taille-1 && s.matrice[i][j+1] == 'V') penalite+=1;
                if (i > 0 && s.matrice[i-1][j] == 'V') penalite+=1;
                if (i < s.taille-1 && s.matrice[i+1][j] == 'V') penalite+=1;

                //Incrémentation de la pénalité pour les cases diagonales
                if (i > 0 && j > 0 && s.matrice[i-1][j-1] == 'V')penalite+=1;
                if (i > 0 && j < s.taille-1 && s.matrice[i-1][j+1] == 'V')penalite+=1;
                if (i < s.taille-1 && j > 0 && s.matrice[i+1][j-1] == 'V')penalite+=1;
                if (i < s.taille-1 && j < s.taille-1 && s.matrice[i+1][j+1] == 'V')penalite+=1;
            }
        }
    }
    penalite = (int)penalite/2;
    //cout<<"Debug score vert, score :"<<score<<" pénalité : "<<penalite<<endl;
    return make_tuple(score,penalite);
}
void calculeScore (solution & s, instance g)
{
    int score = 0;
    int nbPenalite = 0;
    //A supprimer si on utilise pas les tuples
    int tempScore = 0,tempNbPenalite = 0;

    nbPenalite += pionsBleus (s, g); //Pion bleus = pénalité seulement, score = 0
    score += pionRouge (s, g); //Pion rouge = score seulement, aucune pénalité
    score += pionsNoirs (s, g); //Pion noirs = score seulement, aucune pénalité
    // nbPenalite += pionsOranges(s, g); //Pion bleus = pénalité seulement, score = 0
    //A modifier si on utilise pas les tuples
    tie(tempScore, tempNbPenalite) = pionsJaunes(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    tempScore=0;tempNbPenalite=0;
    tie(tempScore, tempNbPenalite) = pionsVerts(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;


    cout << "debug calculeScore : " << "nombre de pénalités = " << nbPenalite << ' ' << "valeur des pénalités = " << g.penalite << endl;
    s.score = score - (nbPenalite * g.penalite);
}

int main ()
{
    //system ("CLS");
    string repInstance = "Instances/probleme_4_a.txt";
    string repSolution = "Solutions/solution_1.txt";
    instance a ;
    solution b;

    initialisationInstance(repInstance, a);
    affichageInstance(a);
    // genereSolutionAlea(b, a);
    initialisationSolution(repSolution, b, a);
    calculeScore(b, a);
    affichageSolution(b);
    //valide(b) == 1 ? cout << endl << "Solution valide." << endl : cout << endl << "Solution invalide." << endl;
    
    // for (int i=0;i<b.taille;++i)
    // {
    //     for (int j=0;j<b.taille;++j)
    //     {
    //         cout<<"Solution orthogonal i ="<<i<<" j= "<<j<<" "<<pion_orthogonal(b,'J',i,j)<<endl;
    //     }
    // }
    cout<<"FIN DE L'EXECUTION";
    //suppressionInstance(a);
    //suppressionSolution(b);
    
}
