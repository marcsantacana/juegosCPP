#define FRAME_RATE 150

#include <iostream>
#include <thread>
#include <chrono>
#include "keyboard.h"

const int WIDTH = 20;
const int HEIGHT = 10;

void dibujaTablero(int snakeX, int snakeY) {
    system("cls");
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (y == 0 || y == HEIGHT - 1) {
                std::cout << '-';
            } 
            else if (x == 0 || x == WIDTH - 1) {
                std::cout << '|';
            } 
            else if (x == snakeX && y == snakeY) {
                std::cout << 'X';
            } 
            else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int snakeX = WIDTH / 2;
    int snakeY = HEIGHT / 2;
    bool bGameOver = false;

    while (!bGameOver) {
        dibujaTablero(snakeX, snakeY);

        if (IsWPressed() && snakeY > 1) {
            --snakeY;
        }
        if (IsAPressed() && snakeX > 1) {
            --snakeX;
        }
        if (IsSPressed() && snakeY < HEIGHT - 2) {
            ++snakeY;
        }
        if (IsDPressed() && snakeX < WIDTH - 2) {
            ++snakeX;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
    }
    return 0;
}