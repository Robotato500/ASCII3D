#include <math.h>
#include <cstdlib>
#include "../headers/global.h"
#include "../headers/Player.h"

Player::Player() {      //al crear un player lo importante es la poicion y el angulo inicial
    xPos = 8;
    angle = 0;
    yPos = 8;
    fov = (pi/6);
    dpp = (int)abs((((float)console.dWidth/2)/tan(fov)));
    speed = 0.0000025;
    /*float a[console.dWidth];
    int b[console.dWidth];
    distancePerRay1 = a;
    distancePerRay2 = a;
    texturePosPerRay1 = a;
    texturePosPerRay2 = a;
    texturePerRay1 = b;
    texturePerRay2 = b;*/
}

int Player::roundXCoord(float xCoord) {     //funcion para redondear de forma correcta para las colisiones
    if (incX == 1)                          //si avanza por el psoitivo
        return (int)xCoord;                 //directamente trunca
    else                                    //si avanza por el negativo
        return ((int)xCoord - 1);           //trunca - 1
}

int Player::roundYCoord(float yCoord) {     //lo mismo para la y
    if (incY == 1)
        return (int)yCoord;
    else
        return ((int)yCoord - 1);
}



Player::checkLoop(double rayAngle, int columna) {        //bucle de hacer avanzar el rayo y comprobar si hay colision
    int colision = 0;                       //para empezar no hay colision (tipo de bloque colisionado = 0)
    float tangente = tan(rayAngle);         //guardo la tangente y la cotangnte para no tener  que llamar constantemente las funciones
    float cotangente = tan(pi/2 - rayAngle);
    while (true) {                          //bucle

        while (!colision) {                 //bucle de colisiones con el eje x, tiene guardado un punto de colision con el eje x
            distanceX = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);  //calculo la distancia sobre el rayo por la que voy (en la que esta la colision con el x guardada)

            if (distanceX >= distanceY)  //si la distancia de este punto es mayo o igual que la del ultimo punto guardado de las colisiones con el eje y
                break;  //eso quiere decir que toca comprobar colisiones con el eje y, ya que esta mas cerca del jugador


            colision = mapa[roundYCoord(colXY)][(int)colXX];    //comprueba el mapa, redondeando como tiene que ser, si en el punto de colision actual hay bloque

            if (colision != 0) {        //si hay colision
                distance = (colXX - xPos)*cos(jugador.angle) + (colXY - yPos)*sin(jugador.angle);   //calculo la distancia proyectada que usa la funcion de dibujar
                texturePosition = colXX - (int)colXX;   //y en que parte del bloque me he chocado para saber que columna de pixeles de la textura asignada
                console.columnDistance[columna] = distanceX; //guarda la distancia al muro en esta columna de pixeles para luego dibujar bien los sprites
                break;  //se sale del bucle
            }

            visibleMap[roundYCoord(colXY)][(int)colXX] = 1;

            colXY += incY; colXX += cotangente*incY; //incremento el punto de colision para pasar al siguiente (la y va de uno en uno con su signo, ya que son colisiones con
                                                    //el eje x, y la x avanza con la cotangente

        }

        while (!colision) {     //mismo bucle, pero para las colisiones con el eje y
            distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);

            if (distanceY > distanceX)
                break;

            colision = mapa[(int)colYY][roundXCoord(colYX)];

            if (colision != 0) {
                distance = (colYX - xPos)*cos(jugador.angle) + (colYY - yPos)*sin(jugador.angle);
                texturePosition = colYY - (int)colYY;
                console.columnDistance[columna] = distanceY;
                break;
            }

            visibleMap[(int)colYY][roundXCoord(colYX)] = 1;

            colYX += incX; colYY += abs(tangente)*incY;

        }


        if (colision != 0)  //si ha habido colision, hemos terminado
                break;
    }
    return colision;    //y pues devuelve el tipo de bloque con el que ha habido colision
}

Player::rayCast(){ //funcion encargada de tirar los rayos y dibujar el espacio 3d

    double angleRay;

    float realDistance;

    int texture = 0;

    for (int i = 0; i < MAP_SIZE; i++){for (int j = 0; j < MAP_SIZE; j++){visibleMap[i][j] = 0;}}

    console.clearScreen();  //borra la pantala (y a�ade el cielo y el suelo)
    for (int column = 0; column < console.dWidth; column++) {       //bucle que tira un rayo por columna

        angleRay = -atan(((-(float)console.dWidth + 1)/(2) + (float)column)/(float)dpp) + angle;

        if (angleRay >= 2*pi)       //para que se quede entre 0 y 2pi
            angleRay -= 2*pi;
        else if (angleRay < 0)
            angleRay += 2*pi;

        prepareCollision(angleRay); //preparo las posiciones iniciales del rayo

        distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);//distancias iniciales
        distanceX = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);


        texture = checkLoop(angleRay, column);  //y chequeo las colisiones de este rayo
        //texturePerRay1[column] = texture;
        //distancePerRay1[column] = distance;
        //texturePosPerRay1[column] = texturePosition;
        console.drawLine(dpp/distance, texture-1, column, texturePosition, distance/3, &textureAtlas);

    }
    return 0;
}

Player::prepareCollision(double angulo) {   //prepara los incrementos y la primera posicion de las colisiones
    if ((0 <= angulo) && (angulo < pi/2)) {incY = 1; incX = 1;} //los signos de avanzar segun el cuadrante
    else if ((pi/2 <= angulo) && (angulo < pi)) {incY = 1; incX = -1;}
    else if ((pi <= angulo) && (angulo < 3*pi/2)) {incY = -1; incX = -1;}
    else {incY = -1; incX = 1;}

    colYX = (int)xPos + incX;               //dependiendo del caudrante del angulo elijo un puto u otro del cuadrado que rodea a la posicion del jugador como posicion inicial de las colisiones
    if (incX == -1) {colYX += 1;}

    colYY = yPos + abs((colYX - xPos)*tan(angulo))*incY;

    colXY = (int)yPos + incY;
    if (incY == -1) {colXY += 1;}

    colXX = xPos + abs((colXY - yPos)/tan(angulo))*incX;
    return 0;

}

Player::playerMov() {

    switch(roll) {
        case 1:
            angle += speed*deltaTime;
        break;

        case -1:
            angle -= speed*deltaTime;
        break;
    }

    if (angle >= 2*pi)       //para que se quede entre 0 y 2pi
            angle -= 2*pi;
        else if (angle < 0)
            angle += 2*pi;

    switch(advance) {
        case 1:
            xPos += speed*deltaTime*cos(jugador.angle);
            if (mapa[(int)yPos][(int)xPos])
                xPos -= speed*deltaTime*cos(jugador.angle);

            yPos += speed*deltaTime*sin(jugador.angle);
            if (mapa[(int)yPos][(int)xPos])
                yPos -= speed*deltaTime*sin(jugador.angle);
        break;

        case -1:
            xPos -= speed*deltaTime*cos(jugador.angle);
            if (mapa[(int)yPos][(int)xPos])
                xPos += speed*deltaTime*cos(jugador.angle);

            yPos -= speed*deltaTime*sin(jugador.angle);
            if (mapa[(int)yPos][(int)xPos])
                yPos += speed*deltaTime*sin(jugador.angle);
        break;
    }
}


//http://www.permadi.com/tutorial/raycast/rayc9.html
