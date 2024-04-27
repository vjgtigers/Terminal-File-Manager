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


// 00-00-00 00-00


using namespace std;



fd_display_data nameView {true, 20}; //no particularly recommended size
fd_display_data extentionView {true, 5};
fd_display_data sizeView {true, 6}; //recommended size is 6
fd_display_data typeView {true, 4}; //TODO: is this nessessary?
fd_display_data modifiedView {true, 14}; //recommended size is 14
fd_display_data createdView {true, 14}; //recommended size is 14

struct fdInfo {
    string name;
    int type;
    long long size;
    string extention;
};

//TODO: xy-avalible should probably be in the draw functions to update teh window on resize


int main()
{
    std::cout << "Hello, World!" << std::endl;


    if (!EnableVTMode()) {
        printf("Unable to enter VT processing mode. Quitting.\n");
        return -1;
    }
    toggleVT(true);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);


    drawBaseLayout();
    while(true) {
        const int key = key_press(); // blocks until a key is pressed
        //println("Input is: "+to_string(key)+", \""+(char)key+"\"");
        xy available = detectSize();
        debugOutput(to_string(key) +" "+(char)key +" " + to_string(available.x) + " " + to_string(available.y));


        if(key == 'q') {toggleVT(false);return 0;}
        if(key == 'c') {clearScreen();}
    }

    return 0;
}
