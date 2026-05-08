#include "piece.h"
#include <cstdlib>

using namespace std;

// 7 Bentuk klasik Tetris (I, J, L, O, S, T, Z)
const vector<vector<vector<int>>> SHAPES = {
    {{1, 1, 1, 1}},                               // I
    {{1, 0, 0}, {1, 1, 1}},                       // J
    {{0, 0, 1}, {1, 1, 1}},                       // L
    {{1, 1}, {1, 1}},                             // O
    {{0, 1, 1}, {1, 1, 0}},                       // S
    {{0, 1, 0}, {1, 1, 1}},                       // T
    {{1, 1, 0}, {0, 1, 1}}                        // Z
};

// Fungsi memutar matriks 90 derajat searah jarum jam
vector<vector<int>> rotate(vector<vector<int>> shape) {
    int row = shape.size();
    int col = shape[0].size();
    vector<vector<int>> result(col, vector<int>(row));

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            result[j][row - 1 - i] = shape[i][j];
        }
    }
    return result;
}

// Fungsi untuk mendapatkan blok acak di posisi awal tengah atas
Piece getRandomPiece() {
    int index = rand() % SHAPES.size();
    return Piece(SHAPES[index], 4, 0); // Mulai dari tengah (kolom 4), atas (baris 0)
}
