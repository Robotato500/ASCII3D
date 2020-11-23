#include <math.h>
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
    float cotangente = (float)1/tan(rayAngle);
    while (true) {
        while (!colision) {
            if (colXX > colYX)
                break;
            if (colXX > 7) {colXX = 7;} if (colXY > 7) {colXY = 7;}
            if (colXX < 0) {colXX = 0;} if (colXY < 0) {colXY = 0;}
            colision = mapa[(int)colXY][(int)colXX];
            if (colision != 0) {
                distance = (colXX - xPos)*(colXX - xPos) + (colXY- yPos)*(colXY- yPos);
                //distance = (colXX - xPos)*cos(rayAngle) + (colXY- yPos)*sin(rayAngle);
                texturePosition = colXX - (int)colXX;
                break;
            }
            colXY += incX; colXX += cotangente*incX;
        }
        while (!colision) {
            if (colYX > colXX)
                break;
            if (colYX > 7) {colYX = 7;} if (colYY > 7) {colYY = 7;}
            if (colYX < 0) {colYX = 0;} if (colYY < 0) {colYY = 0;}
            colision = mapa[(int)colYY][(int)colYX];
            if (colision != 0) {
                distance = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);
                //distance = (colYX - xPos)*cos(rayAngle) + (colYY - yPos)*sin(rayAngle);
                texturePosition = colYY - (int)colYY;
                break;
            }
            colYX += incY; colYY += tangente*incY;
        }
        if (colision != 0)
                break;
    }
    return colision;
}

Player::rayCast(){
    double angleRay = angle - pi/3;
    console.clearScreen();
    for (int column = 0; column < console.sWidth; column++) {

        angleRay += (2*pi/3)/console.sWidth;

        if (angleRay >= 2*pi)
                angleRay -= 2*pi;

        colXX = xPos; colYX = xPos;
        colXY = yPos; colYY = yPos;

        prepareCollision(angleRay);


        int texture = checkLoop(angleRay);

        console.drawLine(128/distance, texture, column, texturePosition);

    }
    return 0;
}

Player::prepareCollision(double angulo) {
    if ((0 <= angulo) && (angulo < pi/2)) {incY = 1; incX = 1;}
    else if ((pi/2 <= angulo) && (angulo < pi)) {incY = -1; incX = -1;}
    else if ((pi <= angulo) && (angulo < 3*pi/2)) {incY = 1; incX = 1;}
    else {incY = 1; incX = 1;}

    colYX = (int)xPos + incY;
    colYY = yPos + (colYX - xPos)*tan(angulo);

    colXY = (int)yPos + incX;
    colXX = xPos + (colXY - yPos)/tan(angulo);
    return 0;
}
