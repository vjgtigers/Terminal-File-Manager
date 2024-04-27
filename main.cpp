#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread>
#include <string>

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

xy available = detectSize();



int main()
{
    std::cout << "Hello, World!" << std::endl;


    if (!EnableVTMode()) {
        printf("Unable to enter VT processing mode. Quitting.\n");
        return -1;
    }
    toggleVT(true);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

    while(true) {
        const int key = key_press(); // blocks until a key is pressed
        println("Input is: "+to_string(key)+", \""+(char)key+"\"");

        CONSOLE_SCREEN_BUFFER_INFO sbInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
        int availableColumns = sbInfo.dwSize.X;
        int availableRows = sbInfo.dwSize.Y;


        cout << available.x << " " << available.y << endl;
        if(key == 'q') {toggleVT(false);return 0;}
        if(key == 'c') {clearScreen();}
    }

    return 0;
}
