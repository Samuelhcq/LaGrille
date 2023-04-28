#include <iostream>
#include <string>
//Lecture de fichier
#include <fstream>
//Génération de grille aléatoire
#include <ctime>
//Netoyer le terminal
#include <stdlib.h>
//Renvoie de tuple
#include <tuple>

//Déclaration des identificateurs
using namespace std;

//Déclaration des structures de données d'entrée et de sortie
struct instance
{
    int taille, penalite;
    int ** matrice;
};

struct solution
{
    int taille, score;
    char ** matrice;
};

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

        //Création première dimension de la matrice grille (allocation)
        g.matrice = new int * [t];

        //Assignation de la grille
        for (int i = 0; i < t; ++i)
        {
            //Création deuxième dimension de la matrice grille (allocation)
            g.matrice[i] = new int [t];
            for (int j = 0; j < t; ++j)
            {
                //Lecture du nombre (avec comme séparateur ' ')
                fichier >> g.matrice[i][j];
            }
        }
    }
    //Message d'erreur
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !" << endl;
}

//Suppréssion de la grille (fichier d'entrée)
void suppressionInstance (instance & g)
{
    //Suppréssion de la grille
    for (int i = 0; i < g.taille; ++i)
    {
        //Suppréssion deuxième dimension de la matrice grille (désallocation)
        delete[] g.matrice[i];
    }
    //Suppréssion première dimension de la matrice grille (désallocation)
    delete[] g.matrice;

    //Fin de la suppréssion du fichier
    g.matrice = nullptr;
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

//Vérification de la validitée de la solution
bool valide (solution s)
{
    //Création de la varible nombre pion rouge ('nbPionRouge'), d'incrémentations ('i' et 'j') et taille ('t')
    int nbPionRouge = 0, i = 0, j = 0, t = s.taille;

    //Passage en revue de la solution, pour compter le nombre de pion rouge
    //Arrêt du passage en revue dès que le nombre de pion dépasse 2
    while (nbPionRouge < 2 and i < t)
    {
        do
        {
            //Si pion rouge, incrémentation du nombre de pion rouge
            if (s.matrice[i][j++] == 'R') nbPionRouge++;
        }
        while (nbPionRouge < 2 and j < t);

        //Débuggage (la condition)
        // if (nbPionRouge < 2)
        // {
            j = 0;
            i++;
        // }
    }
    //Débuggage
    //cout << "Débuggage fonction valide() : \t" << "fin de recherche de la validité à S[" << i << "][" << j << "]" << ",\t nombre de pion rouge=" << nbPionRouge << endl;

    //Si le nombre de pion rouge est égal à 1 alors la solution est valdie
    return nbPionRouge == 1;
}

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

    //Création première dimension de la matrice solution (allocation)
    s.matrice = new char * [t];
    //Création deuxième dimension de la matrice solution (allocation)
    //Création effectué en dehors de la boucle par soucis d'optimisation
    for (int i = 0; i < t; ++i)
    {
        s.matrice[i] = new char [t]; 
    }

    //Génaration de la solution
    //Temps que la solution n'est pas valide on en génère
    do
    {
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < t; ++j)
            {
                //Assignation du pion aléatoirement parmis la liste des pions
                s.matrice[i][j] = lettres[rand() % 6];
            }
        }
        //Débuggage
        //cout << "Débuggage fonction genereSolutionAlea() : \t" << "valide=" << (valide(s) == 1 ? true : false) << endl;
    } while (!valide(s));
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
        //Création première dimension de la matrice grille (allocation)
        s.matrice = new char * [t];

        //Assignation de la solution
        for (int i = 0; i < t; ++i)
        {
            //Création deuxième dimension de la matrice grille (allocation)
            s.matrice[i] = new char [t];
            for (int j = 0; j < t; ++j)
            {
                //Lecture du caractère (avec comme séparateur ' ')
                fichier >> s.matrice[i][j];
            }
        }
    }
    //Message d'erreur
    else cerr << "Erreur : le fichier '" << ficA << "' ne peut pas être lu !" << endl;

    //Débuggage
    //cout << "Débuggage fonction lectureSolution() : \t" << "valide=" << (valide(s) == 1 ? true : false) << endl;
}

