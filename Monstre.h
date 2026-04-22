#ifndef MONSTRE_H
#define MONSTRE_H

#include <vector>
#include <iostream>

#include "Case.h" 
#include "TypeCase.h"

class Monstre : public Case {

    private:
        int pv ;

    public:
        Monstre(int valeur) ;
        char afficher() const override ;
        TypeCase getTypeCase() const override ;
};


#endif
