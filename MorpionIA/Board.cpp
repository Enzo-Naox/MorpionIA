#include "Board.h"

Board::Board() : grille(3, vector<char>(3, ' ')) {}

void Board::afficherGrille() const {
    cout << "Grille de Morpion:" << endl;
    cout << "  1 | 2 | 3 " << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1;
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << grille[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        cout << "  ";
        if (i < 2) cout << "--+---+--\n";
    }
}

void Board::placerSymbole(int ligne, int col, char symbole) {
    grille[ligne][col] = symbole;
}

bool Board::verifierVictoire(char symbole) const {
    // Vérification des lignes
    for (int i = 0; i < 3; ++i) {
        if (grille[i][0] == symbole && grille[i][1] == symbole && grille[i][2] == symbole) {
            return true;
        }
    }
    // Vérification des colonnes
    for (int j = 0; j < 3; ++j) {
        if (grille[0][j] == symbole && grille[1][j] == symbole && grille[2][j] == symbole) {
            return true;
        }
    }
    // Vérification des diagonales
    if (grille[0][0] == symbole && grille[1][1] == symbole && grille[2][2] == symbole) {
        return true;
    }
    if (grille[0][2] == symbole && grille[1][1] == symbole && grille[2][0] == symbole) {
        return true;
    }
    return false;
}

bool Board::isFull() const
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grille[i][j] == ' ') { // Supposons que les cases vides sont représentées par un espace
                return false;
            }
        }
    }
    return true;
}

void Board::Rollback(int ligne, int col)
{
    grille[ligne][col] = ' ';
}

Board::Resultat Board::mouvementValide(int ligne, int col) const {
    if (ligne < 0 || ligne >= 3 || col < 0 || col >= 3) {
        return ERREUR;
    }
    if (grille[ligne][col] != ' ') {
        return OCCUPE;
    }
    return VALIDE;
}