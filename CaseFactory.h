#include "Case.h"

enum TypeCase {
    MUR,
    PASSAGE,
    TRESOR,
    MONSTRE,
    PIEGE
};

class CaseFactory {

    public:
        static Case* creerCase (TypeCase type) ;
};