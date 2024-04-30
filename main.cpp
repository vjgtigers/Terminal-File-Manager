#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread>
#include <string>

#include "drawLayout.h"
#include "keyTracker.h"
#include "terminalCommands.h"
#include "miscFunctions.h"

#define  WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

//escape sequence
#define ESC "\x1b"
//commonly used escape sequence for commands

#define CSI "\x1b["


using namespace std;


fd_display_data nameView {true, 20}; //no particularly recommended size
fd_display_data extentionView {true, 5};
fd_display_data sizeView {true, 6}; //recommended size is 6 or 7
fd_display_data modifiedView {true, 14}; //recommended size is 14
fd_display_data createdView {true, 14}; //recommended size is 14




//top length . center point . bottem length
int fileSelectionPointer = 0;
//TODO: xy-avalible should probably be in the draw functions to update teh window on resize



xy currentPointerLocation {0,2};



vector<fileInfoStruct> fileInformation;


int main()
{
    fileInformation.push_back({"oeu","oaeu","oaeu", "aoeu", "ooeu"});
    fileInformation.push_back({"404","5","oaeuuuaeu","33","oaeu[2"});
    //YOU CAN NOT PUT THINGS THAT DEPEND ON TERMINAL SIZE UP HERE
    //initilization settings
    if (engineInit() == -1) {return -1;}
    //end init settings



    fileSelectionPointer = 0;


    for (int i = 0; i < 40; ++i) {
        fileInformation.push_back({"new entry" +to_string(i),to_string(i),to_string(i),to_string(i),to_string(i)});
    }


    //TODO: globalStateCalc needs to be in the function that reads in files to determin global state then
    globalStateCalculator();
    drawBaseLayout();


    debugOutput("test", 0);
    displayFileInfo(fileInformation);

    drawSelectionPointer({0,2});

    while(true) {
        debugOutput("Global State: " + to_string(globalState),-1);
        const int key = key_press(); // blocks until a key is pressed
        //println("Input is: "+to_string(key)+", \""+(char)key+"\"");
        xy available = detectSize();
        debugOutput(to_string(key) +" "+(char)key +" " + to_string(available.x) + " " + to_string(available.y), 0);


        if(key == 'q') {toggleVT(false);return 0;}
        if(key == 'c') {clearScreen();}

        if(key == 'r') {
            refreshScreen(fileInformation);
        }
        if(key == 'R') {
            displayFileInfo(fileInformation);
        }


        if(key == -40) {(fileSelectionPointer+1 < fileInformation.size()) ? (fileSelectionPointer += 1) : true; updateCursorandPointerSync(fileInformation); }
        if(key == -38) {(fileSelectionPointer > 0) ? (fileSelectionPointer -= 1) : true; updateCursorandPointerSync(fileInformation); }

        //if(key == -40) {drawSelectionPointer({currentPointerLocation.x, currentPointerLocation.y+1});}
        //if(key == -38) {drawSelectionPointer({currentPointerLocation.x, currentPointerLocation.y-1});}
    }

    return 0;
}
