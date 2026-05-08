#ifndef PIECE_H
#define PIECE_H

#include <vector>

// Struktur untuk mendefinisikan blok Tetris
struct Piece {
    std::vector<std::vector<int>> shape;
    int x; // Posisi horizontal (kolom)
    int y; // Posisi vertikal (baris)

    Piece() : x(0), y(0) {}
    Piece(std::vector<std::vector<int>> s, int startX, int startY) : shape(s), x(startX), y(startY) {}
};

// Deklarasi fungsi rotasi
std::vector<std::vector<int>> rotate(std::vector<std::vector<int>> shape);

// Deklarasi fungsi untuk mengambil blok acak
Piece getRandomPiece();

#endif
