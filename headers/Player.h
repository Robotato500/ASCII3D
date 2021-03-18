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

        int playerMov();

        bool wallCollision();

        float lSizePerRay1[console.dWidth];
        float lSizePerRay2[console.dWidth];
        char texturePerRay1[console.dWidth];
        char texturePerRay2[console.dWidth];
        float texturePosPerRay1[console.dWidth];
        float texturePosPerRay2[console.dWidth];

};
