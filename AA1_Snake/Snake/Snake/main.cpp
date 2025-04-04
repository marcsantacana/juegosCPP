#define FRAME_RATE 150

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
// Arxiu de les funcions de teclat.
#include "keyboard.h"

using namespace std;

// Constants que es fan servir al llarg del joc.
const int BOARD_WIDTH = 20; // Amplada del tauler.
// Alçada del tauler.
const int BOARD_HEIGHT = 10;
// Retard entre cada fotograma (en milisegons).
const int FRAME_DELAY_MS = 100;
// Punts per menjar una fruita.
const int FRUIT_POINTS = 15;
// Caràcter per a les parets.
const char WALL_CHAR = '#';
// Caràcter per al cap de la serp.
const char SNAKE_HEAD_CHAR = 'O';
// Caràcter per al cos de la serp.
const char SNAKE_BODY_CHAR = 'o';
// Caràcter per a la fruita.
const char FRUIT_CHAR = 'F';

// Estructura per representar una posició al tauler.
struct Point {
    // Posició en l'eix X.
    int x;
    // Posició en l'eix Y.
    int y;
};

// Variables globals.
bool gameOver; // Estat del joc.
// Puntuació del jugador.
int score;
// Cos de la serp.
vector<Point> snake;
// Fruita al tauler.
Point fruit;

// Funció per inicialitzar el joc.
void Setup() {
    gameOver = false;
    // Inicialitza la puntuació.
    score = 0;
    // Neteja qualsevol serp anterior.
    snake.clear();
    // Inicialitza el cap de la serp al centre.
    snake.push_back({BOARD_WIDTH / 2, BOARD_HEIGHT / 2});
    // Col·loca la fruita en una posició aleatòria.
    fruit.x = rand() % BOARD_WIDTH;
    fruit.y = rand() % BOARD_HEIGHT;
}

// Funció per dibuixar el tauler.
void Draw() {
    // Neteja la pantalla. Si corregeixes el programa amb Linux posa "clear".
    system("cls");
    // Mostra la puntuació. No poso accent perque a la terminal no es veu bé.
    cout << "Puntuacio: " << score << endl;
    // Recórre el tauler i dibuixar els elements.
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (y == 0 || y == BOARD_HEIGHT - 1 || x == 0 || x == BOARD_WIDTH - 1) {
                // Dibuixa les parets.
                cout << WALL_CHAR;
            } else if (x == snake[0].x && y == snake[0].y) {
                // Dibuixa el cap de la serp.
                cout << SNAKE_HEAD_CHAR;
            } else if (x == fruit.x && y == fruit.y) {
                // Dibuixa la fruita.
                cout << FRUIT_CHAR;
            } else {
                bool printed = false;
                // Dibuixa el cos de la serp.
                for (int i = 1; i < snake.size(); i++) {
                    if (x == snake[i].x && y == snake[i].y) {
                        // Dibuixa el cos.
                        cout << SNAKE_BODY_CHAR;
                        printed = true;
                        break;
                    }
                }
                if (!printed) {
                    // Espai buit.
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

// Funció per actualitzar la lògica del joc.
void Logic(int &snakeX, int &snakeY) {
    // Crea un nou cap de serp.
    Point newHead = snake[0];

    // Moure el cap segons la direcció.
    if (IsWPressed() && snakeY > 1) {
        // Moure cap amunt.
        newHead.y--;
    }
    if (IsSPressed() && snakeY < BOARD_HEIGHT - 2) {
        // Moure cap avall.
        newHead.y++;
    }
    if (IsAPressed() && snakeX > 1) {
        // Moure cap a l'esquerra.
        newHead.x--;
    }
    if (IsDPressed() && snakeX < BOARD_WIDTH - 2) {
        // Moure cap a la dreta.
        newHead.x++;
    }

    // Comprova col·lisió amb les parets.
    if (newHead.x <= 0 || newHead.x >= BOARD_WIDTH - 1 || newHead.y <= 0 || newHead.y >= BOARD_HEIGHT - 1) {
        // El joc acaba si toca una paret.
        gameOver = true;
        return;
    }

    // Comprova col·lisió amb el cos de la serp.
    for (int i = 1; i < snake.size(); i++) {
        if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
            // El joc acaba si toca el seu propi cos.
            gameOver = true;
            return;
        }
    }

    // Posa el nou cap a la serp.
    snake.insert(snake.begin(), newHead);

    // Comprova si la serp ha menjat la fruita.
    if (newHead.x == fruit.x && newHead.y == fruit.y) {
        // Suma punts per menjar la fruita.
        score += FRUIT_POINTS;
        // Genera nova fruita en una posició aleatòria.
        fruit.x = rand() % BOARD_WIDTH;
        fruit.y = rand() % BOARD_HEIGHT;
    } else {
        // Elimina l'últim segment si no s'ha menjat la fruita.
        snake.pop_back();
    }
}

// Funció principal del joc.
int main() {
    // Inicialitza el generador de nombres aleatoris.
    srand(time(0));
    // Inicialitza el joc.
    Setup();

    int snakeX = BOARD_WIDTH / 2;
    int snakeY = BOARD_HEIGHT / 2;
    
    // Bucle principal del joc.
    while (!gameOver) {
        // Dibuixa el tauler.
        Draw();
        // Actualitza la lògica del joc.
        Logic(snakeX, snakeY);
        
        // Controla el frame rate del joc.
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
    }

    // Mostrar el missatge al final del joc.
    cout << "Game Over! Puntuació final: " << score << endl;

    // Aquí s'acaba el programa.
    return 0;
}