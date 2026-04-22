#ifndef TRESOR_H
#define TRESOR_H

#include "Case.h"
#include "TypeCase.h"

class Tresor : public Case {
    
    private:
        int valeur ;

    public :
        Tresor(int valeur) ;
        char afficher() const override ;
        TypeCase getTypeCase() const override ;
};

#endif