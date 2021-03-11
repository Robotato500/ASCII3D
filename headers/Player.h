#pragma once


class Player {

    public:
        Player();
        int checkLoop(double rayAngle);
        int prepareCollision(double angulo);
        int rayCast();
        int roundXCoord(float xCoord);
        int roundYCoord(float yCoord);

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

};
