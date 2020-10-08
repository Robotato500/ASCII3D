#include <stdio.h>
#include <windows.h>

HANDLE write_Handle;
HANDLE read_Handle;

int console_Init() {
    write_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    read_Handle = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitle("La chucha chucheira");
    return 0;
};