//Saisie d'une solution manuellement
void saisieSolution (solution & s, instance g)
{
    //Assignation de la variable taille
    int t = g.taille;
    s.taille = t;
   
    //Création première dimension de la matrice solution (allocation)
    s.matrice = new char * [t];
    //Création deuxième dimension de la matrice solution (allocation)
    for (int i = 0; i < t; ++i)
    {
        s.matrice[i] = new char [t];
    }

    //Saisie de la matrice solution
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            //Assginement du pion
            cin >> s.matrice[i][j];
        }
    }
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

//Suppréssion de la solution (fichier de sortie)
void suppressionSolution (solution & s)
{
    //Suppréssion de la solution
    for (int i = 0; i < s.taille; ++i)
    {
        //Suppréssion deuxième dimension de la matrice solution (désallocation)
        delete[] s.matrice[i];
    }
    //Suppréssion première dimension de la matrice solution (désallocation)
    delete[] s.matrice;

    //Fin de la suppréssion du fichier
    s.matrice = nullptr;
}

//Vérifie les pions adjacents orthogonalements
bool pionOrthogonal (solution s, char l, int i, int j)
{
    //Si pion adjacent orthogonalement, retourne vrai
    if (j > 0 && s.matrice[i][j-1] == l) return true; //A gauche
    if (j < s.taille-1 && s.matrice[i][j+1] == l) return true; //A droite
    if (i > 0 && s.matrice[i-1][j] == l) return true; //En dessous
    if (i < s.taille-1 && s.matrice[i+1][j] == l) return true; //Au dessus

    //Sinon retourne faux
    return false;
}

//Vérifie les pions adjacents en diagonale
bool pionDiagonale (solution s, char l, int i, int j)
{
    //Si pion adjacent en diagonale, retourne vrai
    if (i > 0 && j > 0 && s.matrice[i-1][j-1] == l) return true; //En bas à gauche
    if (i > 0 && j < s.taille-1 && s.matrice[i-1][j+1] == l) return true; //En bas à droite
    if (i < s.taille-1 && j > 0 && s.matrice[i+1][j-1] == l) return true; //En haut à gauche
    if (i < s.taille-1 && j < s.taille-1 && s.matrice[i+1][j+1] == l) return true; //En haut à droite
    
    //Sinon retourne faux
    return false;
}

//Compte le nombre d'une certaine couleur de pion
int compteurPions (solution s, char l)
{
    //Création de la variable du nombre de pion
    int compteur = 0;

    //Passage en revue de la solution, pour compter le nombre de pion de la couleur indiquée
    for (int i = 0; i < s.taille; ++i)
    {
        for (int j = 0; j < s.taille; ++j)
        {
            //Si correspondance, on incrémente 'compteur' de 1
            if (s.matrice[i][j%s.taille] == l) compteur++;
        }
    }

    //Retourne le nombre de pion de la couleur indiquée trouvé
    return compteur;
}

//Calcule la valeur absolue (utilsé dans la fonction pionsBleus)
int abs (int x)
{
    if(x >= 0) return x;
    return -x;
}

//Calcule le score des pions bleus
int pionsBleus (solution s, instance g)
{
    //Création de la variable différence entre le nombre de case strictement négatif et le nombre de case strictement positif ('d'), valeur ('val') et taille ('t')
    int d = 0, val, t = s.taille;
    //Débuggage
    // int nbNegatif = 0, nbPositif = 0;

    //Optimiser si petite différence (avec 'd' comme référence)

    //Passage en revue de la solution, pour calculer la différence 'd' (des pions bleus)
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            //Assignation de la valeur du pion
            val = g.matrice[i][j];

            //Si pion bleu, modification de la différence
            if (s.matrice[i][j] == 'B')
            {
                //Nombre sctrictement positif, décrémentation de la différence
                if (val > 0)
                {
                    d--;
                    //Débuggage
                    // nbPositif++;
                }
                //Nombre sctrictement négatif, incrémentation de la différence
                if (val < 0) 
                {   
                    d++;
                    //Débuggage
                    // nbNegatif++;
                }
            }
        }
    }
    /*
    //Optimiser si grande différence (avec 'd' comme référence)
    
    //Création des variables d'incrémentations ('i' et 'j'), de la variable case restante ('c') et valeur ('val') 
    int i = 0, j = 0, c = t*t+1, val;

    //Passage en revue de la solution, pour calculer la différence 'd' (des pions bleus)
    //Arret du passage en revue dès que la différence est trop grande pour être rattrapée
    while (!(abs(d) > c) and i < t)
    {
        do
        {
            //Assignation de la valeur du pion
            val = g.matrice[i][j];
            
            //Si pion bleu, modification de la différence
            if (s.matrice[i][j] == 'B')
            {
                //Nombre sctrictement positif, décrémentation de la différence
                if (val > 0)
                {
                    d--;
                    //Débuggage
                    // nbPositif++;
                }
                //Nombre sctrictement négatif, incrémentation de la différence
                if (val < 0) 
                {   
                    d++;
                    //Débuggage
                    // nbNegatif++;
                }
            }

            //Décrémentation des cases restantes
            c--;
        }
        while (!(abs(d) > c) and j < t);

        //Débuggage (la condition)
        // if (!(abs(d) > c))
        // {
             j = 0;
             ++i;
        // }
    }
    */

    //Débuggage algorithme 1
    // cout << "Score pions bleus : " << (d > 0 ? -d*g.penalite : 0) << "\tParamètres : " << "nombres positifs=" << nbPositif << "\t, nombre négatifs=" << nbNegatif << "\t, difference (négatifs-positifs)=" << d << endl;
    //Débuggage algorithme 2
    // cout << "Score pions bleus : " << (d > 0 ? -d*g.penalite : 0) << "\tParamètres : " << "nombres positifs=" << nbPositif << "\t, nombre négatifs=" << nbNegatif << "\t, difference (négatifs-positifs)=" << d << "\t, arrêt du passage en revue à G[" << i << "][" << j << "]" << endl;
    
    //Si la différence est strictement positive il y a 'd' pénalités
    if (d > 0) return d;
    //Sinon il y a 0 pénalité
    return 0;
}

