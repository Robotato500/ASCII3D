#include <math.h>
#include <cstdlib>
#include "../headers/global.h"
#include "../headers/Player.h"

Player::Player() {
    xPos = 8;
    angle = 0;
    yPos = 8;
}

int Player::roundXCoord(float xCoord) {
    if (incX == 1)
        return (int)xCoord;
    else
        return ((int)xCoord - 1);
}

int Player::roundYCoord(float yCoord) {
    if (incY == 1)
        return (int)yCoord;
    else
        return ((int)yCoord - 1);
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

            colision = mapa[roundYCoord(colXY)][(int)colXX];

            if (colision != 0) {
                distance = distanceX;
                distance = (colXX - xPos)*cos(jugador.angle) + (colXY - yPos)*sin(jugador.angle);
                texturePosition = colXX - (int)colXX;
                break;
            }

            colXY += incY; colXX += cotangente*incY; //evidentenmente esto esta bien: se el signo asi que es simplemente el incrmento por la tangente

        }

        while (!colision) {
            distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);
            //distanceY = (colYX - xPos)*cos(rayAngle) + (colYY - yPos)*sin(rayAngle);
            if (distanceY > distanceX)
                break;
            //if (colYX > 7) {colYX = 7;} if (colYY > 7) {colYY = 7;}
            //if (colYX < 0) {colYX = 0;} if (colYY < 0) {colYY = 0;}

            colision = mapa[(int)colYY][roundXCoord(colYX)];

            if (colision != 0) {
                distance = distanceY;
                distance = (colYX - xPos)*cos(jugador.angle) + (colYY - yPos)*sin(jugador.angle);
                texturePosition = colYY - (int)colYY;
                break;
            }

            colYX += incX; colYY += abs(tangente)*incY; //evidentenmente esto esta bien: se el signo asi que es simplemente el incrmento por la tangente

        }


        if (colision != 0)
                break;
    }
    return colision;
}

Player::rayCast(){
    double angleRay = angle + pi/8;
    console.clearScreen();
    for (int column = 0; column < SCREEN_WIDTH; column++) {

        angleRay -= (pi/4)/SCREEN_WIDTH;

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

        console.drawLine((console.sHeight)/(distance), texture, column, texturePosition);

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

Player::playerMov() {

    switch(roll) {
        case 1:
            jugador.angle += 0.05;
        break;

        case -1:
            jugador.angle -= 0.05;
        break;
    }

    switch(advance) {
        case 1:
            jugador.xPos += 0.05*cos(jugador.angle);
            jugador.yPos += 0.05*sin(jugador.angle);
        break;

        case -1:
            jugador.xPos -= 0.05*cos(jugador.angle);
            jugador.yPos -= 0.05*sin(jugador.angle);
        break;
    }
}

//http://www.permadi.com/tutorial/raycast/rayc9.html
