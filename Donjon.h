#ifndef DONJON_H
#define DONJON_H

#include <vector>
#include <iostream>

#include "Case.h" 

using namespace std ;  

template <typename Case>
class Donjon {
    
    private:
        vector<vector<Case*>> grille ;

    public :
        void generer (int largeur, int hauteur) ;
        void afficher () ;
        vector<pair<int,int>> trouverChemin (/* ... */);
};


#endif 