//Calcule le score du pion rouge
//La solution doit être valide
int pionRouge (solution s, instance g)
{
    //Création des variables d'incrémentations ('i' et 'j') et de la variable taille (optimisation)
    int i = 0, j = 0, t = s.taille;
    //Création d'un boolean pour trouver le pion rouge
    bool pionRouge = false;

    //Passage en revue de la solution, pour trouver le pion (rouge)
    //Arret du passage en revue dès que le pion est trouvé (il est unique)
    while (!pionRouge and i < t)
    {
        do
        {
            //Si pion rouge, on arrêt le passage en revue
            if (s.matrice[i][j++] == 'R') /*Passage du bolean à vrai*/ pionRouge = true;
        }
        while (!pionRouge and j < t);

        //Débuggage (la condition)
        if (!pionRouge)
        {
            j = 0;
            ++i;
        }
    }

    //-1 pour corriger le j++ de sortie de boucle
    j--;

    //Création de la variable de la valeur du pion rouge
    int valPion = g.matrice[i][j];

    //Débuggage
    // cout << "Score pion rouge : " << -valPion << ' ' << "\tParamètres : " << "pion trouvé à S[" << i << "][" << j << "] " << "\t, valeur du pion rouge=" << valPion << endl;
    
    //On retourne l'opposé de la valeur du pion rouge
    return -valPion;
}

//Calcule le score des pions noirs
int pionsNoirs (solution s, instance g)
{
    //Création de la variable nombre de pion noir ('nbPionNoir'), score ('score'), taille ('t')
    int nbPionNoir = 0, score = 0, t = s.taille;

    //Premier algorithme
    //Calcule du score (pions noirs) et comptage du nombre de pion (pions noirs)

    //Passage en revue de la solution
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            //Si pion noir, on calcule le score et on incrémente le nombre de pion noir
            if (s.matrice[i][j] == 'N')
            {
                //Calcule du score (sans le -1)
                score += g.matrice[i][j];
                //Incrémentation du nombre de pion noir
                nbPionNoir++;
            }
        }
    }
        

    //Débuggage algorithme 1
    // cout << "Score pions noirs : " << (nbPionNoir <= t ? 2*(score-nbPionNoir) : score-nbPionNoir) << "\tParamètres : " << "somme des pions (-1 compté)=" << score-nbPionNoir << "\t, doublé=" <<(nbPionNoir <= t ? true : false) << endl;
    
    //Retour de fonction algorithme 1
    //Si nombre de pion noir suppérieur à la taille ('t'), on retourne le score doublé (clacule du -1)
    if (nbPionNoir <= t) return 2*(score-nbPionNoir);
    //Sinon on retourne le score (calcule du -1)
    return score-nbPionNoir;

    //Deuxième algorithme
    //Calcule du score (pions noirs), puis comptage du nombre de pion (pions noirs)
    /*
    //Passage en revue de la solution
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            //Si pion noir, on calcule le score
            if (s.matrice[i][j] == 'N') score += g.matrice[i][j] - 1; //-1 directement calculé
        }
    }

    //Création des variables d'incrémentation
    int i = 0, j = 0;

    //Passage en revue de la solution, pour compter le nombre de pion (noir)
    //Arrêt du passage en revue dès que le nombre de pion noir suppérieur à la taille ('t')
    while (!(nbPionNoir > t) and i < t)
    {
        do
        {
            //Si pion noir, incrémentation du nombre de pion noir
            if (s.matrice[i][j++] == 'N') nbPionNoir++;
        }
        while (!(nbPionNoir > t) and j < t);

        //Débuggage (la condition)
        if(!(nbPionNoir > t))
        {
            i++;
            j = 0;
        }
    }

    //Débuggage algorithme 2
    // cout << "Score pions noirs : " << (nbPionNoir <= t ? 2*score : score) << "\tParamètres : " << "somme des pions (-1 compté)=" << score << "\t, recherche interrompu=" << (i == t and j == 0 ? false : true); !(i == t and j == 0) ? cout << " à S[" << i << "][" << j << "] " : cout << ""; cout << "\t, doublé=" <<(nbPionNoir <= t ? true : false) << endl;
    
    //Retour de fonction algorithme 2
    //Si nombre de pion noir suppérieur à la taille ('t'), on retourne le score doublé
    if (nbPionNoir <= t) return 2*score;
    //Sinon on retourne le score
    return score;
    */
}

