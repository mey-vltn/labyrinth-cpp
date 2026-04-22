#ifndef AVENTURIER_H
#define AVENTURIER_H

#include <iostream>
#include <utility>
#include <vector>
#include "Tresor.h"
#include "Donjon.h"
#include "Case.h"

using namespace std;

class Aventurier {

    private:
        int x, y ;
        int ptsVie ;
        int nbTresors ;
    
    public:
        // getters
        int getX() const ;
        int getY() const ;
        int getPV() const ;
        int getNbTresors() const ;

        
        void deplacer(int nx, int ny) ;
        void pertePV(int degats) ; 
        void ajouterTresor() ;

        void resoudreCase(Case* c) ;

        bool estVivant() const ;
        void afficherStatut() const ;
    
};

#endif