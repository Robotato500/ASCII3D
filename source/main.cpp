#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
#include <string.h>
#include <math.h>
#include "../headers/console.h"
#include "../headers/global.h"
#include "../headers/input.h"
#include "../headers/Image.h"
#include "../headers/Player.h"
#define PI 3.14159265

/*  std::string texto = "la chucha chucheira";
    char texto_Array[texto.length() + 1];
    strcpy(texto_Array, texto.c_str()); */


int main() {
    srand(time(0));
    Player jugador;

    while (true) {
        //jugador.angle += 0.01;
        //jugador.xPos += 0.1;
        //jugador.rayCast();

        for (int i = 0; i < console.sWidth; i++) {
            float chucha = i/console.sWidth;
            console.drawLine(128, 1, i, 0.5);
        }
        console.refresh();
        if (processInputs() == 69)
            return 0;
    }
}


/*int main() {
    srand(time(0));
    console.clearScreen();
    console.refresh();

    Image texture("C:/Users/Usuario/Manu/Projects/ASCII3D/texture1.bmp");

    int jaja = 0;
    int tamano = texture.iWidth*texture.iHeight;
    int a[4] = {rand(), rand(), rand(), rand()};
    while (true) {
        for (int k = 0; k < console.sHeight; k++) {
                for (int l = 0; l < console.sWidth; l++) {

                    //float fx = ((l-64)*cos(jaja*PI/180) - (k-64)*sin(jaja*PI/180) + 64)*((float)texture.iWidth/console.sWidth)*sin(jaja*PI/180 + a[2])*2  + sin(jaja*PI/180 + a[0]);// + sin(jaja*PI/180)*100;
                    //float fy = ((l-64)*sin(jaja*PI/180) + (k-64)*cos(jaja*PI/180) + 64)*((float)texture.iHeight/console.sHeight)*sin(jaja*PI/180 + a[3])*2 + sin(jaja*PI/180 + a[1]);// + cos(jaja*PI/180)*100;

                    float fx = l*((float)texture.iWidth/console.sWidth);
                    float fy = k*((float)texture.iHeight/console.sHeight);

                    int x = (int)fx; int y = (int)fy;
                    int modulo = (x + texture.iWidth*y)%tamano;
                    if (modulo < 0)
                        modulo += tamano;

                    console.buffer[l + console.sWidth*k].Attributes = texture.buffer[modulo];
                    console.buffer[l + console.sWidth*k].Char.AsciiChar = 219;

                    //std::cout<<fx; std::cout<<"\n";
                }
        }
        console.refresh();
        if(processInputs()==69)
            return 0;
        jaja++;
    }
}
*/


//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-writing-to-console.html
