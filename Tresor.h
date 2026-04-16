#ifndef TRESOR_H
#define TRESOR_H

#include <Case.h>

class Tresor : public Case {
    private:
    
    int valeur ;

    public :

    Tresor(int valeur) ;
    char afficher() ;
};

#endif