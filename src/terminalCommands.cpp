//
// Created by vjgti on 4/27/2024.
//

//all commands in here have some effect on the terminal

#include "terminalCommands.h"

#include <iostream>
#include <Windows.h>

#include "miscFunctions.h"

//commonly used escape sequence for commands
#define CSI "\x1b["

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

bool EnableVTMode() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return false;
    }

    return true;
}

void toggleVT(bool toggle) {
    if (toggle == true) {
        sendData<std::string>(CSI "?1049h");
    }
    else {
        sendData<std::string>(CSI "?1049l");
    }
}

int engineInit() {
    if (!EnableVTMode()) {printf("Unable to enter VT processing mode. Quitting.\n");return -1;}
    toggleVT(true);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    cursorToggle(false);
    globalStateCalculator(); //not strictly nessessary because no files are in the system yet
    fileSelectionPointer = 0;
    sendData<std::string>("\033]0; TFV - DEVELOPMENT \007");
    return 1;
}

//TODO : make sure this is shown in the debug data
void clearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;
    sendData<std::string>("", {1000,1000}, "cs");
    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
      hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
      hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
        return;
}