//Calcule le score des pions jaunes
//Utilise les tuples (avec le module 'tuple')
tuple<int, int> pionsJaunes (solution s, instance g)
{
    //Création de la variable score ('score'), nombre de pion jaune isolé ('nbPionsIsole') et taille ('t')
    int score = 0, nbPionsIsole = 0, t = s.taille;

    //Première algorithme
    //Calcule du score (pions jaunes) et comptage du nombre de pion isolé (jaune), avec un pas de 1 ou 2 en colonne
    
    //Passage en revue de la solution 
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            //Si pion jaune, on calcule le score et on incrémente le nombre de pion isolé
            if (s.matrice[i][j] == 'J')
            {
                //Calcule du score
                score += g.matrice[i][j];
                //Si pion isolé, on incrémente le nombre de pion isolé et on passe 2 cases
                if (!(pionOrthogonal(s, 'J', i, j) or pionDiagonale(s, 'J', i, j)))
                {
                    //Incrémentation du nombre de pion isolé
                    nbPionsIsole++;
                    //Passe d'une case (la deuxième étant passé avec la boucle for)
                    //Si pion isolé, il est inutile de vérifier si il y a un pion jaune autour
                    j++;
                }
            }
        }
    }
        

    //Deuxième algorithme
    //Calculer d'abord le score, puis les pénalités avec un pas de 2 en colonne ET en ligne
    
    //Sans utiliser les tuples
    /*
    //Débuggage
    cout << "Score pions jaunes : " << score - nbPionsIsole * g.penalite << "\tParamètres : " << "somme des pions=" << score << "\t, nombre de pion isolé=" << nbPionsIsole << endl;
    
    //Retourne le score avec les pénalités calculer directement
    return score - nbPionsIsole * g.penalite;
    */

    //En utilisant les tuples
    //Débuggage
    // cout << "Projection du score pions jaunes : " << score - nbPionsIsole * g.penalite << "\tParamètres : " << "somme des pions=" << score << "\t, nombre de pion isolé(nombre de pénalité)=" << nbPionsIsole << endl;
    
    //Retourne le score (sans pénalité) et le nombre de pénalité
    return make_tuple(score, nbPionsIsole);
}

