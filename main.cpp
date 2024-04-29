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
fd_display_data typeView {true, 4}; //TODO: is this nessessary?
fd_display_data modifiedView {true, 14}; //recommended size is 14
fd_display_data createdView {true, 14}; //recommended size is 14



//TODO: generate a vector with all the outputs then display them all at once

//top length . center point . bottem length
int fileSelectionPointer = 0;
//TODO: xy-avalible should probably be in the draw functions to update teh window on resize

vector<string> name;

xy currentPointerLocation {0,2};
int main()
{
    std::cout << "Hello, World!" << std::endl;
    fileSelectionPointer = 0;
    globalState = 0;
    name.push_back("this is my foldeoeueoueur");
    name.push_back("this is my folder2");
    name.push_back("this is my folder3");
    name.push_back("this is my folder4");

    // for(int i = 0;i < 100; ++i) {
    //     name.push_back("this is a file" +  to_string(i));
    // }
    // name.at(99) = "cmtnchaonsetuhtnoaeus";
    //
     for (int i = 0; i < 14; ++i) {
         name.push_back("new entyf" +to_string(i));
     }
    xy xy2 = detectSize();
    if (xy2.y >= name.size()) {
        globalState = 3;
    }

    //initilization settings
    if (!EnableVTMode()) {printf("Unable to enter VT processing mode. Quitting.\n");return -1;}
    toggleVT(true);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    cursorToggle(false);
    //end init settings

    drawBaseLayout();


    debugOutput("test", 0);
    displayFileInfo(name);

    drawSelectionPointer({0,2});

    while(true) {
        const int key = key_press(); // blocks until a key is pressed
        //println("Input is: "+to_string(key)+", \""+(char)key+"\"");
        xy available = detectSize();
        debugOutput(to_string(key) +" "+(char)key +" " + to_string(available.x) + " " + to_string(available.y), 0);


        if(key == 'q') {toggleVT(false);return 0;}
        if(key == 'c') {clearScreen();}

        if(key == 'r') {
            refreshScreen(name);
        }
        if(key == 'R') {
            displayFileInfo(name);
        }


        if(key == -40) {(fileSelectionPointer+1 < name.size()) ? (fileSelectionPointer += 1) : true; updateCursorandPointerSync(name); }
        if(key == -38) {(fileSelectionPointer > 0) ? (fileSelectionPointer -= 1) : true; updateCursorandPointerSync(name); }

        //if(key == -40) {drawSelectionPointer({currentPointerLocation.x, currentPointerLocation.y+1});}
        //if(key == -38) {drawSelectionPointer({currentPointerLocation.x, currentPointerLocation.y-1});}
    }

    return 0;
}
