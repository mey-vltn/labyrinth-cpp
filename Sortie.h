#ifndef SORTIE_H
#define SORTIE_H

#include "Case.h"

class Sortie : public Case {
    public :
    char afficher() const override ;
    TypeCase getTypeCase() const override ;
};

#endif
