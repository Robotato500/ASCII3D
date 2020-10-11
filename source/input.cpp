#include "../headers/Console.h"
#include "../headers/global.h"

int keyProcess(KEY_EVENT_RECORD key) {
    int returnValue = 0;
    if (key.bKeyDown) {
        switch(key.wVirtualKeyCode) {
            case VK_LEFT:
                if (console.cursorPos.X > 0) {
                    console.cursorPos.X -= 1;
                }
            break;

            case VK_RIGHT:
                if (console.cursorPos.X < (console.sWidth-1)) {
                    console.cursorPos.X += 1;
                }
            break;

            case VK_UP:
                if (console.cursorPos.Y > 0) {
                    console.cursorPos.Y -= 1;
                }
            break;

            case VK_DOWN:
                if (console.cursorPos.Y < (console.sHeight-1)) {
                    console.cursorPos.Y += 1;
                }
            break;

            case VK_ESCAPE:
                returnValue = 69;
            break;
        }
        console.refreshCursor();
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

