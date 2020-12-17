#include <chrono>
#include "../headers/global.h"
#include "../headers/Console.h"
#include "../headers/Player.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256
#define FONT_WIDTH 2
#define FONT_HEIGHT 2

#define TIC

#ifdef TIC
#define FARYPATH "C:/Users/Usuario/Manu/Projects/ASCII3D/texture1.bmp"
#endif // TIC

#ifndef TIC
#define FARYPATH "C:/dev/Projects/C(++)/ASCII3D/texture1.bmp"
#endif // TIC



std::chrono::time_point<std::chrono::system_clock> clockA = std::chrono::system_clock::now();
std::chrono::time_point<std::chrono::system_clock> clockB = std::chrono::system_clock::now();
int deltaTime = 0;
Console console(SCREEN_WIDTH, SCREEN_HEIGHT, FONT_WIDTH, FONT_HEIGHT, false);
Image textureFary(FARYPATH);
double pi = 3.14159265;
Player jugador;

int mapa[16][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

float average(float *numbers, int numNumbers) {
    int sum = 0;
    for (int i = 0; i < numNumbers; i++) {
        sum += numbers[i];
    }
    return sum/numNumbers;
}
