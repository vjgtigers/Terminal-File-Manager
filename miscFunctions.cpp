//
// Created by vjgti on 4/27/2024.
//

#include "miscFunctions.h"

#include <iostream>
#include <thread>
#include <Windows.h>

#include "drawLayout.h"
#include "terminalCommands.h"

#define CSI "\x1b["


void println(const std::string& s) {
    std::cout << s << std::endl;
}

void sleep(const double t) {
    if(t>0.0) std::this_thread::sleep_for(std::chrono::milliseconds((int)(1E3*t+0.5)));
}

xy detectSize() {
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
    return {sbInfo.dwSize.X, sbInfo.dwSize.Y};

}

void debugOutput(const std::string& s, const int offset) {
    xy wd = detectSize();
    setCursorPosition(wd.x-30,wd.y-(wd.y-20)+offset);
    std::cout << std::string(30, ' ');
    setCursorPosition(wd.x-30,wd.y-(wd.y-20)+offset);
    std::cout << s;
}


void cursorToggle(bool enable) {
    if (enable == true) {
        printf(CSI "?25h");
    } else {
        printf(CSI "?25l");
    }
}


tmb_tem tmbDeterminator() {
    xy wd = detectSize();
    int usableY = wd.y - 5;
    //std::cout << usableY/2-1 <<' '<< usableY/2 <<' '<<usableY/2;
    if (usableY % 2 == 0) {
        return {usableY / 2 - 1, usableY / 2 + 1, usableY / 2};
    } else {
        return {(usableY - 1) / 2, (usableY - 1) / 2 + 2, (usableY - 1) / 2};
    }
}


int globalState;




void updateCursorandPointerSync(const std::vector<std::string>& fileNames) {
    xy wd = detectSize();
    tmb_tem tmb = tmbDeterminator();
    debugOutput("file:" + fileNames[fileSelectionPointer], 4);
    debugOutput(std::to_string(fileSelectionPointer), 1);

    if (globalState == 3) {
        drawSelectionPointer({0, fileSelectionPointer+2});
    }

    else if (fileSelectionPointer < tmb.top_length) {
        drawSelectionPointer({0, fileSelectionPointer+2});
        if (globalState != 0) {
            globalState = 0;
            displayFileInfo(fileNames);
        }
    }
    else if (fileSelectionPointer >= fileNames.size()-tmb.bottom_length) {
        int y = wd.y-3 - (fileNames.size()-fileSelectionPointer);
        drawSelectionPointer({0,y});
        if (globalState != 2) {
            globalState = 2;
            displayFileInfo(fileNames);
        }

    }
    else {
        if (globalState != 1) {
            globalState = 1;
            drawSelectionPointer({0, tmb.middle_pos});
        }
        displayFileInfo(fileNames);
    }

}
