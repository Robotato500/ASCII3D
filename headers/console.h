#pragma once
#include <ctime>
#include <windows.h>


class Console {

    public:
    HANDLE wHandle;
    HANDLE rHandle;
    SMALL_RECT windowSize;
    COORD bufferSize;

    Console(int width, int height, int font_width, int font_height, bool cursorOn);
    ~Console();

    int refresh();
    int random();
    int clearScreen(int attribute = 0);

    int drawChar();
    int drawString(char *text, int aSize, int xPos, int yPos, bool specify = false, short int attribute = 0);
    int refreshCursor();
    int drawPixel(int xPos, int yPos, int attribute, int intestity = 4);


    int sWidth;
    int sHeight;
    int fWidth;
    int fHeight;
    int fpsIndex;
    float fps[50];

    CHAR_INFO *buffer;

    char title[30];

    COORD cursorPos;

    DWORD eventBuffer[];

};
