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
        std::pair<int,int> position ;
        int ptsVie ;
        vector<Tresor> inventaire ;

    public:
        // types à changer probablement 
        void deplacer(int nx, int ny) ;
        void resoudreCase(Case* c) ;
        bool estVivant() const ;
        void afficherStatut() const ;
        void boucleDeJeu (Donjon& d) ;
        void afficherPosition () const ;
};

#endif