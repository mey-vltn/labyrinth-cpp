#include "Case.h"
#include "Mur.h"
#include "Passage.h"
#include "Tresor.h"
#include "Monstre.h"
#include "Piege.h"

enum TypeCase {
    MUR = new Mur(),
    PASSAGE = new Passage(),
    TRESOR = new Tresor(),
    MONSTRE = new Monstre(),
    PIEGE = new Piege()

}

class CaseFactory {

    public:
        Case* creerCase (TypeCase tc) {

        }
};