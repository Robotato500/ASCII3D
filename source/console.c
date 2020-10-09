#include <stdio.h>
#include <windows.h>

HANDLE write_Handle;
HANDLE read_Handle;

SMALL_RECT window_Size = {0, 0, 79, 39};

COORD buffer_Size = {80, 40};

int consoleInit() {
    write_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    read_Handle = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitle("La chucha chucheira");

    SetConsoleWindowInfo(write_Handle, TRUE, &window_Size);

    SetConsoleScreenBufferSize(write_Handle, buffer_Size);

    return 0;
};
