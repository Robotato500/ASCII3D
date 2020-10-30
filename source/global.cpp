#include <chrono>
#include "../headers/global.h"
#include "../headers/Console.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define FONT_WIDTH 4
#define FONT_HEIGHT 4


std::chrono::time_point<std::chrono::system_clock> clockA = std::chrono::system_clock::now();
std::chrono::time_point<std::chrono::system_clock> clockB = std::chrono::system_clock::now();
int deltaTime = 0;
Console console(SCREEN_WIDTH, SCREEN_HEIGHT, FONT_WIDTH, FONT_HEIGHT, false);
double pi = 3.14159265;

bool mapa[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1,}
    {1, 0, 0, 0, 0, 0, 0, 1,}
    {1, 0, 0, 0, 0, 0, 0, 1,}
    {1, 0, 0, 0, 0, 0, 0, 1,}
    {1, 0, 0, 0, 0, 0, 0, 1,}
    {1, 0, 0, 0, 0, 0, 0, 1,}
    {1, 0, 0, 0, 0, 0, 0, 1,}
    {1, 1, 1, 1, 1, 1, 1, 1}
}

float average(float *numbers, int numNumbers) {
    int sum = 0;
    for (int i = 0; i < numNumbers; i++) {
        sum += numbers[i];
    }
    return sum/numNumbers;
}
