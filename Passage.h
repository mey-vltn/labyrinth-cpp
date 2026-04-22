#ifndef PASSAGE_H
#define PASSAGE_H

#include <Case.h>

class Passage : public Case {
    public :
    char afficher() const override ;
    TypeCase getTypeCase() const override ;
};

#endif