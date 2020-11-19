#include "../headers/Console.h"
#include "../headers/global.h"
#include <math.h>

int keyProcess(KEY_EVENT_RECORD key) {
    int returnValue = 0;
    if (key.bKeyDown) {
        switch(key.wVirtualKeyCode) {
            case VK_LEFT:
                jugador.angle -= 0.1;
            break;

            case VK_RIGHT:
                jugador.angle += 0.1;
            break;

            case VK_UP:
                jugador.xPos += 0.1*cos(jugador.angle);
                jugador.yPos += 0.1*sin(jugador.angle);
                if (((jugador.xPos < 1) || (jugador.yPos < 1)) || ((jugador.xPos > 7) || (jugador.yPos > 7))) {
                    jugador.xPos -= 0.1*cos(jugador.angle);
                    jugador.yPos -= 0.1*sin(jugador.angle);
                }
            break;

            case VK_DOWN:
                jugador.xPos -= 0.1*cos(jugador.angle);
                jugador.yPos -= 0.1*sin(jugador.angle);
                if (((jugador.xPos < 1) || (jugador.yPos < 1)) || ((jugador.xPos > 7) || (jugador.yPos > 7))) {
                    jugador.xPos += 0.1*cos(jugador.angle);
                    jugador.yPos += 0.1*sin(jugador.angle);
                }
            break;

            case VK_ESCAPE:
                returnValue = 69;
            break;
        }
    }
    return returnValue;
}

int processInputs() {
    INPUT_RECORD inputBuffer[128];
    DWORD numEvents;
    GetNumberOfConsoleInputEvents(console.rHandle, &numEvents);
    if (numEvents == 0)
        return 0;
    ReadConsoleInputA(console.rHandle, inputBuffer, 128, &numEvents);
    int returnValue = 0;
    for (int i = 0; i < numEvents; i++) {
        switch(inputBuffer[i].EventType) {
            case KEY_EVENT:
                returnValue = keyProcess(inputBuffer[i].Event.KeyEvent);
            break;
        }
    }
    return returnValue;
}

