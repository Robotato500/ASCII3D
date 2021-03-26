#pragma once

class Image {

    public:

        Image(const char* imagePath, int atlas);
        ~Image();
        unsigned char findPixel(int x, int y);

        unsigned char *buffer;
        long bufferLen;
        int iHeight;
        int iWidth;
        int tWidth;
};
