#include "Donjon.h"
#include "CaseFactory.h"
#include <random>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>


using namespace std;


const int DIRECTIONS[4][2] = {
    {-2, 0},
    {2, 0},
    {0, -2},
    {0, 2}
};


// GETTERS

int Donjon::getSortieX() const{
    return sortie.first;
}

int Donjon::getSortieY() const{
    return sortie.second;
}

Case* Donjon::getCase (int x, int y) const {
    return grille[x][y] ;
}

vector<vector<Case*>> Donjon::getGrille() const{
    return grille;
}




// AFFICHAGES

void Donjon::afficher(int ax, int ay) {
    cout << '\n';
    // contour du haut
    cout << '+';
    for (int j = 0; j < largeur; j++) cout << " -";
    cout << "+" << endl;

    // contenu
    for (int i = 0; i < hauteur; i++) {
        cout << '|'; // bord de gauche
        for (int j = 0; j < largeur; j++) {
            if (i == ax && j == ay) {
                cout << "@ ";}
            else{
                Case* c = grille[i][j];
                if (c != nullptr) cout << c->afficher() << " ";
            }
            
        }
        cout << '|' << endl; // bord droit + retour à la ligne
    }

    // contour du bas
    cout << '+';
    for (int j = 0; j < largeur; j++) cout << " -";
    cout << "+" << endl;
}


void Donjon::afficherChemin(const vector<pair<int,int>>& chemin, int ax, int ay) {
    
    if (chemin.empty()) {
        cout << "Aucun chemin trouvé.\n";
        return;
    }

    vector<vector<char>> copie(hauteur, vector<char>(largeur));

    // copie de l'affichage actuel de la grille
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie[i][j] = grille[i][j]->afficher();
        }
    }

    // marquage du chemin avec '.'
    for (auto& pos : chemin) {
        int x = pos.first;
        int y = pos.second;

        // éviter de remplacer l'entrée, la sortie et le joueur
        if (!(x == ax && y == ay) &&
            grille[x][y]->getTypeCase() != TypeCase::ENTREE &&
            grille[x][y]->getTypeCase() != TypeCase::SORTIE) {
            copie[x][y] = '.';
        }
    }

    // Afficher la copie
    cout << '+';
    for (int j = 0; j < largeur; j++) cout << " -";
    cout << "+" << endl;

    for (int i = 0; i < hauteur; i++) {
        cout << '|';
        for (int j = 0; j < largeur; j++) {
            if (i == ax && j == ay)
                cout << "@ ";
            else
                cout << copie[i][j] << " ";
        }
        cout << '|' << endl;
    }

    cout << '+';
    for (int j = 0; j < largeur; j++) cout << " -";
    cout << "+" << endl;

    cout << "Distance a la sortie : " << chemin.size() - 1 << " cases" << endl;
}





// GESTION DE LA GRILLE


bool Donjon::estDansBornes(int x, int y) const {
    return (y >= 0 && y < grille.size()) && (x >= 0 && x < grille[y].size()) ;
}

void Donjon::genererLabyrinthe(int x, int y){
    grille[x][y] = CaseFactory::creerCase(TypeCase::PASSAGE);

    int ordre[4] = {0, 1, 2, 3}; // on crée ça pour représenter les indices du tableau DIRECTIONS

    // Initialisation du générateur aléatoire
    std::random_device rd;
    std::mt19937 g(rd());

    // mélange
    std::shuffle(ordre, ordre + 4, g);

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
    largeur = l ;
    hauteur = h ;

    // initialisation de toute la grille avec des murs
    grille = vector<vector<Case*>>(hauteur, vector<Case*>(largeur, nullptr));

    visites = vector<vector<bool>>(hauteur, vector<bool>(largeur, false));
    nbCasesVisitees = 0;

    for(int i = 0; i < hauteur; i++){
        for(int j = 0; j < largeur; j++){
            grille[i][j] = CaseFactory::creerCase(TypeCase::MUR);
        }
    }

    genererLabyrinthe(1, 1);

    placerElements();

    grille[1][1] = CaseFactory::creerCase(TypeCase::ENTREE);
    // ici on veut toujours que la sortie soit accessible : il faut que ce soit sur une case impair parce qu'on commence sur (1,1) et on saute de 2 en 2.
    int si = (hauteur - 2) % 2 == 0 ? hauteur - 3 : hauteur - 2;
    int sj = (largeur - 2) % 2 == 0 ? largeur - 3 : largeur - 2;
    grille[si][sj] = CaseFactory::creerCase(TypeCase::SORTIE);
    sortie = {si, sj};


}


void Donjon::placerElements() {
    std::mt19937 rng{std::random_device{}()}; // générateur de nombres aléatoires
    std::uniform_int_distribution<int> dist(0, 100);  // Distribution uniforme d'entiers entre 0 et 100
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {

            TypeCase type = grille[i][j]->getTypeCase();
            if (type == TypeCase::ENTREE || type == TypeCase::SORTIE) continue;

            if (grille[i][j]->getTypeCase() == TypeCase::PASSAGE) {
                int r = dist(rng);
                if      (r < 5)  grille[i][j] = CaseFactory::creerCase(TypeCase::TRESOR);
                else if (r < 10) grille[i][j] = CaseFactory::creerCase(TypeCase::MONSTRE);
                else if (r < 13) grille[i][j] = CaseFactory::creerCase(TypeCase::PIEGE);
            }
        }
    }
}


