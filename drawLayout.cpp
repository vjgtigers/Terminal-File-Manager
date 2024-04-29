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
    if (nameView.active == true){slots[0] = 1+nameView.size;}
    else {slots[0] = 1;}
    //TODO: this is the basic framework for cheking if activation
        //however we need to check for activation on line draw too
        // i need to work on this
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
//TODO: one struct with vectors of info in it then pass that to the function
//display the filename/size/type/mod/creat/exten
void displayFileInfo(const std::vector<std::string>& fileNames) {
    xy wd = detectSize();
    tmb_tem tmb = tmbDeterminator();
    debugOutput(std::to_string(tmb.top_length) + ' ' + std::to_string(tmb.middle_pos) + ' '+ std::to_string(tmb.bottom_length), 3);
    debugOutput(std::to_string(currentPointerLocation.x + ' ') + std::to_string(currentPointerLocation.y), 2);

    if (fileNames.size() <= wd.y-5) {
        for (int i = 2; i <fileNames.size()+2 && i < wd.y-3; ++i) {
            setCursorPosition(1, i);
            std::cout << fileNames[i-2].substr(0,20);
            if (fileNames[i-2].length() < 20) {
                std::cout << std::string(20 - fileNames[i-2].length(), ' ');
            }
        }
    }

    else if (currentPointerLocation.y < tmb.middle_pos) { //this might not work with new selection pointer
        for (int i = 2; i < fileNames.size()+2 && i < wd.y-3; ++i) {
            setCursorPosition(1, i);
            std::cout << fileNames[i-2].substr(0,20);// << ((20-fileNames[i-2].length() > 0) ? std::string(20-fileNames[i-2].length(), ' '):std::string(0, ' '));
            if (fileNames[i-2].length() < 20) {
                std::cout << std::string(20- fileNames[i-2].length(), ' ');
            }
        }
    }

    else if (currentPointerLocation.y > tmb.middle_pos) {
        for (int i = fileNames.size()-1, y =wd.y-4;i >= 0 && y >= 2; i--, y--) {
            setCursorPosition(1,y); //(fileName[i].length()-20 > 0) ? std::string(fileName[i].length()-20, ' ')
            //debugOutput(fileNames[i]);
            std::cout << fileNames[i].substr(0,20);// << ((20-fileNames[i].length() > 0) ? std::string(""): "");
            if (fileNames[i].length() < 20) {
                std::cout << std::string(20-fileNames[i].length(), ' ');
            }
        }
    }

    else if (currentPointerLocation.y = tmb.middle_pos) {
        for (int i = tmb.middle_pos, y = 0; i > 1 && y != -1; --i, ++y) {
            setCursorPosition(1, i);
            std::cout << fileNames[fileSelectionPointer-y].substr(0,20);
            if (fileNames[fileSelectionPointer-y].length() < 20) {
                std::cout << std::string(20-fileNames[fileSelectionPointer-y].length(), ' ');
            }
        }
        for (int i = tmb.middle_pos+1, y = 1; i < wd.y-3 && y != -1; ++i, ++y) {
            setCursorPosition(1, i);
            std::cout << fileNames[fileSelectionPointer+y].substr(0,20);
            if (fileNames[fileSelectionPointer+y].length() < 20) {
                std::cout << std::string(20-fileNames[fileSelectionPointer+y].length(), ' ');
            }
        }
    }

    debugOutput("done", 0);
    std::cout << tmb.top_length << " " << tmb.middle_pos << " " << tmb.bottom_length;
}




void refreshScreen(const std::vector<std::string>& fileNames) {
    clearScreen();
    drawBaseLayout();
    displayFileInfo(fileNames);
    drawSelectionPointer(currentPointerLocation);
}