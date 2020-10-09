#include <stdio.h>
#include <windows.h>
#include "../headers/console.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 40

CHAR_INFO screen_Buffer[SCREEN_WIDTH*SCREEN_HEIGHT];

int main() {
    consoleInit(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 16);
    getchar();
    return 0;
}

//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-writing-to-console.html
