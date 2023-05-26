La Grille
=============

Comment télécharger l'archive ?
-----------------------------------
Pour lancer le programme, suivez les instructions suivantes :
1. Télécharger le .zip du projet
2. Ouvrir un terminal où le CMakeLists.txt se trouve
3. Saisissez la commande ```mkdir build && cd build```, puis ```cmake``` et ```make```

L'executable à du être créé sous le nom de *lagrille*

Comment choisir l'instance et lancer l'algorithme ?
-----------------------------------
Après la création de votre executable (cf . *lagrille*) vous pouvez maintenant choisir sur quelle grille lancer l'algorithme mais aussi où va aller la solution généré !
### Choisir l'instance
1. Ouvrir le fichier ```main.cpp``` dans le dossier ```programme```
2. Modifier le chemin relatif du fichier en question dans la variable ```cheminInstance``` (ligne 34)

### Choisir où va aller le fichier de sortie
Dans le meme fichier (ie. ```main.cpp```) vous pouvez modifier le chemin relatif et nom de fichier de sortie dans la variable ```cheminSortie``` (par defaut ```../sortie.txt```)
