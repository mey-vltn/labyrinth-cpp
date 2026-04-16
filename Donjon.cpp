#include "Donjon.h"


void Donjon::afficher () {
    
    // contour
    cout << '+' ;
    for (int i = 0 ; i < grille.size() ; i++) {
        cout << '-' ;
    }
    cout << '+' ;


    for (int i = 0 ; i < grille.size() ; i++) {
        for (int j = 0 ; j < grille[i].size() ; j++)  {

            if (i == 0 || i == (grille.size() - 1)) {
                cout << '|' ;
            }

            Case* c = grille[i][j] ;

            if (c != nullptr) {
                cout << c->afficher() ;
            } 
        }
    }

    // contour
    cout << '+' ;
    for (int i = 0 ; i < grille.size() ; i++) {
        cout << '-' ;
    }
    cout << '+' ;

    cout << endl ;
}

