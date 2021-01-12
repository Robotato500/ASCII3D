#include "../headers/Console.h"
#include "../headers/global.h"
#include <math.h>

int keyProcess(KEY_EVENT_RECORD key) {
    int returnValue = 0;
    if (key.bKeyDown) {
        switch(key.wVirtualKeyCode) {
            case VK_LEFT:
                jugador.roll = 1;
            break;

            case VK_RIGHT:
                jugador.roll = -1;
            break;

            case VK_UP:
                jugador.advance = 1;
            break;

            case VK_DOWN:
                jugador.advance = -1;
            break;

            case VK_ESCAPE:
                returnValue = 69;
            break;
        }
    }

    if (!key.bKeyDown) {
        switch(key.wVirtualKeyCode) {
            case VK_LEFT:
                if (jugador.roll == 1)
                    jugador.roll = 0;
            break;

            case VK_RIGHT:
                if (jugador.roll == -1)
                    jugador.roll = 0;
            break;

            case VK_UP:
                if (jugador.advance == 1)
                    jugador.advance = 0;
            break;

            case VK_DOWN:
                if (jugador.advance == -1)
                    jugador.advance = 0;
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

