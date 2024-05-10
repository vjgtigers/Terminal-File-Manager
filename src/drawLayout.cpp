//
// Created by vjgti on 4/27/2024.
//

#include "drawLayout.h"

#include <filesystem>
#include <io.h>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <ctime>

#include <string>
#include "miscFunctions.h"
#include "terminalCommands.h"




#include <bits/fs_path.h>
#include <stdio.h>



extern xy currentPointerLocation;

void drawBaseLayout() {
    clearScreen();
    //setCursorPosition(0,1);
    xy wd =  detectSize();
    //std::cout << std::string(wd.x,renderCodes.divHori);

    sendData(std::string(wd.x,renderCodes.divHori), {0,1});

    //setCursorPosition(0, wd.y-3);
    //std::cout << std::string(wd.x,renderCodes.divHori);
    sendData(std::string(wd.x,renderCodes.divHori), {0,wd.y-3});

    //setCursorPosition(5,5);

    int arrLen = nameView.active + extentionView.active + sizeView.active + modifiedView.active + createdView.active;
    int slots[arrLen];
    if (nameView.active == true){slots[0] = 1+nameView.size;} //nameview will alwasy be active
    else {slots[0] = 1;}
    int slotCounter = 1;

    if (extentionView.active == true) {slots[slotCounter] = extentionView.size+1 + slots[slotCounter - 1]; slotCounter += 1;}
    if (sizeView.active == true) {slots[slotCounter] = sizeView.size+1 + slots[slotCounter - 1]; slotCounter += 1;}
    if (modifiedView.active == true) {slots[slotCounter] = modifiedView.size+1 + slots[slotCounter - 1]; slotCounter += 1;}
    if (createdView.active == true) {slots[slotCounter] = createdView.size+1 + slots[slotCounter - 1]; slotCounter += 1;}

    for ( int i : slots) {
        for (int j = 2; j< wd.y-3; ++j) {
            // setCursorPosition(i,j);
            // std::cout << renderCodes.divVert;
            sendData(renderCodes.divVert, {i, j});
        }
        // setCursorPosition(i,1);
        // std::cout << renderCodes.topCombine;
        sendData(renderCodes.topCombine, {i, 1});
        // setCursorPosition(i, wd.y-3);
        // std::cout << renderCodes.bottomCombine;
        sendData(renderCodes.bottomCombine, {i, wd.y-3});
    }
    //setCursorPosition(0,wd.y-1);
    //std::cout << nameView.size;
    //was not previouly in use

    //TODO: combine into one and loop though array that has the values in it
    //start draw dir divider
    // setCursorPosition(topBarSettings.dirMaxLen +1 ,0);
    // std::cout << renderCodes.divVert;
    sendData(renderCodes.divVert, {topBarSettings.dirMaxLen+1, 0});
    // setCursorPosition(topBarSettings.dirMaxLen+1, 1);
    // std::cout << renderCodes.bottomCombine;
    sendData(renderCodes.bottomCombine, {topBarSettings.dirMaxLen+1, 1});


    //setCursorPosition(topBarSettings.dirMaxLen+1, 1);
    for (int  j : slots) {
        if (j == topBarSettings.dirMaxLen+1) {
            //std::cout << renderCodes.allcombine;
            sendData(renderCodes.allcombine, {topBarSettings.dirMaxLen+1, 1});
            break;
        }
    }
    //end draw dir divider


    // setCursorPosition(wd.x-topBarSettings.timeMaxLen-1, 0);
    // std::cout << renderCodes.divVert;
    sendData(renderCodes.divVert, {wd.x-topBarSettings.timeMaxLen-1, 0});
    // setCursorPosition(wd.x-topBarSettings.timeMaxLen-1, 1);
    // std::cout << renderCodes.bottomCombine;
    sendData(renderCodes.bottomCombine, {wd.x-topBarSettings.timeMaxLen-1, 1});

    //setCursorPosition(wd.x-topBarSettings.timeMaxLen-1, 1);
    for (int  j : slots) {
        if (j == wd.x-topBarSettings.timeMaxLen-1) {
            //std::cout << renderCodes.allcombine;
            sendData(renderCodes.allcombine, {wd.x-topBarSettings.timeMaxLen-1, 1});
            break;
        }
    }
}

void displayDirBar(const std::string& dirName) {
    //setCursorPosition(1,0);
    if( dirName.length() > topBarSettings.dirMaxLen) {
        //std::cout << dirName.substr(dirName.length()-topBarSettings.dirMaxLen);
        sendData(dirName.substr(dirName.length()-topBarSettings.dirMaxLen), {1, 0});
    } else {
        //std::cout << dirName;
        //std::cout << std::string(topBarSettings.dirMaxLen- dirName.length(), ' ');
        sendData(dirName, {1,0});
        sendData(std::string(topBarSettings.dirMaxLen- dirName.length(), ' '));
    }
}

