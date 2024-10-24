#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Board {
public:
    Board();

    enum Resultat {VALIDE, OCCUPE, ERREUR};
    Resultat mouvementValide(int ligne, int col)const;

    void afficherGrille() const;
    void placerSymbole(int ligne, int col, char symbole);
    bool verifierVictoire(char symbole) const;
    bool isFull() const;
    void Rollback(int ligne, int col);

private:
    vector<vector<char>> grille;
};

