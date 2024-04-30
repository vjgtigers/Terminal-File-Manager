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
    std::cout << std::string(wd.x,renderCodes.divHori);
    setCursorPosition(0, wd.y-3);
    std::cout << std::string(wd.x,renderCodes.divHori);
    setCursorPosition(5,5);

    int slots[5];
    if (nameView.active == true){slots[0] = 1+nameView.size;}
    else {slots[0] = 1;}
    //TODO: this is the basic framework for cheking if activation
        //however we need to check for activation on line draw too
        // i need to work on this
    slots[1] = 1+slots[0]+extentionView.size;
    slots[2] = 1+slots[1]+sizeView.size;
    slots[3] = 1+slots[2]+modifiedView.size;
    slots[4] = 1+slots[3]+createdView.size;

    for (int i =2; i < wd.y-3; ++i) {
        setCursorPosition(slots[0],i);
        std::cout << renderCodes.divVert;
        setCursorPosition(slots[1], i);
        std::cout << renderCodes.divVert;
        setCursorPosition(slots[2], i);
        std::cout << renderCodes.divVert;
        setCursorPosition(slots[3], i);
        std::cout << renderCodes.divVert;
        setCursorPosition(slots[4], i);
        std::cout << renderCodes.divVert;
    }
    for(int i: slots) {
        setCursorPosition(i,1);
        std::cout << renderCodes.topCombine;
        setCursorPosition(i, wd.y-3);
        std::cout << renderCodes.bottomCombine;
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
    std::cout << renderCodes.pointer;
    currentPointerLocation.x = xy_cursor.x;
    currentPointerLocation.y = xy_cursor.y;
}


void extendedFileInfoDisplay() {



}




void displayFileInfo(const std::vector<fileInfoStruct>& fileNames) {
    xy wd = detectSize();
    tmb_tem tmb = tmbDeterminator();
    debugOutput(std::to_string(tmb.top_length) + ' ' + std::to_string(tmb.middle_pos) + ' '+ std::to_string(tmb.bottom_length), 3);
    debugOutput(std::to_string(currentPointerLocation.x + ' ') + std::to_string(currentPointerLocation.y), 2);
    debugOutput("SIZE: " + std::to_string(fileNames.size()), -3);
    if (fileNames.size() <= wd.y-5) {
        for (int i = 2; i <fileNames.size()+2 && i < wd.y-3; ++i) {
            setCursorPosition(1, i);
            std::cout << fileNames[i-2].name.substr(0,nameView.size);
            if (fileNames[i-2].name.length() < nameView.size) {
                std::cout << std::string(nameView.size - fileNames[i-2].name.length(), ' ');
            }
        }
    }

    else if (currentPointerLocation.y < tmb.middle_pos) { //this might not work with new selection pointer
        for (int i = 2; i < fileNames.size()+2 && i < wd.y-3; ++i) {
            setCursorPosition(1, i);
            std::cout << fileNames[i-2].name.substr(0,nameView.size);// << ((20-fileNames[i-2].length() > 0) ? std::string(20-fileNames[i-2].length(), ' '):std::string(0, ' '));
            if (fileNames[i-2].name.length() < nameView.size) {
                std::cout << std::string(nameView.size - fileNames[i-2].name.length(), ' ');
            }
        }
    }

    else if (currentPointerLocation.y > tmb.middle_pos) {
        for (int i = fileNames.size()-1, y =wd.y-4;i >= 0 && y >= 2; i--, y--) {
            setCursorPosition(1,y); //(fileName[i].length()-20 > 0) ? std::string(fileName[i].length()-20, ' ')
            //debugOutput(fileNames[i]);
            std::cout << fileNames[i].name.substr(0,nameView.size);// << ((20-fileNames[i].length() > 0) ? std::string(""): "");
            if (fileNames[i].name.length() < nameView.size) {
                std::cout << std::string(nameView.size-fileNames[i].name.length(), ' ');
            }
        }
    }

    else if (currentPointerLocation.y = tmb.middle_pos) {
        for (int i = tmb.middle_pos, y = 0; i > 1 && y != -1; --i, ++y) {
            setCursorPosition(1, i);
            std::cout << fileNames[fileSelectionPointer-y].name.substr(0,nameView.size);
            if (fileNames[fileSelectionPointer-y].name.length() < nameView.size) {
                std::cout << std::string(nameView.size-fileNames[fileSelectionPointer-y].name.length(), ' ');
            }
        }
        for (int i = tmb.middle_pos+1, y = 1; i < wd.y-3 && y != -1; ++i, ++y) {
            setCursorPosition(1, i);
            std::cout << fileNames[fileSelectionPointer+y].name.substr(0,nameView.size);
            if (fileNames[fileSelectionPointer+y].name.length() < nameView.size) {
                std::cout << std::string(nameView.size-fileNames[fileSelectionPointer+y].name.length(), ' ');
            }
        }
    }

    debugOutput("done", 0);
    std::cout << tmb.top_length << " " << tmb.middle_pos << " " << tmb.bottom_length;
}




void refreshScreen(const std::vector<fileInfoStruct>& fileNames) {
    cursorToggle(false);
    clearScreen();
    drawBaseLayout();
    currentPointerLocation = {0,2};
    fileSelectionPointer = 0;
    displayFileInfo(fileNames);
    drawSelectionPointer(currentPointerLocation);
    globalStateCalculator();
}