void displayTime() {
    xy wd = detectSize();
    auto t1 = std::chrono::system_clock::now();
    std::time_t t2 = std::chrono::system_clock::to_time_t(t1);
    char* o = ctime(&t2);
    std::string s((LPCTSTR)o); //contvert from c string to std::string
    debugOutput(s, -12);
    if (s.substr(0,16) != currTime) {
        //setCursorPosition(wd.x - topBarSettings.timeMaxLen + 1, 0);
        //std::cout << s.substr(0,10) << s.substr(19);//just date
        sendData(s.substr(0,10) + s.substr(19), {wd.x - topBarSettings.timeMaxLen+1, 0});
        currTime = s.substr(0,10) + s.substr(19);
    }
}



void drawSelectionPointer(xy xy_cursor) {
    xy wd =  detectSize();
    if(xy_cursor.y<2 || xy_cursor.y >wd.y-4) {return;}
    //setCursorPosition(currentPointerLocation.x, currentPointerLocation.y);
    //std::cout << ' ';
    sendData(' ', currentPointerLocation);
    // setCursorPosition(xy_cursor.x, xy_cursor.y);
    // std::cout << renderCodes.pointer;
    sendData(renderCodes.pointer, xy_cursor);
    currentPointerLocation.x = xy_cursor.x;
    currentPointerLocation.y = xy_cursor.y;
}



void extendedFileInfoDisplay(const fileInfoStruct& fileInfo, const xy& wd) {
    if(extentionView.active == true) {
        //setCursorPosition(wd.x, wd.y);
        //std::cout << fileInfo.extention.substr(0, extentionView.size);

        sendData(fileInfo.extention.substr(0, extentionView.size), wd);

        if (fileInfo.extention.length() < extentionView.size) {
            //std::cout << std::string(extentionView.size - fileInfo.extention.length(), ' ');

            sendData(std::string(extentionView.size - fileInfo.extention.length(), ' '));

        }
        //std::cout << renderCodes.divVert;

        sendData(renderCodes.divVert);

    }
    if (sizeView.active == true) {
        //std::cout << fileInfo.size.substr(0,sizeView.size);

        sendData(fileInfo.size.substr(0,sizeView.size));

        if (fileInfo.size.length() < sizeView.size) {
            //std::cout << std::string(sizeView.size - fileInfo.size.length(), ' ');

            sendData(std::string(sizeView.size - fileInfo.size.length(), ' '));

        }
    }
}


