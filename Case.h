#ifndef CASE_H
#define CASE_H

#include "TypeCase.h"


class Case {
    
    public:
        virtual char afficher() const  = 0 ;
        virtual ~Case() = default ;
        virtual TypeCase getTypeCase() const = 0 ;
};

#endif