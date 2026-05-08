
#ifndef GAME_H
#define GAME_H

#include <queue>
#include <vector>
#include "piece.h"

const int ROWS = 20;
const int COLS = 10;

// Variabel Global Game
extern std::vector<std::vector<int>> canvas;
extern std::queue<Piece> nextPieceQueue;
extern int score;
extern bool gameOver;

void initGame();
void drawMenu();
void draw();
bool checkCollision(Piece p, int offsetX, int offsetY);
void lockPiece(Piece p);
void clearFullRows();
void startGame();

#endif
