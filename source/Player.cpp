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
                //distance = (colXX - xPos)*cos(rayAngle) + (colXY- yPos)*sin(rayAngle);
                distance = (colXX - xPos)*(colXX - xPos) + (colXY- yPos)*(colXY- yPos);
                texturePosition = 0.5;//colXX - (int)colXX;
                break;
            }
            colXY += 1; colXX += cotangente;
        }
        while (!colision) {
            if (colYX > colXX)
                break;
            if (colYX > 7) {colYX = 7;} if (colYY > 7) {colYY = 7;}
            if (colYX < 0) {colYX = 0;} if (colYY < 0) {colYY = 0;}
            colision = mapa[(int)colYY][(int)colYX];
            if (colision != 0) {
                //distance = (colYX - xPos)*cos(rayAngle) + (colYY - yPos)*sin(rayAngle);
                distance = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);
                texturePosition = 0.5;//colYY - (int)colYY;
                break;
            }
            colYX += 1; colYY += tangente;
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

        //prepareCollision(angleRay);


        int texture = checkLoop(angleRay);

        console.drawLine(128/distance, texture, column, texturePosition);

    }
    return 0;
}

Player::prepareCollision(double angulo) {
    if ((0 <= angulo) && (angulo < pi/2)) {
        colYX = (int)xPos + 1;
        colYY = yPos + (colYX - xPos)*tan(angulo);

        colXY = (int)yPos + 1;
        colXX = xPos + (colXY - yPos)/tan(angulo);
    }
    else if ((pi/2 <= angulo) && (angulo < pi)) {
        colYX = (int)xPos - 1;
        colYY = yPos + (colYX - xPos)*tan(angulo);

        colXY = (int)yPos + 1;
        colXX = xPos + (colXY - yPos)/tan(angulo);
    }
    else if ((pi <= angulo) && (angulo < 3*pi/2)) {
        colYX = (int)xPos - 1;
        colYY = yPos + (colYX - xPos)*tan(angulo);

        colXY = (int)yPos - 1;
        colXX = xPos + (colXY - yPos)/tan(angulo);
    }
    else {
        colYX = (int)xPos + 1;
        colYY = yPos + (colYX - xPos)*tan(angulo);

        colXY = (int)yPos - 1;
        colXX = xPos + (colXY - yPos)/tan(angulo);
    }

    return 0;
}
