La Grille
=============

Comment télécharger l'archive ?
-----------------------------------
Pour lancer le programme, suivez les instructions suivantes :
1. Télécharger le .zip du projet
2. Ouvrir un terminal où le CMakeLists.txt se trouve
3. Saisissez la commande ```mkdir build && cd build``` , puis ```cmake``` et ```make```

L'executable à du être créé sous le nom de *lagrille*.out

Comment lancer l'algorithme ?
-----------------------------------
Après la création de votre executable (cf . *lagrille*.out) vous pouvez maintenant choisir sur quelle grille lancer l'algorithme mais aussi où va aller la solution généré !
1. Ouvrir un terminal dans ```build```
2. Lancer la commande ```./lagrille``` suivis des instance et des sortis des solutions que vous souhaitez calculer

### Exemple
>```console
>.\lagrille "../../instances/competition_01.txt" "../../sortie_01.txt" 
>```
>Calcule la solution de l'instance ```competition_01.txt``` situé dans ```../../instances/```, puis l'écrit dans le fichier texte ```sortie_01.txt``` situé dans ```../../```

>```console
>.\lagrille "../../instances/competition_01.txt" "../../sortie_01.txt" "../../instances/competition_02.txt" "../../sortie_02.txt" "../../instances/competition_03.txt" "../..>/sortie_03.txt" "../../instances/competition_04.txt" "../../sortie_04.txt" "../../instances/competition_05.txt" "../../sortie_05.txt" "../../instances/competition_06.txt" >"../../sortie_06.txt"  "../../instances/competition_07.txt" "../../sortie_07.txt" "../../instances/competition_08.txt" "../../sortie_08.txt" "../../instances>/competition_09.txt" "../../sortie_09.txt" "../../instances/competition_10.txt" "../../sortie_10.txt" "../../instances/competition_11.txt" "../../sortie_11.txt" "../..>/instances/competition_12.txt" "../../sortie_12.txt"
>```
>Calcule la solution des 12 intances de compétition
