#include "Sortie.h"
#include "CaseFactory.h"
#include <iostream>

using namespace std;

char Sortie::afficher() const {
    return 'S' ;
}

TypeCase Sortie::getTypeCase() const {
    return TypeCase::SORTIE ;
}

ostream& operator<<(ostream& os, const Sortie& e){
    os << e.afficher();
    return os;
}