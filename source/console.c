#include <stdio.h>
#include <windows.h>

HANDLE write_Handle;
HANDLE read_Handle;




int consoleInit(int width, int height, int font_width, int font_height) {
    write_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    read_Handle = GetStdHandle(STD_INPUT_HANDLE);

    SMALL_RECT window_Size = {0, 0, width - 1, height - 1};
    COORD buffer_Size = {width, height};

    SetConsoleTitle("La chucha chucheira");


    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(write_Handle, 0, &font);

    font.FontFamily = FF_DONTCARE;
    font.FontWeight = FW_NORMAL;

    font.dwFontSize.X = (SHORT)font_width;
    font.dwFontSize.Y = (SHORT)font_height;
    SetCurrentConsoleFontEx(write_Handle, FALSE, &font);
    wcscpy(font.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(write_Handle, FALSE, &font);

    //GetLargestConsoleWindowSize();

    SetConsoleActiveScreenBuffer(write_Handle);
    SetConsoleScreenBufferSize(write_Handle, buffer_Size);
    SetConsoleWindowInfo(write_Handle, TRUE, &window_Size);

    return 0;
};
