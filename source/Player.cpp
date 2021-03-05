#include <math.h>
#include <cstdlib>
#include "../headers/global.h"
#include "../headers/Player.h"

Player::Player() {      //al crear un player lo importante es la poicion y el angulo inicial
    xPos = 8;
    angle = 0;
    yPos = 8;
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



Player::checkLoop(double rayAngle) {        //bucle de hacer avanzar el rayo y comprobar si hay colision
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
                distance = (colXX - xPos + 1)*cos(jugador.angle) + (colXY - yPos + 1)*sin(jugador.angle);   //calculo la distancia proyectada que usa la funcion de dibujar
                texturePosition = colXX - (int)colXX;   //y en que parte del bloque me he chocado para saber que columna de pixeles de la textura asignar
                break;  //se sale del bucle
            }

            colXY += incY; colXX += cotangente*incY; //incremento el punto de colision para pasar al siguiente (la y va de uno en uno con su signo, ya que son colisiones con
                                                    //el eje x, y la x avanza con la cotangente

        }

        while (!colision) {     //mismo bucle, pero para las colisiones con el eje y
            distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);

            if (distanceY > distanceX)
                break;

            colision = mapa[(int)colYY][roundXCoord(colYX)];

            if (colision != 0) {
                distance = (colYX - xPos + 1)*cos(jugador.angle) + (colYY - yPos + 1)*sin(jugador.angle);
                texturePosition = colYY - (int)colYY;
                break;
            }

            colYX += incX; colYY += abs(tangente)*incY;

        }


        if (colision != 0)  //si ha habido colision, hemos terminado
                break;
    }
    return colision;    //y pues devuelve el tipo de bloque con el que ha habido colision
}

Player::rayCast(){ //funcion encargada de tirar los rayos y dibujar el espacio 3d

    double angleRay = angle + (pi/8)*(console.dWidth/console.dHeight);  //el angulo inicial es el actual + el aspect ratio*22.5º (porque el fov para 1:1 es de 45º)
    console.clearScreen();  //borra la pantala (y añade el cielo y el suelo)
    for (int column = 0; column < console.dWidth; column++) {       //bucle que tira un rayo por columna

        angleRay -= (pi/4)/console.dHeight;     //el siguiente angulo es desplazarlo a clockwise el fov total (45º*W/H) partido por W (ya que tira W rayos en total)

        if (angleRay >= 2*pi)       //para que se quede entre 0 y 2pi
            angleRay -= 2*pi;
        else if (angleRay < 0)
            angleRay += 2*pi;

        prepareCollision(angleRay); //preparo las posiciones iniciales del rayo

        distanceY = (colYX - xPos)*(colYX - xPos) + (colYY - yPos)*(colYY - yPos);//distancias iniciales
        distanceX = (colXX - xPos)*(colXX - xPos) + (colXY - yPos)*(colXY - yPos);


        int texture = checkLoop(angleRay);  //y chequeo las colisiones de este rayo

        console.drawLine((console.dHeight)/(distance), texture, column, texturePosition);   //y dibujo la columna de este rayo

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
            angle += 0.05;
        break;

        case -1:
            angle -= 0.05;
        break;
    }

    switch(advance) {
        case 1:
            xPos += 0.05*cos(jugador.angle);
            if ((mapa[(int)yPos][(int)xPos]) || (mapa[(int)yPos][(int)xPos]))
                xPos -= 0.05*cos(jugador.angle);
            yPos += 0.05*sin(jugador.angle);
            if ((mapa[(int)yPos][(int)xPos]) || (mapa[(int)yPos][(int)xPos]))
                yPos -= 0.05*sin(jugador.angle);
        break;

        case -1:
            xPos -= 0.05*cos(jugador.angle);
            yPos -= 0.05*sin(jugador.angle);
        break;
    }
}


//http://www.permadi.com/tutorial/raycast/rayc9.html
