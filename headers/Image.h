#pragma once

class Image {

    public:

        Image(const char* imagePath);
        ~Image();

        unsigned char *buffer;
        long bufferLen;
        int iHeight;
        int iWidth;
};
