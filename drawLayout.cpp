//
// Created by vjgti on 4/27/2024.
//

#include "drawLayout.h"

#include <iostream>
#include <string>
#include "miscFunctions.h"
#include "terminalCommands.h"



void drawBaseLayout() {
    clearScreen();
    setCursorPosition(0,1);
    xy wd =  detectSize();
    std::cout << std::string(wd.x,char(196));
    setCursorPosition(0, wd.y-3);
    std::cout << std::string(wd.x,char(196));
    setCursorPosition(5,5);

    int slots[6];
    slots[0] = 1+nameView.size;
    slots[1] = 1+slots[0]+extentionView.size;
    slots[2] = 1+slots[1]+sizeView.size;
    slots[3] = 1+slots[2]+typeView.size;
    slots[4] = 1+slots[3]+modifiedView.size;
    slots[5] = 1+slots[4]+createdView.size;

    for (int i =2; i < wd.y-3; ++i) {
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
        setCursorPosition(i, wd.y-3);
        std::cout << char(193);
    }



    setCursorPosition(0,wd.y-1);
    //std::cout << nameView.size;
}

extern xy currentPointerLocation;

void drawSelectionPointer(xy xy_cursor) {
    xy wd =  detectSize();
    if(xy_cursor.y<2 || xy_cursor.y >wd.y-4) {return;}
    setCursorPosition(currentPointerLocation.x, currentPointerLocation.y);
    std::cout << ' ';
    setCursorPosition(xy_cursor.x, xy_cursor.y);
    std::cout << char(62);
    currentPointerLocation.x = xy_cursor.x;
    currentPointerLocation.y = xy_cursor.y;
}


//TODO: add vector for each type for files and get them all printed


//TODO: will have to be redone to be able to scroll down in the files
//BUG: cant view other files
//display the filename/size/type/mod/creat/exten
void displayFileInfo(const std::vector<std::string>& fileNames) {
    xy wd = detectSize();
    for (int i = 2; i < fileNames.size()+2 && i < wd.y-3; ++i) {
        setCursorPosition(1, i);
        std::cout << fileNames[i-2];
    }
    debugOutput("done");
}


