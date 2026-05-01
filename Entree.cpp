#include "Entree.h"
#include "CaseFactory.h"
#include <iostream>

using namespace std;

char Entree::afficher() const {
    return 'E' ;
}

TypeCase Entree::getTypeCase() const {
    return TypeCase::ENTREE ;
}

ostream& operator<<(ostream& os, const Entree& e) {
    os << e.afficher() ;
    return os ;
}