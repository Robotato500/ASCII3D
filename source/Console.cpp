#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
#include "../headers/Console.h"
#include "../headers/global.h"


Console::Console(int width, int height, int font_width, int font_height, bool cursorOn, int hudHeight) {

    buffer = new CHAR_INFO[width*height];


    wHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    rHandle = GetStdHandle(STD_INPUT_HANDLE);

    windowSize = {0, 0, (width - 1), (height - 1)};
    bufferSize = {width, height};

    SetConsoleTitle("La chucha chucheira");


    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(wHandle, 0, &font);

    font.FontFamily = FF_DONTCARE;
    font.FontWeight = FW_NORMAL;

    font.dwFontSize.X = (SHORT)font_width;
    font.dwFontSize.Y = (SHORT)font_height;
    wcscpy(font.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(wHandle, FALSE, &font);

    //GetLargestConsoleWindowSize();

    SetConsoleActiveScreenBuffer(wHandle);
    SetConsoleScreenBufferSize(wHandle, bufferSize);
    SetConsoleWindowInfo(wHandle, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHandle, bufferSize);

    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(wHandle, &cursor);
    cursor.bVisible = cursorOn;
    cursor.dwSize = 100;
    SetConsoleCursorInfo(wHandle, &cursor);

    fWidth = font_width;
    fHeight = font_height;
    sWidth = width;
    sHeight = height;
    dWidth = width;
    dHeight = height - hudHeight;

    fpsIndex = 0;

};

Console::~Console() {
    delete []buffer;
}


Console::refresh() {
    WriteConsoleOutputA(wHandle, buffer, bufferSize, {0,0}, &windowSize);
    clockA = std::chrono::system_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(clockA-clockB).count();
    if (deltaTime > 0) {
        fps[fpsIndex%50] = 1000000/deltaTime;
        fpsIndex++;
        sprintf(title, "AS3DEditor - %.2f FPS", average(fps, 50));
    }
    SetConsoleTitle(title);
    clockB = clockA;
    return 0;
}

Console::random() {
    for (int y = 0; y<sHeight; y++) {
        for (int x = 0; x<sWidth; x++) {
            buffer[x + y*sWidth].Char.AsciiChar = (unsigned char)219;
            buffer[x + y*sWidth].Attributes = rand()%256;
        }
    }
    return 0;
}

Console::clearScreen(int attribute) {
    for (int y = 0; y<(float)dHeight/2; y++) {
        for (int x = 0; x<dWidth; x++) {
            buffer[x + y*dWidth].Char.AsciiChar = (unsigned char)219;
            buffer[x + y*dWidth].Attributes = 11;
        }
    }
    for (int y = (int)((float)dHeight/2); y<dHeight; y++) {
        for (int x = 0; x<dWidth; x++) {
            buffer[x + y*dWidth].Char.AsciiChar = (unsigned char)219;
            buffer[x + y*dWidth].Attributes = 8;
        }
    }
    return 0;
}

Console::drawString(char *text, int aSize, int xPos, int yPos, bool specify, short int attribute) {
    for (int i = 0; i<(aSize/sizeof(char)); i++) {
        buffer[xPos + yPos*sWidth + i].Char.AsciiChar = text[i];
        if (specify) {buffer[xPos + yPos*sWidth + i].Attributes = attribute;}
    }
    return 0;
}

Console::refreshCursor() {
    SetConsoleCursorPosition(wHandle, cursorPos);
}

Console::drawPixel(int xPos, int yPos, int attribute, int intensity) {
    if (intensity >= 4)
        buffer[xPos + yPos*sWidth].Char.AsciiChar = 32;
    else if (intensity == 0)
        buffer[xPos + yPos*sWidth].Char.AsciiChar = 219;
    else
        buffer[xPos + yPos*sWidth].Char.AsciiChar = 179 - intensity;
    buffer[xPos + yPos*sWidth].Attributes = attribute;
}



Console::drawLine(float lSize, int texIndex, int lPos, float texPos, float intensidad) {

    float texBufIndex = textureAtlas.tWidth*(texPos + texIndex - 1);
    float consoleBufIndex;
    //if (lSize > console.dHeight)
        //lSize = console.dHeight;
    if (lSize <= dHeight) {
        for (int k = 0; k < lSize; k++) {
            //consoleBufIndex = lPos +(int)((float)dHeight/2 - lSize/2 + k)*dWidth;
            drawPixel(lPos, (int)((float)dHeight/2 - lSize/2 + k), textureAtlas.findPixel((int)texBufIndex, (int)(k*(float)textureAtlas.iHeight/(float)lSize)), (int)intensidad);
            //buffer[(int)consoleBufIndex].Attributes = textureAtlas.findPixel((int)texBufIndex, (int)(k*(float)textureAtlas.iHeight/(float)lSize));
        }
    }

    else {
        float caca = (lSize - dHeight)/2;
        for (int k = caca; k < lSize - caca; k++) {
            //consoleBufIndex = lPos +(int)((float)dHeight/2 - lSize/2 + k)*dWidth;
            drawPixel(lPos, (int)((float)dHeight/2 - lSize/2 + k), textureAtlas.findPixel((int)texBufIndex, (int)(k*(float)textureAtlas.iHeight/(float)lSize)), (int)intensidad);
            //buffer[(int)consoleBufIndex].Attributes = textureAtlas.findPixel((int)texBufIndex, (int)(k*(float)textureAtlas.iHeight/(float)lSize));
        }
    }

    return 0;
}
