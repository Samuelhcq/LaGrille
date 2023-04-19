#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
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

void suppressionInstance (instance & g)
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
        while (r < 2 and j < 4);

        if (r < 2)
        {
            j = 0;
            ++i;
        }
    }
    // cout << endl << r << ' ' << i << ' ' << j << endl;
    return r == 1;
}

void genereSolution (solution & s, instance g)
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
    // cout << endl << s.score << endl;
}

void suppressionSolution (solution & s)
{
    for (int i = 0; i < s.taille; ++i)
        delete[] s.matrice[i];
    delete[] s.matrice;
}

void saisieSolution(solution & s, instance g)
{
   int t = g.taille;
   s.taille = t;
   
   s.matrice = new char * [t];
   for (int i = 0; i < t; ++i) s.matrice[i] = new char [t];

   for (int i = 0; i < t; ++i)
   {
       for (int j = 0; j < t; ++j)
       {
           cin >> s.matrice[i][j];
       }
   }
}

bool pion_orthogonal(solution s,char l,int i,int j)
{
    if (i==0 and j==0) return (s.matrice[i+1][j]==l or s.matrice[i][j+1]==l);
    if(i==0 and j==s.taille-1) return (s.matrice[i][j-1]==l or s.matrice[i+1][j]==l);
    if(i==s.taille-1 and j==0) return(s.matrice[i-1][j]==l or s.matrice[i][j+1]==l);
    if(i==s.taille-1 and j==s.taille-1)return (s.matrice[i][j-1]==l or s.matrice[i-1][j]==l);

    /*   
    if (i>0 and i<s.taille) //Test bord de ligne
    {
        cout<<"test";
        if (j>0 and j <s.taille) //Test bord de colonne
        {
            return (s.matrice[i-1][j]==l or s.matrice[i+1][j]==l or s.matrice[i][j-1]==l or s.matrice[i][j+1]==l);
        }
    }

    if (j-1==-1) //Première colonne
    {
        if(i-1==-1) //Première ligne
        {
            return (s.matrice[i][j+1]==l or s.matrice[i+1][j]==l);
        }
        if(i+1>=s.taille)//Dernière ligne
        {
            return (s.matrice[i-1][j]==l or s.matrice[i][j+1]==l);
        }
        return (s.matrice[i-1][j]==l or s.matrice[i+1][j] or s.matrice[i][j+1]==l);
    }

    if (j+1>s.taille) //Dernière colonne
    {
        cout<<"test";   
        if(i-1==-1) //Première ligne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i+1][j]==l);
        }
        if(i+1>=s.taille) //Dernière ligne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i-1][j]==l);
        }
        return(s.matrice[i-1][j]==l or s.matrice[i+1][j]==l or s.matrice[i][j-1]==l);
    }

    if (i-1==-1) //Première ligne
    {
        if (j-1==-1) //Première colonne
        {
            return (s.matrice[i][j+1]==l or s.matrice[i+1][j]==l);
        }
        if (j+1>=s.taille) //Dernière colonne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i+1][j]==l);
        }
    }

    if (i+1>=s.taille) //Dernière ligne
    {
        if (j-1==-1) // Première colonne
        {
            return (s.matrice[i-1][j]==l or s.matrice[i][j+1]==l);
        }
        if (j+1>=s.taille) // Dernière colonne
        {
            return (s.matrice[i][j-1]==l or s.matrice[i-1][j]==l);
        }
    }
    */
    return 0;
}

bool pion_diagonal(solution s,char l,int i,int j)
{
    return false;
}

int compteur_pion(solution s,char l)
{
    return false;
}
// int calculeScore (instance g, solution s)
// {
//     int scoreTotal=0,penalite=0;  
//     for (int i=0;i<s.taille;++i)
//     {
//         for (int j=0;j<s.taille;++j)
//         {
//             int val_case=g.matrice[i][j];
//             char car_case=s.matrice[i][j];
//             {             
//                 if (car_case='J') //Jaune
//                 {

//                 }
//                 if(car_case='V') //Vert
//                 {

//                 }
//                 if(car_case='N') //Noir
//                 {
                    
//                 }
//                 if(car_case='B') //Bleu
//                 {
                    
//                 }
//                 if(car_case='O') //Orange
//                 {N
                    
//                 }
//                 if(car_case='R') //Rouge
//                 {
                    
//                 }
//             }
//         }
//     }
// }

int main ()
{
    string repertoire = "Instances/test.txt";
    instance a;
    solution b;

    initialisationInstance(repertoire, a);
    saisieSolution(b,a);
    affichageSolution(b);
    for (int i=0;i<b.taille;++i)
    {
        for (int j=0;j<b.taille;++j)
        {
            cout<<"Solution orthogonal i ="<<i<<" j= "<<j<<" "<<pion_orthogonal(b,'J',i,j)<<endl;
        }
    }
    suppressionInstance(a);
    suppressionSolution(b);
}
