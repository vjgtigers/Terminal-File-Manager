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
    xy wd =  detectSize();
    sendData(std::string(wd.x,renderCodes.divHori), {0,1});
    sendData(std::string(wd.x,renderCodes.divHori), {0,wd.y-3});

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
            sendData(renderCodes.divVert, {i, j});
        }
        sendData(renderCodes.topCombine, {i, 1});
        sendData(renderCodes.bottomCombine, {i, wd.y-3});
    }
    //TODO: combine into one and loop though array that has the values in it
    //start draw dir divider
    sendData(renderCodes.divVert, {topBarSettings.dirMaxLen+1, 0});
    sendData(renderCodes.bottomCombine, {topBarSettings.dirMaxLen+1, 1});


    for (int  j : slots) {
        if (j == topBarSettings.dirMaxLen+1) {
            sendData(renderCodes.allcombine, {topBarSettings.dirMaxLen+1, 1});
            break;
        }
    }
    //end draw dir divider


    sendData(renderCodes.divVert, {wd.x-topBarSettings.timeMaxLen-1, 0});
    sendData(renderCodes.bottomCombine, {wd.x-topBarSettings.timeMaxLen-1, 1});

    for (int  j : slots) {
        if (j == wd.x-topBarSettings.timeMaxLen-1) {
            sendData(renderCodes.allcombine, {wd.x-topBarSettings.timeMaxLen-1, 1});
            break;
        }
    }
}

void displayDirBar(const std::string& dirName) {
    if( dirName.length() > topBarSettings.dirMaxLen) {
        sendData(dirName.substr(dirName.length()-topBarSettings.dirMaxLen), {1, 0});
    } else {
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
        sendData(s.substr(0,10) + s.substr(19), {wd.x - topBarSettings.timeMaxLen+1, 0});
        currTime = s.substr(0,10) + s.substr(19);
    }
}



void drawSelectionPointer(xy xy_cursor) {
    xy wd =  detectSize();
    if(xy_cursor.y<2 || xy_cursor.y >wd.y-4) {return;}
    sendData(' ', currentPointerLocation);
    sendData(renderCodes.pointer, xy_cursor);
    currentPointerLocation.x = xy_cursor.x;
    currentPointerLocation.y = xy_cursor.y;
}



void extendedFileInfoDisplay(const fileInfoStruct& fileInfo, const xy& wd) {
    if(extentionView.active == true) {
        sendData(fileInfo.extention.substr(0, extentionView.size), wd);

        if (fileInfo.extention.length() < extentionView.size) {
            sendData(std::string(extentionView.size - fileInfo.extention.length(), ' '));
        }
        sendData(renderCodes.divVert);

    }
    if (sizeView.active == true) {
        sendData(fileInfo.size.substr(0,sizeView.size));

        if (fileInfo.size.length() < sizeView.size) {
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
            sendData(fileNames[i-2].name.substr(0,nameView.size), {1, i});

            if (fileNames[i-2].name.length() < nameView.size) {
                sendData(std::string(nameView.size - fileNames[i-2].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[i-2], {nameView.size+2, i});
        }
    }

    else if (currentPointerLocation.y < tmb.middle_pos) { //this might not work with new selection pointer
        for (int i = 2; i < fileNames.size()+2 && i < wd.y-3; ++i) {
            sendData(fileNames[i-2].name.substr(0,nameView.size), {1, i});

            if (fileNames[i-2].name.length() < nameView.size) {
                sendData(std::string(nameView.size - fileNames[i-2].name.length(), ' '));
            }
            extendedFileInfoDisplay(fileNames[i-2], {nameView.size+2, i});
        }
    }

    else if (currentPointerLocation.y > tmb.middle_pos) {
        for (int i = fileNames.size()-1, y =wd.y-4;i >= 0 && y >= 2; i--, y--) {
            sendData(fileNames[i].name.substr(0,nameView.size), {1,y});

            if (fileNames[i].name.length() < nameView.size) {
                sendData(std::string(nameView.size-fileNames[i].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[i], {nameView.size + 2, y});
        }
    }

    else if (currentPointerLocation.y = tmb.middle_pos) {
        for (int i = tmb.middle_pos, y = 0; i > 1 && y != -1; --i, ++y) {
            sendData(fileNames[fileSelectionPointer-y].name.substr(0,nameView.size), {1, i});

            if (fileNames[fileSelectionPointer-y].name.length() < nameView.size) {
                sendData(std::string(nameView.size-fileNames[fileSelectionPointer-y].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[fileSelectionPointer-y], {nameView.size+2, i});
        }
        for (int i = tmb.middle_pos+1, y = 1; i < wd.y-3 && y != -1; ++i, ++y) {
            sendData(fileNames[fileSelectionPointer+y].name.substr(0,nameView.size), {1, i});

            if (fileNames[fileSelectionPointer+y].name.length() < nameView.size) {
                sendData(std::string(nameView.size-fileNames[fileSelectionPointer+y].name.length(), ' '));

            }
            extendedFileInfoDisplay(fileNames[fileSelectionPointer+y], {nameView.size+2, i});
        }
    }

    debugOutput("done", 0);
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
    updateCursorandPointerSync(fileNames);
    displayFileInfo(fileNames);
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

extern std::vector<std::string> saveOutData;

void sendData(const std::string& out, const xy& pos) {
    setCursorPosition(pos.x, pos.y);
    std::cout << out;
    if (advancedCodes.debugMode == true) {
        saveOutData.push_back("<" + std::to_string(pos.x) +',' +  std::to_string(pos.y) + ">" +out + '.');
    }
}
void sendData(const std::string& out) {
    std::cout << out;
    if (advancedCodes.debugMode == true) {
        saveOutData.push_back("<-,->" +out + '.');
    }
}
void sendData(const char& out) {
    std::cout << out;
    if (advancedCodes.debugMode == true) {
        saveOutData.push_back("<-,->"+ out + '.');
    }
}
void sendData(const char& out, const xy& pos) {
    setCursorPosition(pos.x, pos.y);
    std::cout << out;
    if (advancedCodes.debugMode == true) {
        saveOutData.push_back("<" + std::to_string(pos.x) + ','+ std::to_string(pos.y) + ">" +out + '.');
    }
}

#include <fstream>
void onQuit() {
    if(advancedCodes.debugMode != true) {return;}
    std::ofstream file("data.txt");
    for(auto t : saveOutData) {
        //std::cout << t << std::endl;
        file << t << std::endl;
    }
    file.close();
}
