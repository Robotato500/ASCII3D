#pragma once
#include <ctime>
#include <windows.h>
#include "Image.h"


class Console {

    public:
    HANDLE wHandle;
    HANDLE rHandle;
    SMALL_RECT windowSize;
    COORD bufferSize;

    Console(int width, int height, int font_width, int font_height, bool cursorOn, int hudHeight);
    ~Console();

    int refresh();
    int random();
    int clearScreen(int attribute = 0);

    int drawChar();
    int drawString(char *text, int aSize, int xPos, int yPos, bool specify = false, short int attribute = 0);
    int refreshCursor();
    int drawPixel(int xPos, int yPos, int attribute, int intestity = 0);
    int drawLine(float lSize, int texIndex, int lPos, float texPos, float intensidad, Image *imagen);
    int drawWalls();


    int sWidth;
    int sHeight;
    int fWidth;
    int fHeight;
    int fpsIndex;
    float fps[50];
    int dWidth;
    int dHeight;

    float *columnDistance;

    CHAR_INFO *buffer;

    char title[30];

    COORD cursorPos;

    DWORD eventBuffer[];

};
