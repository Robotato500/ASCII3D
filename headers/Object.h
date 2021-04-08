#include "Image.h"

#define SPRITE1_PATH "C:/Users/Usuario/Manu/Projects/ASCII3D/sprite1.bmp"

class Object {

    public:
        Object(const char* spritePath, int atlas);

        Image *sprite;

        float xPos;
        float yPos;

        float angle;

        int draw;

};
