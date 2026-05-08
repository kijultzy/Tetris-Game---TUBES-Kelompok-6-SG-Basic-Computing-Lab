#include "game.h"
#include <iostream>
#include <conio.h>   // Untuk _kbhit() dan _getch() di Windows
#include <windows.h> // Untuk Sleep() di Windows
#include <time.h>

// Ganti "using namespace std;" dengan pemanggilan spesifik untuk menghindari konflik Windows API
using std::cout;
using std::cin;
using std::vector;
using std::queue;

vector<vector<int>> canvas(ROWS, vector<int>(COLS, 0));
queue<Piece> nextPieceQueue;
int score = 0;
bool gameOver = false;

void initGame() {
    srand(time(0));
    canvas.assign(ROWS, vector<int>(COLS, 0));
    score = 0;
    gameOver = false;

    while(!nextPieceQueue.empty()) nextPieceQueue.pop();

    nextPieceQueue.push(getRandomPiece());
    nextPieceQueue.push(getRandomPiece());
}

void drawMenu() {
    system("cls");
    cout << "======================================\n";
    cout << "           TETRIS TERMINAL            \n";
    cout << "======================================\n";
    cout << " Kelompok  : Kelompok 6\n";
    cout << "   Study Group Basic Computing Lab\n";\n";
    cout << "--------------------------------------\n";
    cout << " Anggota Tim:\n";
    cout << " 1. Rizky Dzulfikar Ahmad. (103012430033)\n";
    cout << " 2. Tiara Fitriannisha     (103012400015)\n";
    cout << " 3. [Nama Anggota 3]       ([NIM 3])\n";
    cout << "======================================\n\n";
    cout << " [1] Start Game\n";
    cout << " [2] Exit\n\n";
    cout << " Pilih menu (1/2): ";
}

void draw(Piece currentPiece) {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    cout << "SCORE: " << score << "\n";
    cout << "NEXT PIECE IN QUEUE: \n";

    Piece nextP = nextPieceQueue.front();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i < nextP.shape.size() && j < nextP.shape[0].size() && nextP.shape[i][j] == 1)
                cout << "[]";
            else
                cout << "  ";
        }
        cout << "\n";
    }

    cout << "========================\n";

    vector<vector<int>> renderCanvas = canvas;
    for (int i = 0; i < currentPiece.shape.size(); i++) {
        for (int j = 0; j < currentPiece.shape[0].size(); j++) {
            if (currentPiece.shape[i][j] == 1) {
                renderCanvas[currentPiece.y + i][currentPiece.x + j] = 1;
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        cout << "|";
        for (int j = 0; j < COLS; j++) {
            if (renderCanvas[i][j] == 1) cout << "[]";
            else cout << " .";
        }
        cout << "|\n";
    }
    cout << "========================\n";
    cout << "Kontrol: W(Rotate) A(Kiri) S(Bawah) D(Kanan)\n";
}

bool checkCollision(Piece p, int offsetX, int offsetY) {
    for (int i = 0; i < p.shape.size(); i++) {
        for (int j = 0; j < p.shape[0].size(); j++) {
            if (p.shape[i][j] == 1) {
                int newX = p.x + j + offsetX;
                int newY = p.y + i + offsetY;

                if (newX < 0 || newX >= COLS || newY >= ROWS) return true;
                if (newY >= 0 && canvas[newY][newX] == 1) return true;
            }
        }
    }
    return false;
}

void lockPiece(Piece p) {
    for (int i = 0; i < p.shape.size(); i++) {
        for (int j = 0; j < p.shape[0].size(); j++) {
            if (p.shape[i][j] == 1) {
                canvas[p.y + i][p.x + j] = 1;
            }
        }
    }
}

void clearFullRows() {
    for (int i = 0; i < ROWS; i++) {
        bool isFull = true;

        for (int j = 0; j < COLS; j++) {
            if (canvas[i][j] == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            score += 100;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLS; j++) {
                    canvas[k][j] = canvas[k - 1][j];
                }
            }
            for (int j = 0; j < COLS; j++) {
                canvas[0][j] = 0;
            }
        }
    }
}

void startGame() {
    char input;
    do {
        drawMenu();
        cin >> input;

        if (input == '1') {
            initGame();
            system("cls");

            Piece currentPiece = nextPieceQueue.front();
            nextPieceQueue.pop();
            nextPieceQueue.push(getRandomPiece());

            int fallDelay = 0;

            while (!gameOver) {
                draw(currentPiece);
                Sleep(50);
                fallDelay++;

                if (_kbhit()) {
                    char key = _getch();
                    if ((key == 'a' || key == 'A') && !checkCollision(currentPiece, -1, 0)) currentPiece.x--;
                    if ((key == 'd' || key == 'D') && !checkCollision(currentPiece, 1, 0)) currentPiece.x++;
                    if ((key == 's' || key == 'S') && !checkCollision(currentPiece, 0, 1)) currentPiece.y++;
                    if (key == 'w' || key == 'W') {
                        Piece rotatedPiece = currentPiece;
                        rotatedPiece.shape = rotate(currentPiece.shape);
                        if (!checkCollision(rotatedPiece, 0, 0)) {
                            currentPiece = rotatedPiece;
                        }
                    }
                }

                if (fallDelay >= 10) {
                    if (!checkCollision(currentPiece, 0, 1)) {
                        currentPiece.y++;
                    } else {
                        lockPiece(currentPiece);
                        clearFullRows();

                        currentPiece = nextPieceQueue.front();
                        nextPieceQueue.pop();
                        nextPieceQueue.push(getRandomPiece());

                        if (checkCollision(currentPiece, 0, 0)) {
                            gameOver = true;
                        }
                    }
                    fallDelay = 0;
                }
            }

            system("cls");
            cout << "\n\n   GAME OVER! \n";
            cout << "   FINAL SCORE: " << score << "\n\n";
            system("pause");

        }
    } while (input != '2');
}