void Donjon::remplacerCase(int x, int y, Case* newCase) {
    delete grille[x][y] ;
    grille[x][y] = newCase ;
}

// BFS
vector<pair<int,int>> Donjon::trouverChemin(vector<vector<Case*>> grille , pair<int,int> depart, pair<int,int> arrivee){

    queue<pair<int,int>> file;
    vector<vector<bool>> visite(hauteur, vector<bool>(largeur, false));
    vector<vector<pair<int,int>>> parent(hauteur, vector<pair<int,int>>(largeur, {-1,-1}));

    file.push(depart);
    visite[depart.first][depart.second] = true;

    // directions pour les voisins v
    int dir_x[4] = {-1, 0, 1, 0};
    int dir_y[4] = {0, 1, 0, -1};


    while(!file.empty()){
        pair<int,int> courant = file.front();
        file.pop();

        if(courant==arrivee) return reconstruireChemin(parent, depart, arrivee);

        for(int i=0; i<4; i++){
            int nx = courant.first + dir_x[i];
            int ny = courant.second + dir_y[i];
            pair<int,int> voisin = {nx, ny};

            if(nx>=0 && nx<hauteur && ny>=0 && ny < largeur && !visite[nx][ny] && grille[nx][ny]->getTypeCase() != TypeCase::MUR){
                visite[nx][ny] = true;
                parent[nx][ny] = courant;
                file.push(voisin);
            }
        }
    } 
    return {} ;
}

vector<pair<int,int>> Donjon::reconstruireChemin(vector<vector<pair<int,int>>>& parent, pair<int,int> depart, pair<int,int> arrivee) {
    
    vector<pair<int,int>> chemin;
    pair<int,int> courant = arrivee;

    while (courant != depart) {
        chemin.insert(chemin.begin(), courant); 
        courant = parent[courant.first][courant.second];
    }
    chemin.insert(chemin.begin(), depart); 

    return chemin;
}



// GESTION DE LA VISITE DES CASES

void Donjon::marquerVisitee(int x, int y) {
    if (!visites[x][y]) {
        visites[x][y] = true ;
        nbCasesVisitees++ ;
    }
}

int Donjon::getNbCasesVisitees() const {
    return nbCasesVisitees;
} 



// GETSIONDE LA SAUVEGARDE DANS FICHIER TEXTE

void Donjon::sauvegarder(const std::string& nomFichier) const {
    std::ofstream fichier(nomFichier) ;

    fichier << largeur << " " << hauteur << "\n" ; 

    for (int i = 0 ; i < hauteur ; i++) {
        for (int j = 0; j < largeur; j++) {
            fichier << grille[i][j]->afficher() ;
        }
        fichier << "\n"; 
    }
}

void Donjon::charger(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier) ;

    fichier >> largeur >> hauteur ;
    fichier.ignore() ;

    grille = std::vector<std::vector<Case*>>(
        hauteur,
        std::vector<Case*>(largeur, nullptr)
    ) ;

    std::string ligne ;

    for (int i = 0 ; i < hauteur ; i++) {
        std::getline(fichier, ligne) ;

        for (int j = 0; j < largeur; j++) {
            char c = ligne[j] ;

            if (c == '#') grille[i][j] = CaseFactory::creerCase(TypeCase::MUR) ;
            else if (c == '+') grille[i][j] = CaseFactory::creerCase(TypeCase::TRESOR) ; 
            else if (c == 'M') grille[i][j] = CaseFactory::creerCase(TypeCase::MONSTRE) ;
            else if (c == 'P') grille[i][j] = CaseFactory::creerCase(TypeCase::PIEGE) ;
            else if (c == 'E') grille[i][j] = CaseFactory::creerCase(TypeCase::ENTREE) ;
            else if (c == 'S') {
                grille[i][j] = CaseFactory::creerCase(TypeCase::SORTIE) ;
                sortie = {i, j} ;
            }
            else grille[i][j] = CaseFactory::creerCase(TypeCase::PASSAGE) ;
        }
    }
}



// GESTION DEPLACEMENT ALÉATOIREE DES MONSTRES

void Donjon::deplacerMonstreAleatoirement(int oldX, int oldY) {
    std::vector<std::pair<int, int>> casesLibres;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (grille[i][j]->getTypeCase() == TypeCase::PASSAGE) {
                casesLibres.push_back({i, j});
            }
        }
    }

    if (casesLibres.empty()) return ;
 
    int indice = rand() % casesLibres.size() ;
    int newX = casesLibres[indice].first ;
    int newY = casesLibres[indice].second ;

    remplacerCase(oldX, oldY, CaseFactory::creerCase(TypeCase::PASSAGE)) ; 
    remplacerCase(newX, newY, CaseFactory::creerCase(TypeCase::MONSTRE) ); 
}