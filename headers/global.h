#pragma once
#include <chrono>
#include <iostream>
#include <filesystem>
#include "Console.h"
#include "Image.h"
#include "Player.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 144
#define FONT_WIDTH 4
#define FONT_HEIGHT 4
#define HUD_HEIGHT 30

#define TIC

#ifdef TIC
#define FARYPATH "C:/Users/Usuario/Manu/Projects/ASCII3D/texture1.bmp"
#endif // TIC

#ifndef TIC
#define FARYPATH "C:/Users/usuario/Programming/Projects/ASCII3D/texture1.bmp"
#endif // TIC


#define MAP_SIZE 16

extern std::chrono::time_point<std::chrono::system_clock> clockA;
extern std::chrono::time_point<std::chrono::system_clock> clockB;
extern float deltaTime;
extern Console console;
extern float average(float *numbers, int numNumbers);
extern int mapa[MAP_SIZE][MAP_SIZE];
extern bool visibleMap[MAP_SIZE][MAP_SIZE];
extern double pi;
extern Player jugador;

extern Image textureAtlas;

