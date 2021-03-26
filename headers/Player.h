#pragma once
#include "global.h"


class Player {

    public:
        Player();
        int checkLoop(double rayAngle);
        int prepareCollision(double angulo);
        int rayCast();
        int roundXCoord(float xCoord);
        int roundYCoord(float yCoord);

        int dpp;

        float fov;

        double angle;

        float xPos;
        float yPos;

        float colXX;
        float colXY;
        float colYX;
        float colYY;

        float texturePosition;

        float distance;
        float distanceX;
        float distanceY;

        int incX;
        int incY;

        int advance;
        int roll;
        float speed;

        int playerMov();

        bool wallCollision();

        float *distancePerRay1;
        float *distancePerRay2;
        int *texturePerRay1;
        int *texturePerRay2;
        float *texturePosPerRay1;
        float *texturePosPerRay2;

};
