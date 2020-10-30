#include <math.h>
#include "../headers/global.h"
#include "../headers/Player.h"

Player::check_loop(float rayAngle) {
    while (true) {
        int colision = 0;
        while (!colision) {
            if (colXX > colYX):
                break;
            colision = mapa[(int)colXX][(int)colXY];
            if (colision != 0):
                break;
            colXY += 1; colXX += 1/tan(rayAngle);
        }
        while (!colision) {
            if (colYX > colXX):
                break;
            colision = mapa[(int)colYX][(int)colYY];
            if (colision != 0):
                break;
            colYX += 1; colYY += tan(rayAngle);
        }
        if (colision != 0):
                break;
    }
}

Player::rayCast(){
    float angleRay = angle - pi/3;
    for (int column = 0; i < console.sWidth; i++) {
        angleRay += (2*pi/3)/console.sWidth;
        if (angleRay >= 2*pi):
                angleRay -= 2*pi;
        if (0 <= angleRay < pi/2) {
            colYX = (int)xPos + 1;
            colYY = yPos + (colXX - xPos)*tan(angleRay);
        }
        else if (pi/2 <= angleRay < pi) {
            colYX = (int)xPos + 1;
            colYY = yPos + (colXX - xPos)*tan(angleRay);
        }
        else if (pi <= angleRay < 3*pi/2) {
            colYX = (int)xPos + 1;
            colYY = yPos + (colXX - xPos)*tan(angleRay);
        }
        else {
            colYX = (int)xPos + 1;
            colYY = yPos + (colXX - xPos)*tan(angleRay);
        }

    }
}

