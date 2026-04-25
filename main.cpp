#include "Donjon.h"
#include "Aventurier.h"

int main() {
    Donjon donjon;
    Aventurier aventurier(1, 1);

    donjon.generer(21, 21);

    aventurier.boucledeJeu(donjon);

    return 0;
}