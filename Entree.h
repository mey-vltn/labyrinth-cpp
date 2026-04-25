#ifndef ENTREE_H
#define ENTREE_H

#include "Case.h"

class Entree : public Case {
    public :
    char afficher() const override ;
    TypeCase getTypeCase() const override ;
};

#endif
