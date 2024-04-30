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
        printf(CSI "?1049h");
    }
    else {
        printf(CSI "?1049l");
    }
}

void clearScreen() {
    system("CLS");
}


int engineInit() {
    if (!EnableVTMode()) {printf("Unable to enter VT processing mode. Quitting.\n");return -1;}
    toggleVT(true);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    cursorToggle(false);
    return 1;
}
