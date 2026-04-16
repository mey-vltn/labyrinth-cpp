#ifndef PIEGE_H
#define PIEGE_H

#include <vector>
#include <iostream>

#include "Case.h" 

class Piege : public Case {

    private:
        int degats ;

    public:
        Piege(int degats) ;
        char afficher () override ;
};


#endif
