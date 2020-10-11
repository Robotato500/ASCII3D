#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
#include <string.h>
#include <math.h>
#include "../headers/console.h"
#include "../headers/global.h"
#include "../headers/input.h"
#include "../headers/Image.h"

/*  std::string texto = "la chucha chucheira";
    char texto_Array[texto.length() + 1];
    strcpy(texto_Array, texto.c_str()); */

int main() {
    srand(time(0));
    console.clearScreen(0b00000000);
    console.refresh();

    Image texture("texture1.bmp");

    while (true) {
        for (int y = 0; y < console.sHeight; y++) {
                for (int x = 0; x < console.sWidth; x++) {
                    console.buffer[x + console.sWidth*y].Attributes = texture.buffer[x + texture.iWidth*y];
                    console.buffer[x + console.sWidth*y].Char.AsciiChar = 219;
                }
        }
        console.refresh();
        if(processInputs()==69)
            return 0;
    }
}

//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-writing-to-console.html