void displayFileInfo(const std::vector<fileInfoStruct>& fileNames) {
    xy wd = detectSize();
    tmb_tem tmb = tmbDeterminator();
    debugOutput(std::to_string(tmb.top_length) + ' ' + std::to_string(tmb.middle_pos) + ' '+ std::to_string(tmb.bottom_length), 3);
    debugOutput(std::to_string(currentPointerLocation.x + ' ') + std::to_string(currentPointerLocation.y), 2);
    debugOutput("SIZE: " + std::to_string(fileNames.size()), -3);
    if (fileNames.size() <= wd.y-5) {
        for (int i = 2; i <fileNames.size()+2 && i < wd.y-3; ++i) {
            //setCursorPosition(1, i);
            //std::cout << fileNames[i-2].name.substr(0,nameView.size);

            sendData(fileNames[i-2].name.substr(0,nameView.size), {1, i});


            if (fileNames[i-2].name.length() < nameView.size) {
                //std::cout << std::string(nameView.size - fileNames[i-2].name.length(), ' ');

                sendData(std::string(nameView.size - fileNames[i-2].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[i-2], {nameView.size+2, i});
        }
    }

    else if (currentPointerLocation.y < tmb.middle_pos) { //this might not work with new selection pointer
        for (int i = 2; i < fileNames.size()+2 && i < wd.y-3; ++i) {
            //setCursorPosition(1, i);
            //std::cout << fileNames[i-2].name.substr(0,nameView.size);// << ((20-fileNames[i-2].length() > 0) ? std::string(20-fileNames[i-2].length(), ' '):std::string(0, ' '));

            sendData(fileNames[i-2].name.substr(0,nameView.size), {1, i});

            if (fileNames[i-2].name.length() < nameView.size) {
                //std::cout << std::string(nameView.size - fileNames[i-2].name.length(), ' ');

                sendData(std::string(nameView.size - fileNames[i-2].name.length(), ' '));


            }
            extendedFileInfoDisplay(fileNames[i-2], {nameView.size+2, i});
        }
    }

    else if (currentPointerLocation.y > tmb.middle_pos) {
        for (int i = fileNames.size()-1, y =wd.y-4;i >= 0 && y >= 2; i--, y--) {
            //setCursorPosition(1,y); //(fileName[i].length()-20 > 0) ? std::string(fileName[i].length()-20, ' ')
            //debugOutput(fileNames[i]);
            //std::cout << fileNames[i].name.substr(0,nameView.size);// << ((20-fileNames[i].length() > 0) ? std::string(""): "");

            sendData(fileNames[i].name.substr(0,nameView.size), {1,y});

            if (fileNames[i].name.length() < nameView.size) {
                //std::cout << std::string(nameView.size-fileNames[i].name.length(), ' ');

                sendData(std::string(nameView.size-fileNames[i].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[i], {nameView.size + 2, y});
        }
    }

    else if (currentPointerLocation.y = tmb.middle_pos) {
        for (int i = tmb.middle_pos, y = 0; i > 1 && y != -1; --i, ++y) {
            //setCursorPosition(1, i);
            //std::cout << fileNames[fileSelectionPointer-y].name.substr(0,nameView.size);

            sendData(fileNames[fileSelectionPointer-y].name.substr(0,nameView.size), {1, i});

            if (fileNames[fileSelectionPointer-y].name.length() < nameView.size) {
                //std::cout << std::string(nameView.size-fileNames[fileSelectionPointer-y].name.length(), ' ');

                sendData(std::string(nameView.size-fileNames[fileSelectionPointer-y].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[fileSelectionPointer-y], {nameView.size+2, i});
        }
        for (int i = tmb.middle_pos+1, y = 1; i < wd.y-3 && y != -1; ++i, ++y) {
            //setCursorPosition(1, i);
            //std::cout << fileNames[fileSelectionPointer+y].name.substr(0,nameView.size);

            sendData(fileNames[fileSelectionPointer+y].name.substr(0,nameView.size), {1, i});

            if (fileNames[fileSelectionPointer+y].name.length() < nameView.size) {
                //std::cout << std::string(nameView.size-fileNames[fileSelectionPointer+y].name.length(), ' ');

                sendData(std::string(nameView.size-fileNames[fileSelectionPointer+y].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[fileSelectionPointer+y], {nameView.size+2, i});
        }
    }

    debugOutput("done", 0);
    //std::cout << tmb.top_length << " " << tmb.middle_pos << " " << tmb.bottom_length;
}


void clearFileInfo(const int& size) {
    xy wd = detectSize();
    if (size > wd.y-5) {return;}
    for (int i = 2 + size; i < wd.y-3; ++i) {
        sendData(std::string(nameView.size +1, ' '), {0, i});
        sendData(renderCodes.divVert);

        if (extentionView.active == true) {
            sendData(std::string(extentionView.size, ' '));
        }

        if (sizeView.active == true) {
            sendData(renderCodes.divVert);
            sendData(std::string(sizeView.size, ' '));

        }
    }
}


void dirBackRefresh(const std::vector<fileInfoStruct>& fileNames) {
    fileSelectionPointer = 0;
    clearFileInfo(fileNames.size());
    displayTime();
    displayDirBar(path_dir);
    displayFileInfo(fileNames);
    updateCursorandPointerSync(fileNames);
}


//TODO: some refresh function should research files
//TODO: on refresh recaluclate where div divider should be drawn
void refreshScreen(const std::vector<fileInfoStruct>& fileNames) {
    xy wd = detectSize();
    topBarSettings.dirMaxLen = wd.x/2;
    cursorToggle(false);
    clearScreen();
    drawBaseLayout();
    currentPointerLocation = {0,2};
    fileSelectionPointer = 0;
    displayFileInfo(fileNames);
    drawSelectionPointer(currentPointerLocation);
    globalStateCalculator();
    displayDirBar(path_dir);
    displayTime();
}


void maintainStateRefresh(const std::vector<fileInfoStruct>& fileNames) {
    xy wd = detectSize();
    topBarSettings.dirMaxLen = wd.x/2;
    cursorToggle(false);
    clearScreen();
    drawBaseLayout();
    displayTime();
    displayDirBar(path_dir);
    globalStateCalculator();
    displayFileInfo(fileNames);
    drawSelectionPointer(currentPointerLocation);

}



void sendData(const std::string& out, const xy& pos) {
    setCursorPosition(pos.x, pos.y);
    std::cout << out;
    //system("pause>nul");
}
void sendData(const std::string& out) {
    std::cout << out;
    //system("pause>nul");
}
void sendData(const char& out) {
    std::cout << out;
    //system("pause>nul");
}
void sendData(const char& out, const xy& pos) {
    setCursorPosition(pos.x, pos.y);
    std::cout << out;
    //system("pause>nul");
}
