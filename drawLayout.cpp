//
// Created by vjgti on 4/27/2024.
//

#include "drawLayout.h"

#include <iostream>

#include "miscFunctions.h"
#include "terminalCommands.h"


void drawBaseLayout() {
    clearScreen();
    setCursorPosition(0,1);
    xy wd =  detectSize();
    std::cout << std::string(wd.x,char(196));
    setCursorPosition(0, wd.y-2);
    std::cout << std::string(wd.x,char(196));
    setCursorPosition(5,5);

    //std::cout << nameView.size;
}

