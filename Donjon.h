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
        pair<int, int> sortie;


    public :
    
        Case* getCase (int x, int y) const ;

        void generer (int largeur, int hauteur) ;
        void genererLabyrinthe(int x, int y);
        void placerElements();
        void afficher (int ax, int ay) ;
        vector<pair<int,int>> trouverChemin (vector<vector<Case*>> grille , pair<int,int> depart, pair<int,int> arrivee) ;
        vector<pair<int,int>> reconstruireChemin(vector<vector<pair<int,int>>>& parent, pair<int,int> depart, pair<int,int> arrivee);

        void remplacerCase(int x, int y, Case* newCase) ;
        bool estDansBornes (int x, int y) const ;
        bool estFranchissable (int x, int y) const ;
        int getSortieX() const;
        int getSortieY() const;
        vector<vector<Case*>> getGrille() const;
};


#endif 