#pragma once
#include <chrono>
#include "Console.h"
#include "Image.h"


extern std::chrono::time_point<std::chrono::system_clock> clockA;
extern std::chrono::time_point<std::chrono::system_clock> clockB;
extern int deltaTime;
extern Console console;
extern float average(float *numbers, int numNumbers);
extern bool mapa[8][8];
extern double pi;

extern Image textureFary;
