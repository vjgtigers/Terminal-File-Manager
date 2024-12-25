#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

#include "commandLine.h"
#include "commands.h"
#include "drawLayout.h"
#include "keyTracker.h"
#include "terminalCommands.h"
#include "miscFunctions.h"
#include "configInfo.h"
#include "liveSearch.h"

#define  WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

//escape sequence
#define ESC "\x1b"
//commonly used escape sequence for commands
#define CSI "\x1b["

using namespace std;

fd_display_data nameView {true, 20}; //no particularly recommended size - must remain active
fd_display_data extentionView {true, 5};//if file then display type, if folder then fldr
fd_display_data sizeView {false, 8}; //recommended size is 6 or 7 --probably 8
fd_display_data modifiedView {true, 14}; //recommended size is 14
fd_display_data createdView {true, 14}; //recommended size is 14

topBarSettings_template topBarSettings = {
    48, //when changing this there should be ample space for time and some area between
    17 //15 is the recommended amount
};



std::vector<std::string> saveOutData; //used to save all screen prints if debug mode is on

int fileSelectionPointer;
xy currentPointerLocation {0,2};
vector<fileInfoStruct> fileInformation;

advancedCodes_template advancedCodes = {false, false, false, "regular"};
renderCodes_template renderCodes = {char(62), char(179), char(196), char(194), char(193), char(197), char(217), char(192)};
keyPressCodes_template keyPressCodes ={'q', 'r', 'R', 'c', 's', 'a', 'h', 't'};

string currTime = "";
string path_dir;

//TODO: crashes if you try to open folder that you dont have perms too
int main() {//IF I REDID DRAW WAY I COULD MAKE A RELLY COOL SCREENSHOT TAKER

    //YOU CAN NOT PUT THINGS THAT DEPEND ON TERMINAL SIZE UP HERE
    //initilization settings
    if (engineInit() == -1) {return -1;}

    char full[_MAX_PATH];
    path_dir = _fullpath(full, ".", 260);
    sendData<string>("path: " + path_dir+'\n');
    path_dir = full;
    //path will be SAVED ON COMMIT

    //end init settings
    xy wd = detectSize();
    sendData<string>("Terminal Size: <" + to_string(wd.x) + "," + to_string(wd.y) + ">\n");
    topBarSettings.dirMaxLen = wd.x/2;
    readUserConfig();
    sendData<string>("User Config Read if Avalible\n");
    //draw inital screen
    fileInput(fileInformation, path_dir);
    sendData<string>("Number of items detected: " + fileInformation.size() + '\n');

    //pause opening debug screen if both options are enabled
    if(advancedCodes.debugModeScreenDisplay == true & advancedCodes.debugMode == true) {
        system("PAUSE >nul");
    }
    refreshScreen(fileInformation); //could be faster i guess but for simplicity sake just did this (May 2 11 PM)
    //end draw inital screen
    while(true) {
        debugOutput("size of file" + fileInformation[fileSelectionPointer].size, -7);
        debugOutput("Global State: " + to_string(globalState),-1);
        const int key = key_press(); // blocks until a key is pressed
        xy available = detectSize();
        debugOutput(to_string(key) +" "+(char)key +" " + to_string(available.x) + " " + to_string(available.y), 0);


        if(key == keyPressCodes.quit) {toggleVT(false); onQuit();  return 0;}
        if(key == keyPressCodes.clear) {clearScreen();}

        if(key == keyPressCodes.refresh) {
            refreshScreen(fileInformation);
        }
        if(key == keyPressCodes.maintainStateRefresh) {
            maintainStateRefresh(fileInformation);
        }
        if(key == keyPressCodes.enterParFolder || key == -37) {fileSelectionPointer = 0; changeDir(fileInformation, path_dir); updateCursorandPointerSync(fileInformation);}
        if(key == keyPressCodes.enterCurrFolder || key == -39) {
            if (fileInformation[fileSelectionPointer].extention == "<DIR>") {
                path_dir =  path_dir + "\\" + fileInformation[fileSelectionPointer].name + "\\";
                changeDir(fileInformation, path_dir);
                updateCursorandPointerSync(fileInformation);
            }
        }
        if(key == keyPressCodes.down || key == -40) {(fileSelectionPointer+1 < fileInformation.size()) ? (fileSelectionPointer += 1) : true; updateCursorandPointerSync(fileInformation); }
        if(key == keyPressCodes.up || key == -38) {(fileSelectionPointer > 0) ? (fileSelectionPointer -= 1) : true; updateCursorandPointerSync(fileInformation); }

        if(key == ':') {cmdMain();}
        if(key == 'g') {liveSearch(fileInformation); maintainStateRefresh(fileInformation);}
        if(key == 'f') {openGithub();}
    }

    return 0;
}