//Calcule le score des pions verts
//Utilise les tuples (avec le module 'tuple')
tuple<int, int> pionsVerts (solution s, instance g)
{
    //Création de la variable score ('score'), nombre de paire verte ('nbPaire') et taille ('t')
    int score = 0, nbPaire = 0, t = s.taille;

    //Passage en revue de la solution
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            //Si pion vert, on calcule le score et on compte le nombre de paire
            if (s.matrice[i][j] == 'V')
            {
                //Calcule du score
                //Ajout de la valeur de la case
                score += g.matrice[i][j];
                //Ajout de la valeur des cases adjecentes orthogonalement
                if (j > 0) score += g.matrice[i][j-1]; //En dessous
                if (j < s.taille-1) score += g.matrice[i][j+1]; //Au dessus
                if (i > 0) score += g.matrice[i-1][j]; //A gauche
                if (i < s.taille-1) score += g.matrice[i+1][j]; //A droite

                //Calcule du nombre de paire
                //Ajout du nombre de paire orthogonalement
                if (j > 0 && s.matrice[i][j-1] == 'V') nbPaire++; //En dessous
                if (j < s.taille-1 && s.matrice[i][j+1] == 'V') nbPaire++; //Au dessus
                if (i > 0 && s.matrice[i-1][j] == 'V') nbPaire++; //A gauche
                if (i < s.taille-1 && s.matrice[i+1][j] == 'V') nbPaire++; //A droite
                //Ajout du nombre de paire en diagonale
                if (i > 0 && j > 0 && s.matrice[i-1][j-1] == 'V') nbPaire++; //En bas à gauche
                if (i > 0 && j < s.taille-1 && s.matrice[i-1][j+1] == 'V') nbPaire++; //En bas à droite
                if (i < s.taille-1 && j > 0 && s.matrice[i+1][j-1] == 'V') nbPaire++; //En haut à gauche
                if (i < s.taille-1 && j < s.taille-1 && s.matrice[i+1][j+1] == 'V') nbPaire++; //En haut à droite
            }
        }
    }
        

    //Suppréssion des doublons de paire
    //(int) assure la nature du nombre de paire (un entier)
    nbPaire = (int)nbPaire/2;

    //Sans utiliser les tuples
    /*
    //Débuggage
    cout << "Score pions verts : " << score - nbPaire * g.penalite << "\tParamètres : " << "somme des pions=" << score << "\t, nombre de paire(nombre de pénalité)=" << nbPaire << endl;    
    
    //Retourne le score avec les pénalités calculer directement
    return score - nbPaire * g.penalite;
    */

    //En utilisant les tuples
    //Débuggage
    // cout << "Projection du score pions verts : " << score - nbPaire * g.penalite << "\tParamètres : " << "somme des pions=" << score << "\t, nombre de paire(nombre de pénalité)=" << nbPaire << endl;    
    
    //Retourne le score (sans pénalité) et le nombre de pénalité
    return make_tuple(score, nbPaire);
}

//Calcule du score final
void calculeScore (solution & s, instance g)
{
    //Création de la variable score ('score') et nombre de pénalité ('nbPenalite')
    int score = 0, nbPenalite = 0;
    //Création de variables temporaire score ('tempScore') et pénalité ('tempNbPenalite')
    //A supprimer si les tuples ne sont pas utilisés
    int tempScore = 0, tempNbPenalite = 0;

    //Calcule du score
    //Score des pions bleus, nombre de pénalité seulement (score = 0)
    nbPenalite += pionsBleus (s, g);
    //Score du pion rouge, score seulement (nombre de pénalité = 0)
    score += pionRouge (s, g);
    //Score des pions noirs, score seulement (nombre de pénalité = 0)
    score += pionsNoirs (s, g);
    //Score des pions jaunes, score et nombre de pénalité
    //Utilisation des tuples
    tie(tempScore, tempNbPenalite) = pionsJaunes(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    //Score des pions verts, score et nombre de pénalité
    //Utilisation des tuples
    tie(tempScore, tempNbPenalite) = pionsVerts(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    //Score des pions oranges, nombre de pénalité seulement (score = 0)

    //Débuggage
    // cout << "Débuggage fonction calculeScore() : \t" << "score sans penalité=" << score << "\t, nombre de pénalité=" << nbPenalite << endl;

    //Assignation du score final
    s.score = score - (nbPenalite * g.penalite);
}

int main ()
{
    //Nettoyage du termnial (affichage propre)
    system ("CLS");
    
    //Chemin d'accès des fichiers d'entrées
    //Chemin de l'instance ('repInstance') et d'une solution ('repSolution')
    //Chemin d'une solution utile pour la fonction lectureSolution()
    string repInstance = "Instances/exemple_1.txt", repSolution = "Solutions/solution_2.txt";

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
    genereSolutionAlea(b, a);
    //Initialisation d'un fichier
    // lectureSolution(repSolution, b, a);
    //Initialisation par la saisie
    // saisieSolution(b, a);

    //Calcule du score de la solution
    calculeScore(b, a);
    //Affichage de la solution avec le score
    affichageSolution(b);

    //Débuggage
    cout << endl << "Fin de l'éxecution." << endl;

    //Suppréssion de la grille
    // suppressionInstance(a);
    //Suppréssion de la solution
    // suppressionSolution(b);
}
