#include "Passage.h"
#include <iostream>

using namespace std;

char Passage::afficher() const {
    return ' ' ;
}

TypeCase Passage::getTypeCase() const {
    return TypeCase::PASSAGE ;
}

ostream& operator<<(ostream& os, const Passage& e) {
    os << e.afficher() ;
    return os ;
}