#include <math.h>
#include <cstdlib>
#include "../headers/global.h"
#include "../headers/Player.h"

Player::Player() {
    xPos = 4;
    angle = 0;
    yPos = 4;
}


Player::checkLoop(double rayAngle) {
    int colision = 0;
    float tangente = tan(rayAngle);
    float cotangente = tan(pi/2 - rayAngle);
    while (true) {

        while (!colision) {
            distanceX = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);
            //distanceX = (colXX - xPos)*cos(rayAngle) + (colXY - yPos)*sin(rayAngle);

            if (distanceX >= distanceY)
                break;

            //if (colXX > 7) {colXX = 7;} if (colXY > 7) {colXY = 7;}
            //if (colXX < 0) {colXX = 0;} if (colXY < 0) {colXY = 0;}

            colision = mapa[(int)colXY][(int)colXX];

            if (colision != 0) {
                distance = distanceX;
                distance = (colXX - xPos)*cos(rayAngle) + (colXY - yPos)*sin(rayAngle);
                texturePosition = 0.3;//colXX - incX*(int)colXX;
                break;
            }

            colXY += incY; colXX += abs(cotangente)*incX; //evidentenmente esto esta bien: se el signo asi que es simplemente el incrmento por la tangente

        }

        while (!colision) {
            distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);
            //distanceY = (colYX - xPos)*cos(rayAngle) + (colYY - yPos)*sin(rayAngle);
            if (distanceY > distanceX)
                break;
            //if (colYX > 7) {colYX = 7;} if (colYY > 7) {colYY = 7;}
            //if (colYX < 0) {colYX = 0;} if (colYY < 0) {colYY = 0;}

            colision = mapa[(int)colYY][(int)colYX];

            if (colision != 0) {
                distance = distanceY;
                distance = (colYX - xPos)*cos(rayAngle) + (colYY - yPos)*sin(rayAngle);
                texturePosition = 0.7;//colYY - incY*(int)colYY;
                break;
            }

            colYX += incX; colYY += tangente*incX; //evidentenmente esto esta bien: se el signo asi que es simplemente el incrmento por la tangente

        }


        if (colision != 0)
                break;
    }
    return colision;
}

Player::rayCast(){
    double angleRay = angle + pi/3;
    console.clearScreen();
    for (int column = 0; column < console.sWidth; column++) {

        angleRay -= (2*pi/3)/console.sWidth;

        if (angleRay >= 2*pi)
            angleRay -= 2*pi;
        else if (angleRay < 0)
            angleRay += 2*pi;


        colXX = xPos; colXY = yPos;
        colYX = xPos; colYY = yPos;

        prepareCollision(angleRay);
        distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);
        distanceX = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);



        int texture = checkLoop(angleRay);

        console.drawLine(256/distance, texture, column, texturePosition);

    }
    return 0;
}

Player::prepareCollision(double angulo) {
    if ((0 <= angulo) && (angulo < pi/2)) {incY = 1; incX = 1;}
    else if ((pi/2 <= angulo) && (angulo < pi)) {incY = 1; incX = -1;}
    else if ((pi <= angulo) && (angulo < 3*pi/2)) {incY = -1; incX = -1;}
    else {incY = -1; incX = 1;}

    colYX = (int)xPos + incX;               //y esta
    if (incX == -1) {colYX += 1;}

    colYY = yPos + abs((colYX - xPos)*tan(angulo))*incY; //esta formula esta chequeada

    colXY = (int)yPos + incY;           //esta parte estoy basttante seguro de que esta bien
    if (incY == -1) {colXY += 1;}

    colXX = xPos + abs((colXY - yPos)/tan(angulo))*incX; //y esta
    return 0;

}
