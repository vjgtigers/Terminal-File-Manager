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

    int slots[6];
    slots[0] = 1+nameView.size;
    slots[1] = 2+nameView.size+extentionView.size;
    slots[2] = 3+nameView.size+extentionView.size+sizeView.size;
    slots[3] = 4+nameView.size+extentionView.size+sizeView.size+typeView.size;
    slots[4] = 5+nameView.size+extentionView.size+sizeView.size+typeView.size+modifiedView.size;
    slots[5] = 6+nameView.size+extentionView.size+sizeView.size+typeView.size+modifiedView.size+createdView.size;

    for (int i =2; i < wd.y-2; ++i) {
        setCursorPosition(slots[0],i);
        std::cout << char(179);
        setCursorPosition(slots[1], i);
        std::cout << char(179);
        setCursorPosition(slots[2], i);
        std::cout << char(179);
        setCursorPosition(slots[3], i);
        std::cout << char(179);
        setCursorPosition(slots[4], i);
        std::cout << char(179);
        setCursorPosition(slots[5], i);
        std::cout << char(179);
    }
    for(int i: slots) {
        setCursorPosition(i,1);
        std::cout << char(194);
        setCursorPosition(i, wd.y-2);
        std::cout << char(193);
    }



    setCursorPosition(0,wd.y-1);
    //std::cout << nameView.size;
}

