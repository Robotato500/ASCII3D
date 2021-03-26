#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include "../headers/Image.h"


Image::Image(const char* filePath, int atlas) {
    unsigned char *fakeBuffer;
    long filelen;
    FILE *imagePtr;

    imagePtr = fopen(filePath, "rb");
    fseek(imagePtr, 0, SEEK_END);
    filelen = ftell(imagePtr);
    rewind(imagePtr);

    fakeBuffer = (unsigned char *)malloc(filelen * sizeof(char));
    fread(fakeBuffer, filelen, 1, imagePtr);

    iWidth = fakeBuffer[18] + fakeBuffer[19]*256 + (fakeBuffer[20])*256*256 + (fakeBuffer[21])*256*256*256; //por como es el formato bmp
    iHeight = fakeBuffer[22] + fakeBuffer[23]*256 + (fakeBuffer[24])*256*256 + (fakeBuffer[25])*256*256*256;
    tWidth = iWidth/atlas;

    unsigned char cgaColors[][3] = { { 0, 0, 0 }, { 0, 0, 170 }, { 0, 170, 0 }, { 0, 170, 170 }, { 170, 0, 0 }, { 170, 0, 170 },
    { 170, 85, 0 }, { 170, 170, 170 }, { 85, 85, 85 }, { 85, 85, 255 }, { 85, 255, 85 }, { 85, 255, 255 },
    { 255, 85, 85 }, { 255, 85, 255 }, { 255, 255, 85 }, { 255, 255, 255 } };

    bufferLen = (filelen - 54)/3;
    buffer = (unsigned char *)malloc(bufferLen * sizeof(char));

    int index1, index2;

    for (int i = 0; i<bufferLen; i++) {

        int currentColorValue = 0;
        int dr1 = 255; int dg1 = 255; int db1 = 255;
        int dr2, dg2, db2;

        for (int j = 0; j < 16; j++) {

            dr2 = (fakeBuffer[54 + 3*i] - cgaColors[j][2]);
            dg2 = (fakeBuffer[54 + 3*i + 1] - cgaColors[j][1]);
            db2 = (fakeBuffer[54 + 3*i + 2] - cgaColors[j][0]);

            if ((dr1*dr1 + dg1*dg1 + db1*db1) > (dr2*dr2 + dg2*dg2 + db2*db2)) {
                dr1 = dr2; dg1 = dg2; db1 = db2;
                currentColorValue = j;
            }
        }
        buffer[i] = currentColorValue;
    }
}

unsigned char Image::findPixel(int x, int y) {
    return(buffer[x+y*iWidth]);
}

Image::~Image() {
}

