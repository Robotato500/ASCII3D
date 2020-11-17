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
            colision = mapa[(int)colXX][(int)colXY];
            if (colision != 0) {
                distance = (colXX - xPos)*cos(rayAngle) - (colXY- yPos)*sin(rayAngle);
                texturePosition = colXX - (int)colXX;
                break;
            }
            colXY += 1; colXX += cotangente;
        }
        while (!colision) {
            if (colYX > colXX)
                break;
            colision = mapa[(int)colYX][(int)colYY];
            if (colision != 0) {
                distance = (colYX - xPos)*cos(rayAngle) - (colYY - yPos)*sin(rayAngle);
                texturePosition = colYY - (int)colYY;
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

        prepareCollision(angleRay);

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
