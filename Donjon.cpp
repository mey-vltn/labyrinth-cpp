#include "Donjon.h"
#include "CaseFactory.h"
#include <random>


void Donjon::afficher() {
    
    // contour du haut
    cout << '+';
    for (int j = 0; j < largeur; j++) cout << '-';
    cout << '+' << endl;

    // contenu
    for (int i = 0; i < hauteur; i++) {
        cout << '|'; // bord de gauche
        for (int j = 0; j < largeur; j++) {
            Case* c = grille[i][j];
            if (c != nullptr) cout << c->afficher();
        }
        cout << '|' << endl; // bord droit + retour à la ligne
    }

    // contour du bas
    cout << '+';
    for (int j = 0; j < largeur; j++) cout << '-';
    cout << '+' << endl;
}

const int DIRECTIONS[4][2] = {
    {-2, 0},
    {2, 0},
    {0, -2},
    {0, 2}
};


bool Donjon::estDansBornes(int x, int y) const {

    return (y >= 0 && y < grille.size()) && (x >= 0 && x < grille[y].size()) ;
}



// FONCTIONS DE GÉNÉRATION DE LABYRINTHE

void Donjon::genererLabyrinthe(int x, int y){
    grille[x][y] = CaseFactory::creerCase(TypeCase::PASSAGE);

    int ordre[4] = {0, 1, 2, 3}; // on crée ça pour représenter les indices du tableau DIRECTIONS, c'est ce qu'on va shuffle
    random_shuffle(ordre, ordre+4);

    for(int i=0; i<4; i++) {
        int dx = DIRECTIONS[ordre[i]][0];
        int dy = DIRECTIONS[ordre[i]][1];
        int mur_x = dx/2;
        int mur_y = dy/2;

        int nx = x + dx;
        int ny = y + dy;

        // vérification des bornes
        if (nx > 0 && nx < hauteur - 1 && ny > 0 && ny < largeur - 1 && grille[nx][ny]->getTypeCase() == TypeCase::MUR) {
            grille[x + mur_x][y + mur_y] = CaseFactory::creerCase(TypeCase::PASSAGE);

            genererLabyrinthe(nx, ny);
        }
     }
}


void Donjon::generer(int l, int h) {
    largeur = l ;
    hauteur = h ;

    // initialisation de toute la grille avec des murs
    grille = vector<vector<Case*>>(hauteur, vector<Case*>(largeur, nullptr));

    for(int i = 0; i < hauteur; i++){
        for(int j = 0; j < largeur; j++){
            grille[i][j] = CaseFactory::creerCase(TypeCase::MUR);
        }
    }

    genererLabyrinthe(1, 1);

    placerElements();

}


void Donjon::placerElements() {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, 100); // c'est des générateurs de probabilités mais j'avoue que je les comprends pas trop

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (grille[i][j]->getTypeCase() == TypeCase::PASSAGE) {
                int r = dist(rng);
                if      (r < 5)  grille[i][j] = CaseFactory::creerCase(TypeCase::TRESOR);
                else if (r < 10) grille[i][j] = CaseFactory::creerCase(TypeCase::MONSTRE);
                else if (r < 13) grille[i][j] = CaseFactory::creerCase(TypeCase::PIEGE);
            }
        }
    }
}




Case* Donjon::getCase (int x, int y) const {
    return grille[y][x] ;
}

void Donjon::remplacerCase(int x, int y, Case* newCase) {
    delete grille[y][x] ;
    grille[y][x] = newCase ;
}

