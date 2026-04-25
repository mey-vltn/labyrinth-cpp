#ifndef DONJON_H
#define DONJON_H

#include <vector>
#include <iostream>

#include "Case.h" 

using namespace std ;  

class Donjon {
    
    private:
        vector<vector<Case*>> grille ;
        int hauteur ;
        int largeur ;


    public :
    
        Case* getCase (int x, int y) const ;

        void generer (int largeur, int hauteur) ;
        void genererLabyrinthe(int x, int y);
        void placerElements();
        void afficher () ;
        vector<pair<int,int>> trouverChemin () ;

        void remplacerCase(int x, int y, Case* newCase) ;
        bool estDansBornes (int x, int y) const ;
        bool estFranchissable (int x, int y) const ;
};


#endif 