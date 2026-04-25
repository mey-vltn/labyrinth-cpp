#ifndef MUR_H
#define MUR_H

#include "Case.h"

class Mur : public Case {
    public :
    char afficher() const override ;
    TypeCase getTypeCase() const override ;
};

#endif
