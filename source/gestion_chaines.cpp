//Comparaison de chaînes

#include <iostream>

#include "../header/gestion_chaines.h"

using namespace std;

int comparaison_chaines(const char *chaine1, const char *chaine2) {
    int i = 0;
    while (chaine1[i] != '\0' && chaine2[i] != '\0') { //Vérifie qu'à chaque tour de boucle les deux lettres à comparer diffèrent de \0
        //Valeurs entières des lettres selon le code ASCII
        int a = (int)chaine1[i];
        int b = (int)chaine2[i];

        //Comparer directement si les lettres ont la même casse
        if ((a <= 90 && b <= 90) || (a >= 97 && b >= 97)) {
            if (a < b) {
                return -1;
            }
            else if (a > b) {
                return 1;
            }
            else {
                i+=1;
            }
        }

        //Au cas où les lettres sont de casse différente, on les ramêne à la même casse pour la comparaison
        else {
            if (a <= 90 && b >= 97) {
                b-=32;
            }
            else if (a >= 97 && b <= 90) {
                a-=32;
            }

            if (a < b) {
                return -1;
            }
            else if (a > b) {
                return 1;
            }
            else {
                i+=1;
            }
        }
    }

    //Vérification au cas où l'on sort de la boucle précédente sans résultat
    if (chaine1[i] == '\0' && chaine2[i] != '\0') {
        return -1;
    }
    else if (chaine1[i] != '\0' && chaine2[i] == '\0') {
        return 1;
    }
    else {
        return 0;
    }
}
